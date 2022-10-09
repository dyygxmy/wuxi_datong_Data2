#include "tighten_op_wheel.h"
#include <QTimer>
#include <QtCore/qmath.h>
#include <QDateTime>
#include <QFile>

tighten_op_wheel::tighten_op_wheel(QString ip, int port ,QString cho,QObject *parent) :
    QObject(parent),ip(ip),port(port),cho(cho)
{
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disConnect()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readFunc()));
    qDebug() << "connectToHost:"<<this->ip<<this->port<<this->cho<<tcpSocket<<this;
    newConnect();

    this->moveToThread(&thread);
    thread.start();


    countCycle = 0;
    strJobID = "01";//查哪个程序号的JOB
    tighteningID = "";

    programNO = 0;
    boltCount = 0;

    connectFlag = false;
    startLiveFlag = false;//拧紧机启动成功开始心跳
    disConnectTime = 0;
    onceTimeOut = 0;
    dataMesSubType = 3;//订阅的数据类型（1:角度 2:扭矩 3:角度+扭矩 4:按循环号订阅曲线）
    currentMID = 0;//当前在用的MID
    receiveCurveT = false;//收到扭矩曲线
    receiveCurveA = false;//收到角度曲线
    missCycle = 0;//记录本次处理缺失曲线的循环号
    waitTask = 0;//存储本次不满足条件发送命令，等待满足后发送
    newTightenFlag = false;//来了新的拧紧结果，准备订阅曲线
    thghtenID = "";//拧紧循环号
    curveNullBuf = "Curve is null";
    qDebug()<<"thistighten_op_wheel"<<this;
}

//设置拧紧机连接参数 IP 端口等
//void tighten_op_wheel::setTcpSocket(QString ip, int port ,QString cho)
//{
//    this->ip = ip;
//    this->port = port;
//    this->LeftOrRight = cho;
//    this->start();
//}

//建立连接
void tighten_op_wheel::newConnect()
{
    QDateTime time1 = QDateTime::currentDateTime();
    tcpSocket->abort();
    tcpSocket->connectToHost(ip,port);
    tcpSocket->waitForConnected(2000);
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        qDebug()<<"*connect success*";
        taskCmdEndFlag = true;//任务结束了再发下一条指令
        connectFlag = true;
        CsIsConnect = true ;
        //qDebug()<<"is reConnect0:"<<reConnectFlag;
        startLiveFlag = false;
        sendCmd(1);//tcp连接就启动拧紧机
        socketManage();
    }else{
        qDebug()<<"*connect faile*"<<tcpSocket->errorString();
        QDateTime time2 = QDateTime::currentDateTime();
        if(time1.msecsTo(time2) >= 5000){
            QTimer::singleShot(0,this,SLOT(newConnect()));
        }else{
            QTimer::singleShot(5000-time1.msecsTo(time2),this,SLOT(newConnect()));
        }
    }
}

//掉线重连机制
void tighten_op_wheel::disConnect()
{
    qDebug()<<"tcpSocket disConnect:"<<tcpSocket->errorString();
//    CsIsConnect = false;
//    connectFlag = false;
//    startLiveFlag = false;
//    tcpSocket->deleteLater();
//    newConnect();
}

//控制循环发送数据给拧紧机（心跳）
void tighten_op_wheel::socketManage()
{
    //qDebug()<<"socketManage()"<<startLiveFlag<<connectFlag;
//    qDebug()<<"point[socketManage_0]:";
    int cycleTime = 250;
    countCycle++;
    if(connectFlag){//tcpSocket连接成功
        //拧紧机启动成功 && 有任务已经发送结束 && 5S发一次心跳
        if(startLiveFlag && taskCmdEndFlag && countCycle > 5*1000/cycleTime){
            countCycle = 0;
            sendCmd(9999);//发送心跳
        }
    }else{
        countCycle++;
        if(countCycle > 5*1000/cycleTime){//连接中断超过5S算一次超时
            countCycle = 0;
            onceTimeOut++;
            if(onceTimeOut > 3){//3次超时
                onceTimeOut = 0;
                qDebug() << "heart time out";
                CsIsConnect = false;
                connectFlag = false;
                startLiveFlag = false;
                newConnect();//长时间没有心跳重连
            }

        }
    }
//    qDebug()<<"point[socketManage_1]:";
    QTimer::singleShot(cycleTime,this,SLOT(socketManage()));
}

