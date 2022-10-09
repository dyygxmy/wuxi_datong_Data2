/**********************************************************************
 * file name  tighten_op_net.c
  describe   ：control enable
 *             Last tightening result data subscribe
 *
***********************************************************************/
#include "tighten_op_net.h"
#define  DEBUG_OUT

TightenOpNet::TightenOpNet(QObject *parent) :
    QObject(parent)
{
    powerOnFlag = true;                //data2 restart
    errCount = 0;
    errType = 0;
    boltCount = 0;
    boltNokCount = 0;
    intReadTighteningID = 0; //收到正常（MID:61）拧紧结果的拧紧ID+1
    intPreTighteningID = 0;      //current Tightening
    intOldTighteningID = 0;      //old Tightening
    nexoHandleFlag = 0;
    readMaxTightenIDFlag = false;
    nexoLinkOk = false;
    nexoAliveCount = 0;
    revDataLen =0;
    revFinishLen = 0;
    curveFirstFlag = 0;
    curveDataFlag = 0;
    sendVinFlag = 0;
    curveBuf.clear();
    sendNextEnableFlag = false;
    sendDisableFlag = false;
    oldTightenRedly = true;//收到按拧紧ID请求的结果
    timerCount = 0;
    sendTightenCount = 0;//发送按拧紧ID请求后等待时间
//    dataCount = 0;
    m_thread.start();
    this->moveToThread(&m_thread);
}
//线程开始
void TightenOpNet::tightenStart()
{
    DTdebug() << "cleco 2016_07_05 tighten_op_net thread start!!!" ;

    timer5000ms=new QTimer;
    tcpSocket = new QTcpSocket;
    connect(timer5000ms,SIGNAL(timeout()),this,SLOT(timerFuncXms()));
    connect(tcpSocket, SIGNAL(readyRead()),this, SLOT(revNexoData()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disConnectDO()));
    newConnects();
    timeOut1 = 250;
    timer5000ms->start(timeOut1);
}
//使能
void TightenOpNet::sendReadOperate()
{
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    controlType = config->value("/baseinfo/controlType").toString();
    delete config;

    if(ISRESET) //
    {
        ISRESET = false;
        if(controlType == "Cleco"){
            system("echo 0 > /sys/class/leds/OUTC1/brightness");
        }
        else {
            system("echo 1 > /sys/class/leds/OUTC1/brightness");
        }
        DTdebug()<< "************* ISRESET send disable*************";
    }
    else
    {
        if(controlType == "Cleco"){
            system("echo 1 > /sys/class/leds/OUTC1/brightness");
        }
        else {
            system("echo 0 > /sys/class/leds/OUTC1/brightness");
        }
        DTdebug()<< "************* send enable *************";
        vinBuf = VIN_PIN_SQL.toLatin1();
        boltNumberBuf = SCREWID_SQL.toLatin1();
//        setNexoTighten(VIN_PIN_SQL.toLatin1(),SCREWID_SQL.toLatin1(),proNum.toShort(),lsNum.toShort(),3);
    }
}


/**************************************/
//nexo alive
/**************************************/
void TightenOpNet::timerFuncXms()
{
    timerCount++;
    sendTightenCount++;
    //1秒还没请求到停止该拧紧ID的请求 跳过一个螺栓
    if(!oldTightenRedly && sendTightenCount > 1*1000/timeOut1){//1秒未收到请求回复
        if(requestList.size() > 0){
            qDebug()<<"past one blot:"<<requestList.first();
            sendTightenCount = 0;
            oldTightenRedly = true;
            requestList.removeFirst();
            emit sendconfigwarning(true);//跳过一个螺栓

            if(requestList.isEmpty()){//最后一个缺失螺栓跳过后处理缓存拧紧结果
                intReadTighteningID++;
                for(int i = 0 ; i < tightenResultTempList.size();i++){
                    int tightenID = tightenResultTempList.at(i).mid(221,10).toInt();
                    if(tightenID > intReadTighteningID){//再次检查缓存的拧紧数据中有没有缺失的
                        for(int j = 0;j < tightenID - intReadTighteningID;j++){
                            requestList<<intReadTighteningID+i;
                        }
                        for(int k = 0;k <= i;k++){
                            tightenResultTempList.removeAt(k);
                        }
                        break;
                    }else{
                        if(tightenID == intReadTighteningID){
                            manageTightenResult(61,tightenResultTempList.at(i));
                        }else{
                            qDebug()<<"tightenIDTemp error00:"<<tightenID << intReadTighteningID;
                        }
                    }
                    intReadTighteningID = tightenID + 1;
                }
                tightenResultTempList.clear();
                tightenIDTemp.clear();
            }
        }else{
            qDebug()<<"requestList error:"<<requestList.size();
        }
    }

    if(requestList.size() > 0)
    {
        qDebug()<<"requestList:"<<requestList;
        timerCount = 0;
        nexoAliveCount = 0;
        if(nexoLinkOk)//一直请求
        {
            intReadTighteningID = requestList.first();
            nexoHandleFlag = 0x04000000;//read old Tightening Data 按拧紧ID请求拧紧结果
            ctlNexoHandle();
            oldTightenRedly = false;
        }
    }
    else
    {
        if(timerCount >=5*1000/timeOut1)//5S
        {
            timerCount = 0;
            nexoAliveCount++;
            qDebug() << "op 5000ms tiemr" ;
            if(nexoLinkOk)                   //nexo link
            {
                nexoHandleFlag |= 0x00800000;//Alive
                ctlNexoHandle();             //send CMD to nexo
            }
        }
    }
    if(nexoAliveCount > 3)             //3 times alive not ack 3*5S
    {
        nexoAliveCount = 0;
        nexoLinkOk = false;
        emit IsTigntenReady(false);
        CsIsConnect = false;
        qDebug() << "3 times alive no ack disconnect  ";
        newConnects();
    }
}