//发送指令整理
void tighten_op_wheel::sendCmd(int type)
{
    qDebug()<<"sendCmd:"<<type;
    if(9999 == type){//Keep alive message
        writeBuf = "00209999            ";
        writeFunc(writeBuf,type);
    }else{
//        qDebug()<<"sendCmd:"<<type;
        if(taskCmdEndFlag){
            currentMID = type;//记录非心跳任务中的MID
            if(1 == type){//Communication start（拧紧机通信启动）
                writeBuf = "00200001001         ";
            }else if(3 == type){//Communication stop（拧紧机通信终止） 本程序有断线重连机制
                writeBuf = "00200003001         ";
            }else if(5 == type){//Application Communication positive acknowledge(results curve ACK)
                writeBuf = "00240005001         0900";
            }else if(8 == type){//Application data message subscription（订阅）
                if(1 == dataMesSubType){//New curve Angle subscribe 角度曲线订阅
                    writeBuf = "006400080011        0900001350                             01001";
                }else if(2 == dataMesSubType){//New curve Torque subscribe 扭矩曲线订阅
                    writeBuf = "006400080011        0900001350                             01002";
                }else if(3 == dataMesSubType){//角度扭矩曲线订阅
                    writeBuf = "006700080011        0900001350                             02001002";
                }else if(4 == dataMesSubType){//按循环号订阅曲线
                    //missCycle = 195;
                    writeBuf = "005800080011        09000012930000000122000000012202001002";
                    for(int i=0;i<10;i++){
                        int powTen = qPow(10,10-1-i);
                        writeBuf.replace(30+i,1,QByteArray::number((missCycle/powTen)%10));
                        writeBuf.replace(40+i,1,QByteArray::number((missCycle/powTen)%10));
                    }
                }
            }else if(9 == type){//Application Data Message unsubscribe（取消订阅）
                writeBuf = "003400090010        09000010601002";//torque curve unsubscribe（拧紧曲线订阅取消）
            }else if(10 == type){//Parameter set ID upload request（获取程序号列表）
                writeBuf = "00200010001         ";
            }else if(18 == type){//Select Parameter set（选择参数集：程序号）
                writeBuf = "00230018001         001";
                writeBuf[21] = programNO/10 + 0x30;
                writeBuf[22] = programNO%10 + 0x30;
            }else if(19 == type){//Set Parameter set batch size(参数集批量设置)
                writeBuf = "00250019001         00105";
                writeBuf[21] = programNO/10 + 0x30;//设置的哪个程序
                writeBuf[22] = programNO%10 + 0x30;
                writeBuf[23] = boltCount/10 + 0x30;//set bolt number 螺栓个数
                writeBuf[24] = boltCount%10 + 0x30;
            }else if(34 == type){//Job info subscribe（JOB信息订阅）
                writeBuf = "00200034001         ";
            }else if(38 == type){//Select Job（选择JOB）
                writeBuf = "00220038001         "; //Job ID
                writeBuf.append(strJobID.toLatin1());
            }else if(42 == type){//disable（断开使能）
                writeBuf = "00200042001         ";
            }else if(43 == type){//enable（给使能）
                writeBuf = "00200043001         ";
            }else if(50 == type){//Vehicle ID Number download request（VIN码下载请求）
                writeBuf = "00370050            LSVAE45E7EN123456";
                writeBuf.replace(20,17,vinCode.toLatin1());
            }else if(52 == type){//Vehicle ID Number
                writeBuf = "00370052            LSVAE45E7EN123456";
                writeBuf.replace(20,17,vinCode.toLatin1());
            }else if(53 == type){//Vehicle ID Number acknowledge（车辆识别码） 测试该功能不可用
                writeBuf = "00200053001         ";
            }else if(60 == type){//Last tightening result data subscribe（拧紧结果订阅）
                writeBuf = "002000600011        ";
            }else if(62 == type){//Last tightening result data acknowledge（拧紧数据返回） 测试该功能不可用
                writeBuf = "00200062001         ";
            }else if(63 == type){//Last tightening result data unsubscribe（取消拧紧结果订阅）
                writeBuf = "00200063001         ";
            }else if(64 == type){//Old tightening result upload request（历史拧紧结果上传请求）
                writeBuf = "00300064001         0000000000";
                writeBuf.replace(30-tighteningID.size(),tighteningID.size(),tighteningID.toLatin1());
            }else if(70 == type){//Alarm subscribe（警报订阅）
                writeBuf = "00200070001         ";
            }else if(72 == type){//Alarm acknowledge（警报确认）
                writeBuf = "00200072001         ";
            }else if(77 == type){//Alarm status acknowledge（警报状态确认）
                writeBuf = "00200077001         ";
            }else if(82 == type){//Set Time（设置时间）
                writeBuf = "00390082001         2019-10-11:12:01:01";
                QDateTime time = QDateTime::currentDateTime();
                QString strTime = time.toString("yyyy-MM-dd:hh:mm:ss");
                writeBuf.replace(20,19,strTime.toLatin1());
            }else if(105 == type){//Atlas PM Last tightening results data subscribe
                writeBuf = "00200105            ";
            }else if(108 == type){
                writeBuf = "00210108            0";
            }
            writeFunc(writeBuf,type);
        }else{
            waitTask = type;
            QTimer::singleShot(100,this,SLOT(waitSendCmd()));
        }
    }
}