/*******************************************************/
//nexo disconnect handle
/*******************************************************/
void TightenOpNet::disConnectDO()
{
    nexoLinkOk = false;
    CsIsConnect = false;
    DTdebug() << "OP disconnect 22222222222";
    newConnects();
}
/*******************************************************/
//nexo bulid connect
/*******************************************************/
void TightenOpNet::newConnects()
{
    tcpSocket->abort(); //取消已有的连接
    //连接到主机，这里从界面获取主机地址和端口号
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    QString IP_addr(config->value("baseinfo/cs351Ip").toString());
    controlType = config->value("/baseinfo/controlType").toString();
    delete config;
    tcpSocket->connectToHost(IP_addr,4545);
    tcpSocket->waitForConnected(2000); //waitting 2000ms
#ifdef DEBUG_OUT
    DTdebug() << "the socket state is" << IP_addr << tcpSocket->state()<<controlType;
#endif
    if(tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        CsIsConnect = true;
        DTdebug() << "OP link success  >>>>>>>>";
        nexoAliveCount = 0;
        timerCount = 0;
        nexoHandleFlag  = 0x00000001;  //start communication
        ctlNexoHandle();               //send CMD to nexo
    }
    else
    {
        CsIsConnect = false;
        nexoLinkOk = false;
        DTdebug() << "OP link fail XXXXXXXXXXXX" ;
    }
}

/***********************************/
//处理控制Nexo函数
//len:收到的网络包长度  Rx_Buffer[]:收到的网络包数据  Tx_len:发送网络包长度  Tx_Buffer[]:发送网络包数据
/*************************************/
void TightenOpNet::ctlNexoHandle()
{
    short Tx_len = 0;
    QByteArray sendBuf;
    /****************************************/
    /*******results data ACK**********/
    /****************************************/
    if(nexoHandleFlag&0x02000000)
    {
        nexoHandleFlag &= ~0x02000000;
        Tx_len = 21;
        sendBuf = "0020006200          ";
    }
    /****************************************/
    /*******results curve ACK**********/
    /****************************************/
    else if(nexoHandleFlag&0x00002000)
    {
        nexoHandleFlag &= ~0x00002000;
        Tx_len = 25;
        sendBuf = "0024000500          0900";
    }
    /****************************************/
    /**********communication stop***********/
    /****************************************/
    else if(nexoHandleFlag&0x00000010)
    {
        Tx_len = 21;
        sendBuf = "0020000300          ";
    }
    /****************************************/
    /**********communication start***********/
    /****************************************/
    else if(nexoHandleFlag&0x00000001)
    {
        Tx_len = 21;
        sendBuf = "00200001001         ";  //hu
    }
    /****************************************/
    /*Last tightening results data subscribe*/
    /****************************************/
    else if(nexoHandleFlag&0x01000000)
    {
        Tx_len = 21;
        sendBuf = "002000600011        ";   //hu
    }
    /****************************************/
    /*********      time set       **********/
    /****************************************/
    else if(nexoHandleFlag&0x40000000)
    {
        Tx_len = 40;
        sendBuf = "0039008200          2015-05-01:12:01:01";
        QDateTime time = QDateTime::currentDateTime();
        QString strTime = time.toString("yyyy-MM-dd:hh:mm:ss");
        sendBuf.replace(20,19,strTime.toLatin1());
    }
    /****************************************/
    /*********history results upload request**********/
    /****************************************/
    else if(nexoHandleFlag&0x04000000)
    {
        Tx_len = 31;
        sendBuf = "0030006400          0000000000";
        QByteArray tempBuf = QByteArray::number(intReadTighteningID,10);
        sendBuf.replace(30-tempBuf.size(),tempBuf.size(),tempBuf);
    }

    /****************************************/
    /*********      ID code        **********/
    /****************************************/
    else if(nexoHandleFlag&0x00010000)
    {
        Tx_len = 38;
        sendBuf = "0037005000          LSVAE45E7EN123456";
        sendBuf.replace(20,17,vinBuf); //replace vincode
    }
    /****************************************/
    /******** tool disable**********/
    /****************************************/
    else if(nexoHandleFlag&0x00000200)
    {
        Tx_len = 21;
        sendBuf = "0020004200          ";
    }
    /****************************************/
    /******** tool enable**********/
    /****************************************/
    else if(nexoHandleFlag&0x00000400)
    {
        Tx_len = 21;
        sendBuf = "0020004300          ";
    }
    /****************************************/
    /**********       Alive       ***********/
    /****************************************/
    else if(nexoHandleFlag&0x00800000)//5S send Alive
    {
        nexoHandleFlag &= ~0x00800000;
        Tx_len = 21;
        sendBuf = "00209999001         ";  //hu
    }
    if(controlType == "Atlas")
    {
        QString aaa = "1";
        sendBuf.replace(10,1,aaa.toLatin1());
    }
    else if(controlType == "Cleco")
    {
        QString aaa = " ";
        sendBuf.replace(10,1,aaa.toLatin1());
    }
    qDebug() << "sendCMD:" << sendBuf;// << "nexoHandleFlag :" << nexoHandleFlag ;
    tcpSocket->write(sendBuf,Tx_len);
    tcpSocket->waitForBytesWritten();

}
/***********************************/
//处理接受Nexo数据处理函数
//len:收到的网络包长度  Rx_Buffer[]:收到的网络包数据  Tx_len:发送网络包长度  Tx_Buffer[]:发送网络包数据
/*************************************/
void TightenOpNet::revNexoData()
{
    int nexoMID;
    int cmdType;
    int errCode;
    int revLen,cmdLen;
    QByteArray recBuf;//,hexBufTemp;

    recBuf.clear();
    recBuf = tcpSocket->readAll();
    GTestTightenData = "0231006100**********010001020003Cooper TMEM              04                         050006005070000080000091101111120190001302100014020000150201491600000170999918000001900015202020-04-22:13:28:48212019-01-18:14:05:09222230000031441\n";
//    recBuf = GTestTightenData.toLocal8Bit();
    nexoMID = recBuf.mid(4,4).toInt();
    revLen = recBuf.size();
    cmdLen = recBuf.mid(0,4).toInt();

    //    if(nexoMID != 9999)
    //    {
//    qDebug() << "recBuf:" << revLen << recBuf;
    //        DTdebug() << "/********************************************************************/";
    //    }
    if(revLen == (cmdLen+1))              //length of the same
    {
        nexoAliveCount = 0;           //recvice nexo data
        switch(nexoMID)
        {
        case 4:   //cmd send error         //send CMD to n
            cmdType = recBuf.mid(20,4).toInt();
            errCode = recBuf.mid(24,2).toInt();
            errCount ++;
            if(errCount > 2)   //over 3 timer no send cmdType
            {
                errCount = 0;
                DTdebug() << "nexo cmd error:" << cmdType << errCode;
                nexoHandleFlag = 0;
            }
            else
            {
                if(cmdType == 64)
                {}
                else
                {
                    timerCount = 0;
                    ctlNexoHandle();             //send CMD to nexo
                }
            }
            break;
        case 5:  //cmd send ok
            cmdType = recBuf.mid(20,4).toInt();
            errCount = 0;
            switch(cmdType)
            {
            case 18:     //select program
                //               nexoHandleFlag &= ~0x00000002;
                timerCount = 0;
                nexoHandleFlag = 0x00000004;//set bolt number
                ctlNexoHandle();             //send CMD to nexo
                break;
            case 19:     //set bolt number
                nexoHandleFlag &= ~0x00000004;
                break;
            case 42:    //tool disable
                nexoHandleFlag &= ~0x00000200;
                break;
            case 43:    //tool enable
                nexoHandleFlag &= ~0x00000400;
                break;
            case 60:    //result subscribe
                timerCount = 0;
                nexoHandleFlag = 0x40000000;//time set
                ctlNexoHandle();             //send CMD to nexo
                break;
            case 64:    //read old result
//                nexoHandleFlag &= ~0x04000000;//read old result
                break;
            case 82:    //set time
                nexoHandleFlag &= ~0x40000000;//time set
                break;
            default:
                break;
            }
            break;
        case 2:
            nexoLinkOk = true;                //communication start OK
            if(SYSS != "ING" && SYSS != "OK" && SYSS != "NOK")
            {
                SYSS = "Ready";
            }
            emit IsTigntenReady(true);
            timerCount = 0;
            nexoHandleFlag = 0x01000000;//tightening results data subscription
            ctlNexoHandle();             //send CMD to nexo
            break;
        case 9999://应答不显示在PC 测试使用
            break;
        case 61://Rev result data
            qDebug()<<"is61Result:"<<recBuf;
            timerCount = 0;
            nexoHandleFlag = 0x02000000;//result ACK
            ctlNexoHandle();            //send CMD to nexo
//            if(SYSS == "ING")
//            {
                tighteningID = recBuf.mid(221,10);                           //Tightening ID
                intPreTighteningID = tighteningID.toInt();
//                if(intPreTighteningID > intOldTighteningID)
                if(intPreTighteningID == intReadTighteningID)//非开机收到拧紧结果未缺失 订阅收到的拧紧结果ID == 上次记录的+1（说明数据未缺失）
                    //|| intReadTighteningID == 0 || requestList.size() > 0)
                {
                    if(requestList.size() > 0){//还有请求任务在处理中
                        tightenResultTempList<<QString(recBuf);//有请求任务在处理，先缓存当前收到的拧紧结果
                        tightenIDTemp<<intPreTighteningID;
                    }else{//无请求任务在处理，直接处理数据
                        intReadTighteningID = intPreTighteningID + 1;//确认下一次收到61拧紧结果正常的拧紧ID
                        manageTightenResult(nexoMID,QString(recBuf));
                    }
                }else{//开机收到拧紧结果 || 收到拧紧结果发现有缺失
                    qDebug() << "cleco last tightenResult error:"<<intPreTighteningID << intReadTighteningID;
                    if(intPreTighteningID > intReadTighteningID){//必需是后面来的任务，以前再来的数据不处理了
                        if(intReadTighteningID > 0){//非开机第一次收到拧紧结果
                            for(int i = 0;i < intPreTighteningID - intReadTighteningID;i++){
                                requestList<<intReadTighteningID+i;
                            }
                            tightenResultTempList<<QString(recBuf);//有缺失数据，先缓存当前收到的拧紧结果
                            tightenIDTemp<<intPreTighteningID;
                        }else{//开机第一次收到拧紧结果
                            qDebug()<<"the first tightenResult:"<<intPreTighteningID << intReadTighteningID;
                            intReadTighteningID = intPreTighteningID + 1;//确认下一次收到61拧紧结果正常的拧紧ID
                            manageTightenResult(nexoMID,QString(recBuf));
                        }
                    }else{//收到以前的数据
                        qDebug() << "cleco last tightenResult past:"<<intPreTighteningID << intReadTighteningID;
                    }
                }
                qDebug() << "cleco last tightenResult:" << tighteningID;
//            }
            break;
        case 65://old result data
            qDebug()<<"is65Result:"<<recBuf;
//            nexoHandleFlag &= ~0x02000000;                    //history results upload request
//            ctlNexoHandle();
//            if(SYSS == "ING")
//            {
                oldTighteningID = recBuf.mid(22,10);
                intOldTighteningID = oldTighteningID.toInt();
                if(intOldTighteningID == intReadTighteningID)//本次收到拧紧结果ID==请求的拧紧ID
                {
                    sendTightenCount = 0;
                    oldTightenRedly = true;
                    manageTightenResult(nexoMID,QString(recBuf));
                    requestList.removeFirst();
                    if(requestList.isEmpty()){//最后一个缺失螺栓请求成功后处理缓存拧紧结果
                        intReadTighteningID++;
                        for(int i = 0 ; i < tightenResultTempList.size();i++){
                            int tightenID = tightenResultTempList.at(i).mid(221,10).toInt();
                            if(tightenID > intReadTighteningID){//再次检查缓存的拧紧数据中有没有缺失的
                                for(int j = 0;j < tightenID - intReadTighteningID;j++){
                                    requestList<<intReadTighteningID+i;
                                }
                                for(int k = 0;k <= i;k++){
                                    tightenResultTempList.removeAt(k);
                                }
                                break;
                            }else{
                                if(tightenID == intReadTighteningID){
                                    manageTightenResult(61,tightenResultTempList.at(i));
                                }else{
                                    qDebug()<<"tightenIDTemp error11:"<<tightenID << intReadTighteningID;
                                }
                            }
                            intReadTighteningID = tightenID + 1;
                        }
                        tightenResultTempList.clear();
                        tightenIDTemp.clear();
                    }
                }else{
                    qDebug()<<"cleco old tightenResult error:"<<intOldTighteningID<<intReadTighteningID;
                }
                qDebug()<<"cleco old tightenResult:" << oldTighteningID;
//            }
            break;
        case 900:
            DTdebug() << "it is curve!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"  ;
        default:
            break;
        }
    }
    else
    {
        DTdebug() << "9999999999 data error";
    }
}