//缓存当前没执行的任务，等前面任务执行完再重新执行
void tighten_op_wheel::waitSendCmd()
{
    qDebug() << "waitSendCmd:"<<waitTask;
    sendCmd(waitTask);
}

//向拧紧机写数据，并获取写后收到的回复
void tighten_op_wheel::writeFunc(QByteArray buf,int type)
{
    qDebug()<<"writeBuf:"<<buf<<tcpSocket;
    taskCmdEndFlag = false;//任务结束了再发下一条指令
    tcpSocket->write(buf,buf.size()+1);
    //qDebug() << "writeEnd:"<<tcpSocket;
    if(tcpSocket->waitForBytesWritten(2*1000)){
        taskCmdEndFlag = true;//任务结束了再发下一条指令
        //qDebug()<<"write success";
    }else{
        qDebug()<<"write error:"<<type<<tcpSocket->errorString();
        taskCmdEndFlag = true;
        sendCmd(type);//未写成功，重新发送MID
    }
}

//提取回复数据的字段
void tighten_op_wheel::readFunc()
{
    QByteArray recBuf = tcpSocket->readAll();
    int revLen = recBuf.size();//整包长度
    int nexoMID = recBuf.mid(4,4).toInt();
    int cmdLen = recBuf.mid(0,4).toInt();//回复数据记录长度
    veceivedData.append(recBuf);//缓存等包接到完整
    QByteArray oneData = "";
    int showLen = 200;
    if(revLen < showLen){
        qDebug()<<"receiveBuf:"<<revLen<<veceivedData.size()<<recBuf;
    }else{
        qDebug()<<"receiveBuf:"<<revLen<<veceivedData.size()<<recBuf.left(showLen);
    }
    //单包直接使用  (曲线无结尾符，长度相等)||(普通回复有结尾符，实际长度+1)
    if((900 == nexoMID && revLen == cmdLen)||(900 != nexoMID && revLen == cmdLen + 1)){
        QByteArray veceivedDataTemp = veceivedData;
        veceivedData.clear();
        receivenormaldata(revLen,cmdLen,nexoMID,veceivedDataTemp);
    }else{//判断veceivedData是多包拆分或者包不完整等接收完成
        int foldLen = 0;//所有包记录长度
        int oneLen = 0;//一个包的记录长度
        //如果拆到当前位置的包记录>实际说明没接收完，清掉继续接收
        //如果拆到当前位置的包==实际 说明刚好拆完，foldList有数据可以发送出去了
        while(foldLen < veceivedData.size()){
            oneLen = veceivedData.mid(foldLen,4).toInt();//第一个包从0开始，如果有多个包，下一个包从前面包结束位置开始
            if(900 == veceivedData.mid(foldLen+4,4).toInt()){
                oneData = veceivedData.mid(foldLen,oneLen);
                if(foldLen+oneLen <= veceivedData.size()){//拆包中当前这条数据是完整的
                    foldList << oneData;
                }else{//包不完整，不存储，继续接收数据
                    foldList.clear();
                    break;
                }
            }else{
                oneData = veceivedData.mid(foldLen,oneLen+1);
                if(foldLen+oneLen <= veceivedData.size()){//拆包中当前这条数据是完整的
                    foldList << oneData;
                }else{//包不完整，不存储，继续接收数据
                    foldList.clear();
                    break;
                }
            }
            foldLen = foldLen+oneData.size();//记录当前节点，下个循环从这里再开始取值
        }
        int foldListSize = foldList.size();
        //qDebug()<<"foldList.size():"<<foldListSize;
        for(int i = 0;i <foldListSize;i++){
            if(foldListSize > 1){//叠包了
                qDebug()<<"foldListVa:"<<foldList.at(i);
            }
            QByteArray data = foldList.at(i);
            receivenormaldata(data.size(),data.mid(0,4).toInt(),data.mid(4,4).toInt(),data);
            if(i == foldList.size()-1){
                veceivedData.clear();//所有数据发完可以把缓存包清掉
                foldList.clear();
            }
        }
    }
}