//处理按拧紧结果
void TightenOpNet::manageTightenResult(int type,QString data)
{
    int status;//收到拧紧机的合格状态 0 1
    QString nexoProNO;//程序号
    double torque;//扭矩
    double angle;//角度
    QString tightenTime;//拧紧时间
    if(61 == type){
        status = data.mid(107,1).toInt();
        nexoProNO = data.mid(90,3);
        torque = data.mid(140,6).toDouble()/100;
        angle  = data.mid(169,5).toDouble();
        tightenTime   = data.mid(176,19);
    }else if(65 == type){
        status = data.mid(72,1).toInt();
        nexoProNO = data.mid(61,3);
        torque = data.mid(81,6).toDouble()/100;
        angle  = data.mid(89,5).toDouble();
        tightenTime   = data.mid(96,19);
    }

    QString nexoResult = judgeOKStatus(status,torque,angle,nexoProNO);//OK or NOK

    qDebug()<<"tightenResult:"<<type<<torque<<angle<<nexoProNO<<nexoResult;
    data_model[0] = tightenTime.mid(0,10);
    data_model[1] = tightenTime.mid(11,8);
    data_model[2] = nexoResult;
    data_model[3] = QString::number(torque);
    data_model[4] = QString::number(angle);
    data_model[5] = QString(boltNumberBuf);
    data_model[6] = QString(vinBuf);
    data_model[7] = QString(oldTighteningID);
    data_model[8] = "Curve is null";
    data_model[9] = nexoProNO;
    data_model[10] = "1";
    emit sendfromworkthread(data_model);
    emit send_mainwindow(QString::number(torque),QString::number(angle),nexoResult);
}


QString TightenOpNet::judgeOKStatus(int status,double torque,double angle,QString nexoProNO)
{
    QString nexoResult = "NOK";
    if(nexoProNO != "099")       //99 program not count
    {
        if(0 == status)
        {
            nexoResult = "NOK";   //0=tightening NOK ,1=OK
        }
        else
        {
            nexoResult = "OK" ;
            if(bound_enabled)//启用了扭矩角度上下限设置
            {
                QSettings *config = new QSettings("/config_bound.ini", QSettings::IniFormat);
                double torque_max = config->value("/ProNumber"+proNum+"/Torque_max").toDouble();
                double torque_min = config->value("/ProNumber"+proNum+"/Torque_min").toDouble();
                double Angle_max = config->value("/ProNumber"+proNum+"/Angle_max").toDouble();
                double Angle_min = config->value("/ProNumber"+proNum+"/Angle_min").toDouble();
                delete config;
                if(torque_max == 0)
                {
                    torque_max = torque;
                    torque_min = torque;
                }
                if(torque_min == 0)
                    torque_min = torque;
                if(Angle_max == 0)
                {
                    Angle_max = angle;
                    Angle_min = angle;
                }
                if(Angle_min == 0)
                    Angle_min = angle;
                if((torque < torque_min) || (torque > torque_max) ||
                        (angle < Angle_min) || (angle > Angle_max))
                {
                    nexoResult = "NOK";
                }
            }
        }
        if(nexoResult == "NOK")
        {
            if(boltNokCount > 0)
                boltNokCount --;
        }
        else
        {
            if(boltCount > 0)
                boltCount --;
        }
    }
    else
    {
        nexoResult = "NOK";                                  //99 program nok
    }
    return nexoResult;
}