//解析拧紧机回复的数据（拧紧结果，心跳，普通命令收到回复，曲线等） 过来的都是一条条完整的数据
void tighten_op_wheel::receivenormaldata(int revLen,int cmdLen,int nexoMID,QByteArray recBuf)
{
    if(9999 == nexoMID){
        //qDebug() << "~~~~~~~~~~~~~~heart~~~~~~~~~~~~~";
    }else{
        if((4 == nexoMID || 5 == nexoMID)){//回复成功5/失败4
            int replyMid = recBuf.mid(20,4).toInt();//截取之前发送的指令的MID
            if(5 == nexoMID){
                if(105 == replyMid){//拧紧机收到105的回复
                    //多轴拧紧机收到拧紧结果后订阅曲线
                    newTightenFlag = true;
                    dataMesSubType = 1;
                    sendCmd(8);
                }else if(8 == replyMid){//拧紧机收到正确曲线订阅命令的回复
                    curveNullBuf = "null";
                    if(newTightenFlag){
                        newTightenFlag = false;
                        dataMesSubType = 2;
                        sendCmd(8);
                    }
                }
            }
        }else{//回复成功/失败后再回复的数据类型
            if(2 == nexoMID){//拧紧机启动成功
                if(SYSS != "ING" && SYSS != "OK" && SYSS != "NOK")
                {
                    SYSS = "Ready";
                }
                emit IsTigntenReady(true);
                startLiveFlag = true;
                sendCmd(105);//启动拧紧机成功后订阅拧紧结果
            }else if(65 == nexoMID){
                int tempcycle = recBuf.mid(23,10).toInt();//add 20171228
                qDebug()<<"Old Tightening ID:"<<tempcycle;
            }else if(106 == nexoMID){
                sendCmd(108);
                thghtenID = recBuf.mid(31,9).data();//拧紧循环号
                thghtenID.append("0");
                Q_EMIT signalSendTightenData(recBuf);//拧紧结果数据发出去存储
            }else if(900 == nexoMID){
                sendCmd(5);//收到一条完整的曲线数据，回复一下，好接收下一条
                int TempLen = 57;
                int PID_Len = recBuf.mid(TempLen,3).toInt();//17
                TempLen = TempLen + 12 + PID_Len + 5; //57+12+17+5=91
                PID_Len = recBuf.mid(TempLen,3).toInt();//1
                TempLen = TempLen + 12 + PID_Len + 17;//91+12+1+17=121
                QString CurveNO = recBuf.mid(TempLen,1).data();
                //thghtenID最后一位存和取按对应关系
                QString curveID = thghtenID;
                curveID.replace(9,1,CurveNO);
                QString curveType = recBuf.mid(TempLen+1,2).data();
                //qDebug() << "thiscurveType:"<<curveType;
                if(curveType == "01"){//收到角度曲线
                    receiveCurveA = true;
                    receiveCurveT = false;
                }else if(curveType == "02"){//收到扭矩曲线后接着后面的任务
                    receiveCurveT = true;
                }
                curveConversion(cmdLen,recBuf,curveType,curveID);//转换格式后存文件
            }
        }
    }
}

//处理收到的曲线数据（转换格式后存储）
void tighten_op_wheel::curveConversion(int revFinishLen,QByteArray curveBuf,QString curveType,QString curveID)
{
    int nullCount=0,j=0;
    QString hexBuf;
    for(int i=0;i<revFinishLen;i++){
        if(curveBuf[i] == '\0'){
            nullCount = i + 1;
            hexBuf[0] = '#';
            j = 1;
            break;
        }
    }
    for(int i=nullCount;i<revFinishLen;i++){
        int hByte = (curveBuf[i]&0xf0)>>4;
        int lByte = curveBuf[i]&0x0f;
        if(hByte<10){
            hexBuf[j++] = hByte + '0';
        }else{
            hexBuf[j++] = hByte - 10 + 'a';
        }if(lByte<10){
            hexBuf[j++] = lByte + '0';
        }else{
            hexBuf[j++] = lByte - 10 + 'a';
        }
    }
    if(curveType == "01"){//curve Angle角度
        //qDebug()<< "curve Angle ack:" << idCode;
        QString curveStr = QString(curveBuf.mid(0,nullCount)) + QString(hexBuf);
        curveBufTemp = "*PM"+curveStr+"|"+curveBufTemp;
        //curveToDouble(curveStr);//曲线按格式存储到数据库，不需要转换实际double数据
    }else if(curveType == "02"){ //curve Torque扭矩
        QString curveStr = QString(curveBuf.mid(0,nullCount)) + QString(hexBuf);
        curveBufTemp += curveStr + "}";
    }
    if(receiveCurveT&&receiveCurveA){//2条曲线接收完成
        receiveCurveT = false;
        receiveCurveA = false;
        //tightenResultMap["Curve"] = curveBufTemp;
        //qDebug()<<"sendMysqlSaveCurve";
//        emit sendCurveData(curveBufTemp,curveID);
        if(10 == curveID.size()){
            QString fileName = "/curveFile/" + curveID + ".txt";
            QFile file(fileName);
            if(!file.open(QIODevice::ReadWrite)){
                DTdebug()   << "openCurveFileError:"<<file.errorString();
            }else{
                file.write(curveBufTemp.toUtf8());
                //qDebug()<<"curveBufTemp.clear()";
                curveBufTemp.clear();
                file.close();
            }
        }else{
            qDebug()<<"curveIDError:"<<curveID;
        }
    }
}
