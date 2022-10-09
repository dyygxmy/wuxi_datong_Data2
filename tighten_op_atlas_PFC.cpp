/**********************************************************************
 * file name  tighten_op_atlas_PFC.c
  describe   ：control enable / program / vin
 *             Last tightening result data subscribe
 *             Last tightening result curve subscribe
 *             Old tightening result upload request
 *
***********************************************************************/
#include "tighten_op_atlas_PFC.h"
#define  DEBUG_OUT
#include <QDebug>

TightenOpAtlasPFC::TightenOpAtlasPFC(QObject *parent) :
    QObject(parent)
{
    powerOnFlag = true;                //data2 restart
    errCount = 0;
    errType = 0;
    programNO = 0;
    boltCount = 0;
    boltNokCount = 0;
    intReadTighteningID = 0;     //current read Tightening form nexo
    intNexoMaxTighteningID = 0;    //nexo Tightening ID
    nexoHandleFlag = 0;
    readOldDataFlag = false;     //read old data
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
    strJobID = "01";
    tighteningID = "";
    curve_AngleTorque = 0;
    curveNullBuf = "null";
    resetJobOffFlag = false;
    angleSubFlag = 0;
    vari_2 = "";
    vari_1 = "";

    m_thread.start();
    this->moveToThread(&m_thread);
}
//线程开始
void TightenOpAtlasPFC::tightenStart()
{
    system("echo 1 > /sys/class/leds/OUTC1/brightness"); //PF disable = 1
    qDebug() << "tighten_op_atlas_PFC thread start !!!"<<vari_1<<vari_2;
    timer5000ms=new QTimer;
    tcpSocket = new QTcpSocket;
    connect(timer5000ms,SIGNAL(timeout()),this,SLOT(timerFunc5000ms()));
    connect(tcpSocket, SIGNAL(readyRead()),this, SLOT(revNexoData()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disConnectDO()));
    newConnects();
    timer5000ms->start(5000);
}
//使能
void TightenOpAtlasPFC::sendReadOperate()
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
        qDebug()<< "************* ISRESET send disable*************";
    }
    else
    {
        if(controlType == "Cleco"){
            system("echo 1 > /sys/class/leds/OUTC1/brightness");
        }
        else {
            system("echo 0 > /sys/class/leds/OUTC1/brightness");
        }

        qDebug()<< "************* send enable *************";
        vinBuf = VIN_PIN_SQL.toLatin1();
        boltNumberBuf = SCREWID_SQL.toLatin1();
//        setNexoTighten(VIN_PIN_SQL.toLatin1(),SCREWID_SQL.toLatin1(),proNum.toShort(),lsNum.toShort(),3);
    }
}

/**************************************/
//nexo alive
/**************************************/
void TightenOpAtlasPFC::timerFunc5000ms()
{
    qDebug() << "op 5000ms tiemr" << nexoLinkOk << nexoHandleFlag << nexoAliveCount;
    if(nexoLinkOk)                   //nexo link
    {
        nexoHandleFlag |= 0x00800000;//Alive
        ctlNexoHandle();             //send CMD to nexo
    }
    else
    {}
    if(nexoAliveCount > 2)             //3 times alive not ack
    {
        nexoAliveCount = 0;
        if(nexoLinkOk )
        {
            emit IsTigntenReady(false);
            nexoLinkOk = false;
        }
        else
        {
            CsIsConnect = false;
            qDebug() << "3 times alive no ack disconnect  ";
            newConnects();
        }
    }
    nexoAliveCount++;
}

/*******************************************************/
//nexo disconnect handle
/*******************************************************/
void TightenOpAtlasPFC::disConnectDO()
{
//    nexoLinkOk = false;
    qDebug() << "OP disconnect 22222222222";
    CsIsConnect = false;
//    newConnects();
}
/*******************************************************/
//nexo bulid connect
/*******************************************************/
void TightenOpAtlasPFC::newConnects()
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
    qDebug() << "PFC the socket state is" << IP_addr << tcpSocket->state();
#endif
    if(tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        qDebug() << "OP link success  >>>>>>>>";
        CsIsConnect = true ;
        nexoAliveCount = 0;
        timer5000ms->stop();
        nexoHandleFlag  = 0x00000001;  //start communication
        ctlNexoHandle();               //send CMD to nexo
        timer5000ms->start(5000);
    }
    else
    {
        CsIsConnect = false;
        nexoLinkOk = false;
        qDebug() << "OP link fail XXXXXXXXXXXX" ;
    }
}

/***********************************/
//处理控制Nexo函数
//len:收到的网络包长度  Rx_Buffer[]:收到的网络包数据  Tx_len:发送网络包长度  Tx_Buffer[]:发送网络包数据
/*************************************/
void TightenOpAtlasPFC::ctlNexoHandle()
{
    short Tx_len = 0;
    QByteArray sendBuf;
    /****************************************/
    /*******system error system ACK**********/
    /****************************************/
    if(nexoHandleFlag&0x10000000)
    {
        nexoHandleFlag &= ~0x10000000;
        Tx_len = 21;
        sendBuf = "00200077001         ";
    }
    /****************************************/
    /*******results data ACK**********/
    /****************************************/
    else if(nexoHandleFlag&0x02000000)
    {
        nexoHandleFlag &= ~0x02000000;
        Tx_len = 21;
        sendBuf = "00200062001         ";
    }
    /****************************************/
    /*******Alarm  ACK**********/
    /****************************************/
    else if(nexoHandleFlag&0x00001000)
    {
        nexoHandleFlag &= ~0x00001000;
        Tx_len = 21;
        sendBuf = "00200072001         ";
    }
    /****************************************/
    /*******results curve ACK**********/
    /****************************************/
    else if(nexoHandleFlag&0x00002000)
    {
        nexoHandleFlag &= ~0x00002000;
        Tx_len = 25;
        sendBuf = "00240005001         0900";
    }
    /****************************************/
    /*******torque curve unsubscribe****************/
    /****************************************/
    else if(nexoHandleFlag&0x00000800)
    {
        nexoHandleFlag &= ~0x00000800;
        Tx_len = 35;
        sendBuf = "003400090010        09000010601002";
    }
    /****************************************/
    /**********communication stop***********/
    /****************************************/
    else if(nexoHandleFlag&0x00000010)
    {
        Tx_len = 21;
        sendBuf = "00200003001         ";
    }
    /****************************************/
    /*communication start 开始通信（启动拧紧机）*/
    /****************************************/
    else if(nexoHandleFlag&0x00000001)
    {
        Tx_len = 21;
        sendBuf = "00200001001         ";
    }
    /****************************************/
    /*********system error messages**********/
    /****************************************/
    else if(nexoHandleFlag&0x20000000)
    {
        Tx_len = 21;
        sendBuf = "00200070001         ";
    }
    /****************************************/
    /*Last tightening results data subscribe*/
    /****************************************/
    else if(nexoHandleFlag&0x01000000)
    {
        Tx_len = 21;
        sendBuf = "002000600011        ";
    }
    /****************************************/
    /*New curve Angle subscribe*/
    /****************************************/
    else if(nexoHandleFlag&0x00008000)
    {
        Tx_len = 65;
        sendBuf = "006400080011        0900001350                             01001";
        //         1234567890123456789012345678901234567890123456789012345678901234
    }
    /****************************************/
    /*New curve Torque subscribe*/
    /****************************************/
    else if(nexoHandleFlag&0x00004000)
    {
        Tx_len = 65;
        sendBuf = "006400080011        0900001350                             01002";
    }
    /****************************************/
    /*********      time set       **********/
    /****************************************/
    else if(nexoHandleFlag&0x40000000)
    {
        Tx_len = 40;
        sendBuf = "00390082001         2015-05-01:12:01:01";
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
        sendBuf = "00300064001         0000000000";
        if(!readMaxTightenIDFlag)
        {
            QByteArray tempBuf = QByteArray::number(intReadTighteningID,10);
            sendBuf.replace(30-tempBuf.size(),tempBuf.size(),tempBuf);
        }
    }
    /****************************************/
    /*********selected program**********/
    /****************************************/
    else if(nexoHandleFlag&0x00000002)
    {
        Tx_len = 24;
        sendBuf = "00230018001         001";
        sendBuf[21] = programNO/10 + 0x30;
        sendBuf[22] = programNO%10 + 0x30;
    }
    /****************************************/
    /*********set bolt number**********/
    /****************************************/
    else if(nexoHandleFlag&0x00000004)
    {
        Tx_len = 26;
        sendBuf = "00250019001         00105";
        sendBuf[21] = programNO/10 + 0x30;
        sendBuf[22] = programNO%10 + 0x30;
        sendBuf[23] = boltCount/10 + 0x30;
        sendBuf[24] = boltCount%10 + 0x30;
    }
    /****************************************/
    /*********      ID code        **********/
    /****************************************/
    else if(nexoHandleFlag&0x00010000)
    {
        Tx_len = 38;
        sendBuf = "00370050            LSVAE45E7EN123456";
        sendBuf.replace(20,17,vinBuf); //replace vincode
    }
    /****************************************/
    /*********      VIN subscribe        **********/
    /****************************************/
    else if(nexoHandleFlag&0x00020000)
    {
        Tx_len = 21;
        sendBuf = "00200051001         ";
    }
    /****************************************/
    /*********      VIN ACK        **********/
    /****************************************/
    else if(nexoHandleFlag&0x00040000)
    {
        nexoHandleFlag &= ~0x00040000;
        Tx_len = 21;
        sendBuf = "00200053001         ";
    }
    /****************************************/
    /******** tool disable**********/
    /****************************************/
    else if(nexoHandleFlag&0x00000200)
    {
        Tx_len = 21;
        sendBuf = "00200042001         ";
    }
    /****************************************/
    /******** tool enable**********/
    /****************************************/
    else if(nexoHandleFlag&0x00000400)
    {
        Tx_len = 21;
        sendBuf = "00200043001         ";
    }
    /****************************************/
    /********** abort job         ***********/
    /****************************************/
    else if(nexoHandleFlag&0x00400000)
    {
        Tx_len = 21;
        sendBuf = "00200127001         ";
    }
    /****************************************/
    /********** Job batch increment***********/
    /****************************************/
    else if(nexoHandleFlag&0x00080000)
    {
        Tx_len = 21;
        sendBuf = "00200128001         ";
    }
    /****************************************/
    /********Job off and off reset**** ******/
    /****************************************/
    else if(nexoHandleFlag&0x00200000)
    {
        Tx_len = 22;
        if(!resetJobOffFlag)
        {
            sendBuf = "00210130001         0";//job off
            resetJobOffFlag = true;
        }
        else
        {
            sendBuf = "00210130001         1";//reset job off
            resetJobOffFlag = false;
        }
    }
    /****************************************/
    /**********   Job select ***********/
    /****************************************/
    else if(nexoHandleFlag&0x00100000)
    {
        Tx_len = 23;
        sendBuf = "00220038001         "; //Job ID
        sendBuf.append(strJobID);
    }
    /****************************************/
    /**********       Alive       ***********/
    /****************************************/
    else if(nexoHandleFlag&0x00800000)//5S send Alive
    {
        nexoHandleFlag &= ~0x00800000;
        Tx_len = 21;
        sendBuf = "00209999001         ";
    }

    /*
     * repair curve
    */
    else if (nexoHandleFlag&0X08000000)
    {
        int size = strCycle.size() ;
        nexoHandleFlag &= ~0x00800000;
        Tx_len = 59 ;
        sendBuf = "005800080011        09000012930000000000000000000202001002" ;
        sendBuf.replace(40-size,size,strCycle.toLatin1());
        sendBuf.replace(50-size,size,strCycle.toLatin1()) ;
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
    qDebug()<< "PFC_send:" << sendBuf;// << "nexoHandleFlag :" << nexoHandleFlag ;
    tcpSocket->write(sendBuf,Tx_len);
    bool Send_Timeout_flag = tcpSocket->waitForBytesWritten(300);//加入300ms超时,防止发送超时阻塞
    qDebug() << "PFC sendbuf  finish!"<<"Send_Timeout_flag:"<<!Send_Timeout_flag;

}
/***********************************/
//处理接受Nexo数据处理函数
//len:收到的网络包长度  Rx_Buffer[]:收到的网络包数据  Tx_len:发送网络包长度  Tx_Buffer[]:发送网络包数据
/*************************************/
void TightenOpAtlasPFC::revNexoData()
{
    int nexoMID;
    int alivelen = 0;
    int nullCount=0,i=0,j=0,k=0;
    int hByte,lByte;
    int revLen,cmdLen;
    QByteArray recBuf,hexBuf;//,hexBufTemp;

    recBuf.clear();
    recBuf = tcpSocket->readAll();
    QString allStr = recBuf;
    int readAllLen = recBuf.size();
    int strlen = allStr.size();
//    qDebug()<<"revNexoAllDataBuf:"<<recBuf<<"buflen:"<<readAllLen;
    qDebug()<<"revNexoAllDataStr:"<<allStr<<"strlen:"<<strlen<<"buflen:"<<readAllLen;

    nexoMID = recBuf.mid(4,4).toInt();
    revLen = recBuf.size();
    cmdLen = recBuf.mid(0,4).toInt();
    if(nexoMID == 900)
    {
        revDataLen   = revLen;
        revFinishLen = cmdLen;
        curveBuf = recBuf;
        curveFirstFlag = 1;
        curveDataFlag = 1;   //receive curve
        idCode_c = "";
    }

    if(revLen == (cmdLen+1))              //length of the same
    {
        //qDebug() <<curveFirstFlag << curveDataFlag << "recevice len:" << revLen << cmdLen << "note:" << recBuf;
        nexoAliveCount = 0;           //recvice nexo data
        receivenormaldata(revLen, cmdLen,nexoMID,recBuf);

    }
    else  if(curveDataFlag == 1)
    {
        //qDebug() <<curveFirstFlag << curveDataFlag << "recevice len:" << revLen << cmdLen<<curveBuf;
        if(curveFirstFlag == 0)
        {
            curveBuf = curveBuf + recBuf;
            revDataLen = revDataLen + revLen;
            qDebug() << "more data:" << curveBuf.size() << revDataLen << revFinishLen;
        }
        if(revDataLen >= (revFinishLen<<1))//curve receive finished
        {
            for(k=0;k<2;k++)
            {
                curveType = curveBuf.mid(56,3).data();
                idCode_c = curveBuf.mid(20,10); //ID code
                qDebug()<< "******curveType*********" <<curveType << idCode_c;
                for(i=0;i<revFinishLen;i++)
                {
                    if(curveBuf[i] == '\0')
                    {
                        nullCount = i + 1;
                        hexBuf[0] = '#';
                        j = 1;
                        break;
                    }
                }
                for(i=nullCount;i<revFinishLen;i++)
                {
                    hByte = (curveBuf[i]&0xf0)>>4;
                    lByte = curveBuf[i]&0x0f;
                    if(hByte<10)
                    {
                        hexBuf[j++] = hByte + '0';
                    }
                    else
                    {
                        hexBuf[j++] = hByte - 10 + 'a';
                    }
                    if(lByte<10)
                    {
                        hexBuf[j++] = lByte + '0';
                    }
                    else
                    {
                        hexBuf[j++] = lByte - 10 + 'a';
                    }
                }
                if(curveType == "050")//1 times angle
                {
                    qDebug()<< "**curve angle** curveType:" <<curveType << idCode_c;
                    if(curve_AngleTorque == 0)//curve is null
                    {
                        curve_AngleTorque = 1;//curve angle
                        curveBufTemp = "*";
                        curveBufTemp.append(curveBuf.mid(0,nullCount));
                        curveBufTemp.append(hexBuf);
                        curveBufTemp.append('|');
                        //                        qDebug()<<"1111111 angle"<<curveBufTemp;

//                        if(vari_2 != "1445")
//                        {
//                                timer5000ms->stop();
                            nexoHandleFlag = 0x00004000;                  //torque subscribe
                            ctlNexoHandle();                              //send CMD to nexo
                            timer5000ms->start(5000);
//                        }
                    }
                    else if(curve_AngleTorque == 2)//curve is torque
                    {
                        curveBufTemp = "*";
                        curveBufTemp.append(curveBuf.mid(0,nullCount));
                        curveBufTemp.append(hexBuf);
                        curveBufTemp.append('|');
                        //                        qDebug()<<"222222 angle"<<recBuf;
                        curveBufTemp.append(curveBufTemp1);
                        if(idCode_c != "")
                        {
                            QString fileName = "/curveFile/" + idCode_c + ".txt";
                            QFile file(fileName);
                            if(!file.open(QIODevice::ReadWrite))
                            {
                                qDebug()   << "Cannot open wifi file2 for Writing";
                            }
                            else
                            {
                                file.write(curveBufTemp.toUtf8());
                                file.close();
                            }
                            curveDataFlag = 0;
                            idCode_c = "";
                            yellow_led(0);//曲线接收完成，黄灯灭
                            qDebug() << "torque_angle curve file path:" <<fileName;//<<curveBufTemp;
                        }
                        else
                        {
                            qDebug() << "idCode_c == null:";
                        }
                    }
                    else
                    {
                        curve_AngleTorque = 0;
                    }
                }
                else if(curveType == "001") //2 times torque
                {
                    qDebug()<< "**curve torque** curveType:" <<curveType << idCode_c;
                    if(curve_AngleTorque == 0)//curve is null
                    {
                        curve_AngleTorque = 2;//curve torque
                        curveBufTemp1 = curveBuf.mid(0,nullCount);
                        curveBufTemp1.append(hexBuf);
                        curveBufTemp1.append('}');
                        //                        qDebug()<<"1111111 torque"<<curveBufTemp1;

//                        if(vari_2 != "1445")
//                        {
//                                timer5000ms->stop();
                            nexoHandleFlag = 0x00008000;                  //angle subscribe
                            ctlNexoHandle();                              //send CMD to nexo
                            timer5000ms->start(5000);
//                        }
                    }
                    else if(curve_AngleTorque == 1)//curve is angle
                    {
                        curveBufTemp.append(curveBuf.mid(0,nullCount));
                        curveBufTemp.append(hexBuf);
                        curveBufTemp.append('}');
                        //                        qDebug()<<"2222222 torque"<<curveBufTemp;
                        if(idCode_c != "")
                        {
                            QString fileName = "/curveFile/" + idCode_c + ".txt";
                            QFile file(fileName);
                            if(!file.open(QIODevice::ReadWrite))
                            {
                                qDebug()   << "Cannot open wifi file2 for Writing";
                            }
                            else
                            {
                                file.write(curveBufTemp.toUtf8());
                                file.close();
                            }
                            curveDataFlag = 0;
                            idCode_c = "";
                            curve_AngleTorque = 0;
                            yellow_led(0);//曲线接收完成，黄灯灭
                            qDebug() << "angle_torque curve file path:" <<fileName;//<<curveBufTemp;
                        }
                        else
                        {
                            qDebug() << "idCode_c == null:";
                        }
                    }
                    else
                    {
                        curve_AngleTorque = 0;
                    }
                }
                else
                {}
                if(k==1)
                {
                    curveBuf = curveBuf.mid(revFinishLen,revFinishLen);
                }
            }
            revDataLen   = 0;
            revFinishLen = 0;
            curveFirstFlag = 0;
        }
        else if(revDataLen >= revFinishLen) //curve receive finished
        {
            curveType = curveBuf.mid(56,3).data();
            idCode_c = curveBuf.mid(20,10); //ID code
            for(i=0;i<revFinishLen;i++)
            {
                if(curveBuf[i] == '\0')
                {
                    nullCount = i + 1;
                    hexBuf[0] = '#';
                    j = 1;
                    break;
                }
            }
            for(i=nullCount;i<revFinishLen;i++)
            {
                hByte = (curveBuf[i]&0xf0)>>4;
                lByte = curveBuf[i]&0x0f;
                if(hByte<10)
                {
                    hexBuf[j++] = hByte + '0';
                }
                else
                {
                    hexBuf[j++] = hByte - 10 + 'a';
                }
                if(lByte<10)
                {
                    hexBuf[j++] = lByte + '0';
                }
                else
                {
                    hexBuf[j++] = lByte - 10 + 'a';
                }
            }
            if(curveType == "050")//1 times angle
            {
                qDebug()<< "**curve angle** curveType:" <<curveType << idCode_c;
                if(curve_AngleTorque == 0)//curve is null
                {
                    curve_AngleTorque = 1;//curve angle
                    curveBufTemp = "*";
                    curveBufTemp.append(curveBuf.mid(0,nullCount));
                    curveBufTemp.append(hexBuf);
                    curveBufTemp.append('|');
                    //                    qDebug()<<"3333333 angle"<<curveBufTemp;
//                    if(vari_2 != "1445")
//                    {
////                            timer5000ms->stop();
                        nexoHandleFlag = 0x00004000;                  //torque subscribe
                        ctlNexoHandle();                              //send CMD to nexo
                        timer5000ms->start(5000);
//                    }
                }
                else if(curve_AngleTorque == 2)//curve is torque
                {
                    curveBufTemp = "*";
                    curveBufTemp.append(curveBuf.mid(0,nullCount));
                    curveBufTemp.append(hexBuf);
                    curveBufTemp.append('|');
                    //                    qDebug()<<"444444 angle"<<curveBufTemp;
                    curveBufTemp.append(curveBufTemp1);
                    if(idCode_c != "")
                    {
                        QString fileName = "/curveFile/" + idCode_c + ".txt";
                        QFile file(fileName);
                        if(!file.open(QIODevice::ReadWrite))
                        {
                            qDebug()   << "Cannot open wifi file2 for Writing";
                        }
                        else
                        {
                            file.write(curveBufTemp.toUtf8());
                            file.close();
                        }
                        curveDataFlag = 0;
                        idCode_c = "";
                        curve_AngleTorque = 0;
                        yellow_led(0);//曲线接收完成，黄灯灭
                        qDebug() << "torque_angle curve file path:" <<fileName;//<<curveBufTemp;
                    }
                    else
                    {
                        qDebug() << "tighteningID == null:";
                    }
                }
                else
                {
                    curve_AngleTorque = 0;
                }
            }
            else if(curveType == "001") //2 times Torque
            {
                qDebug()<< "**curve torque** curveType:" <<curveType << idCode_c;
                if(curve_AngleTorque == 0)//curve is null
                {
                    curve_AngleTorque = 2;//curve torque

                    curveBufTemp1 = curveBuf.mid(0,nullCount);
                    curveBufTemp1.append(hexBuf);
                    curveBufTemp1.append('}');
                    //                    qDebug()<<"3333333 torque"<<curveBufTemp1;
//                    if(vari_2 != "1445")
//                    {
//                            timer5000ms->stop();
                        nexoHandleFlag = 0x00008000;                  //angle subscribe
                        ctlNexoHandle();                              //send CMD to nexo
                        timer5000ms->start(5000);
//                    }
                }
                else if(curve_AngleTorque == 1)//curve is angle
                {
                    curveBufTemp.append(curveBuf.mid(0,nullCount));
                    curveBufTemp.append(hexBuf);
                    curveBufTemp.append('}');
                    if(idCode_c != "")
                    {
                        QString fileName = "/curveFile/" + idCode_c + ".txt";
                        QFile file(fileName);
                        if(!file.open(QIODevice::ReadWrite))
                        {
                            qDebug()   << "Cannot open wifi file2 for Writing";
                        }
                        else
                        {
                            file.write(curveBufTemp.toUtf8());
                            file.close();
                        }
                        curveDataFlag = 0;
                        idCode_c = "";
                        yellow_led(0);//曲线接收完成，黄灯灭
                        qDebug() << "angle_torque curve file path:" <<fileName;//<<curveBufTemp;
                    }
                    else
                    {
                        qDebug() << "idCode_c == null:";
                    }
                }
                else
                {
                    curve_AngleTorque = 0;
                }
            }
            else
            {}
            if(revDataLen > revFinishLen + 21)//more then 1460
            {
                revDataLen = revDataLen - revFinishLen;
                curveBuf   = curveBuf.mid(revFinishLen,revDataLen);
                qDebug() << "&&&& more then 1460&&&&" << revDataLen;
                return;
            }
            else if(revDataLen > revFinishLen)
            {
                qDebug() << "&&&& ++++++ &&&&&&" << curveBuf.mid(revFinishLen , revDataLen-revFinishLen);
            }
            else
            {
                qDebug() << "&& curve receive OK&&&&&";
            }
            revDataLen   = 0;
            revFinishLen = 0;
            curveFirstFlag = 0;
        }
        else
        {
            qDebug() << "88888888888 data length" << revDataLen << revFinishLen;
            curveFirstFlag = 0;
        }
    }
    else
    {
        //qDebug() << "Receive multiple data sticky packets! ";

        if(nexoMID == 9999)//alive message
        {
            alivelen = 21;//alive message length
            nexoMID = recBuf.mid(4+alivelen,4).toInt();
            revLen = recBuf.size() - alivelen;
            cmdLen = recBuf.mid(0+alivelen,4).toInt();
            if(revLen ==(cmdLen+1) )
            {
                recBuf = recBuf.right(revLen);
                receivenormaldata(revLen,cmdLen, nexoMID,recBuf);
            }
            else
                qDebug()<<"Pfc receive data error!";
        }
        else
        {
            qDebug()<<"First data packet not alive,start NexoData!";
            receivenormaldata(revLen,cmdLen, nexoMID,recBuf);
        }
    }
}

void TightenOpAtlasPFC::receivenormaldata(int revLen, int cmdLen, int nexoMID, QByteArray recBuf)
{
    int cmdType;
    int errCode;
    bool okFlag;
    //int revLen,cmdLen;
    QByteArray torqueMax ="";
    QByteArray torqueMin ="";
//    if(recBuf.size() > 60){
//        qDebug()<<"receiveData_s:"<<recBuf.mid(0,60)<<recBuf.size();
//    }else{
//        qDebug()<<"receiveData_l:"<< recBuf << recBuf.size();
//    }

    switch(nexoMID)
    {
    case 4:   //cmd send error         //send CMD to n
        cmdType = recBuf.mid(20,4).toInt();
        errCode = recBuf.mid(24,2).toInt();
        if((cmdType == 50)&&(errCode == 1))
        {
            sendVinFlag = 0;
            qDebug() << "Vehicle ID Number cmd error,invalid data!";
        }
        else
        {
            errCount ++;
            if(errCount > 3)   //over 3 timer no send cmdType
            {
                errCount = 0;
                qDebug() << "nexo cmd error 3 times";
                nexoHandleFlag = 0;
            }
            else
            {
                if((cmdType == 60)&&(errCode == 9))//Last tightening result subscription already exists
                {
                    nexoHandleFlag = 0x40000000;//time set
                    qDebug() << " Last tightening result data subscribe already exists!";
                }
                else
                {
                    //                        经过测试可以发现这里是个bug，发送的命令为空,所以屏蔽
                    //                        timer5000ms->stop();
                    //                        ctlNexoHandle();             //send CMD to nexo
                    //                        timer5000ms->start(5000);
                    qDebug() << "nexo cmd error:" << cmdType << errCode;
                }
            }
        }
        break;
    case 5:  //cmd send ok
        cmdType = recBuf.mid(20,4).toInt();
        errCount = 0;
        switch(cmdType)
        {
        case 8:
        case 900:
            curveNullBuf = "null";
            nexoHandleFlag &= ~0x00008000;  //angle subscribe
            nexoHandleFlag &= ~0x00004000; //torque subscribe
            qDebug()<<"****curveNullBuf*****:"<<curveNullBuf;
            if(angleSubFlag)
            {
                angleSubFlag = 0;
//                if(vari_2 == "1445")
//                {
                                            timer5000ms->stop();
//                    SenddataFlag = 1;
                    nexoHandleFlag = 0x00004000;   //torque subscribe
                    ctlNexoHandle();               //send CMD to nexo
                                            timer5000ms->start(5000);
//                    SenddataFlag = 0;
//                }
            }
            break;
        case 18:     //select program
            //               nexoHandleFlag &= ~0x00000002;
                             timer5000ms->stop();
//            SenddataFlag = 1;
            nexoHandleFlag = 0x00000004;//set bolt number
            ctlNexoHandle();             //send CMD to nexo
                           timer5000ms->start(5000);
//            SenddataFlag = 0;
            break;
        case 19:     //set bolt number
            //               nexoHandleFlag &= ~0x00000004;
                          timer5000ms->stop();
//            SenddataFlag = 1;
            nexoHandleFlag = 0x00000400;//tool enable
            ctlNexoHandle();             //send CMD to nexo
                            timer5000ms->start(5000);
//            SenddataFlag = 0;
            break;
        case 34:
            nexoHandleFlag &= ~0x00400000;//Job info subcrible
            break;
        case 38:
            nexoHandleFlag &= ~0x00100000; //select Job
            //                nexoHandleFlag = 0x00000400; //enable
            break;
        case 39://Job reset
                            timer5000ms->stop();
//            SenddataFlag = 1;
            nexoHandleFlag = 0x00020000;                  //VIN subscribe
            ctlNexoHandle();
                            timer5000ms->start(5000);
//            SenddataFlag = 0;
            break;
        case 42:    //tool disable
            nexoHandleFlag &= ~0x00000200;
            break;
        case 43:    //tool enable
            nexoHandleFlag &= ~0x00000400;
            break;
        case 50:    //vin download
            nexoHandleFlag &= ~0x00010000;
            //                timer5000ms->stop();
            //                nexoHandleFlag = 0x00000002;//select program
            //                ctlNexoHandle();             //send CMD to nexo
            //                timer5000ms->start(5000);
            break;
        case 51:   //vin subscribe
                            timer5000ms->stop();
//            SenddataFlag = 1;
            nexoHandleFlag = 0x00008000;  //angle subscribe
            ctlNexoHandle();
                            timer5000ms->start(5000);
//            SenddataFlag = 0;
            curve_AngleTorque = 3;
            break;
        case 60:    //result subscribe
            angleSubFlag = 1;
                            timer5000ms->stop();
//            SenddataFlag = 1;
            nexoHandleFlag = 0x40000000;//time set
            ctlNexoHandle();             //send CMD to nexo
                            timer5000ms->start(5000);
//            SenddataFlag = 0;
            break;
        case 64:    //read old result
            nexoHandleFlag &= ~0x04000000;

            break;
        case 127:    //abort job
            if(ISRESET)
            {
                ISRESET = false;
                nexoHandleFlag &= ~0x00400000;            //abort job
                //                    nexoHandleFlag = 0x00000200;            //disable
            }
            else
            {
                                    timer5000ms->stop();
//                SenddataFlag = 1;
                nexoHandleFlag = 0x00020000;                  //VIN subscribe
                ctlNexoHandle();
                                    timer5000ms->start(5000);
//                SenddataFlag = 0;
            }
            break;
        case 128:    //Job batch increment
            nexoHandleFlag &= ~0x00080000;            //job batch incerment
            break;
        case 130:    //Job off
            if(!resetJobOffFlag)
            {
                nexoHandleFlag &= ~0x00200000;            //job off
            }
            else
            {
                                    timer5000ms->stop();
//                SenddataFlag = 1;
                nexoHandleFlag = 0x00200000;                //reset job off
                ctlNexoHandle();
                                    timer5000ms->start(5000);
//                SenddataFlag = 0;
            }
            break;
        case 70:    //alarm subscribe
            break;
        case 82:    //set time
                            timer5000ms->stop();
//            SenddataFlag = 1;
            if(vari_1 == "N")
            {
                nexoHandleFlag = 0x00000200;                  //disable
            }
            else if(vari_1 == "T")
            {
                if(vari_2 == "V")
                {
                    nexoHandleFlag = 0x00020000;                  //VIN subscribe
                }
                else
                {
                    nexoHandleFlag = 0x00008000;                  //angle subscribe
                    curve_AngleTorque = 3;
                }
            }
            else
            {
                nexoHandleFlag = 0x00020000;                  //VIN subscribe
            }
            ctlNexoHandle();
                            timer5000ms->start(5000);
            break;
        default:
            break;
        }
        break;
    case 2:
        nexoLinkOk = true;                //communication start OK

        if(Disconnectflag)  //add 20171228
        {
            Disconnectflag = false;
            reconnectflag = true;
            qDebug()<<"OP reconnect success!";
        }

        if(SYSS != "ING" && SYSS != "OK" && SYSS != "NOK")
        {
            SYSS = "Ready";
        }
        emit IsTigntenReady(true);
                    timer5000ms->stop();
        nexoHandleFlag = 0x01000000;//tightening results data subscription
        ctlNexoHandle();             //send CMD to nexo
                    timer5000ms->start(5000);
        break;
    case 9999://应答不显示在PC 测试使用
        break;
    case 71:    //alarm
                   timer5000ms->stop();
        nexoHandleFlag = 0x00001000;
        ctlNexoHandle();            //send CMD to nexo
                    timer5000ms->start(5000);
        break;
    case 76://system error status
                    timer5000ms->stop();
        nexoHandleFlag = 0x10000000;//Status ACK ???????? not nexo ack
        ctlNexoHandle();             //send CMD to nexo
                    timer5000ms->start(5000);
        break;
    case 52:   //vin ack
                    timer5000ms->stop();
        nexoHandleFlag = 0x00040000;                  //VIN ACK
        ctlNexoHandle();
        timer5000ms->start(5000);
        if(recBuf.size() >= 37)
        {
            if(vari_2 == "V")//
            {
                qDebug()<<"*****rev VIN*****QueueAlign**********";
                emit QueueAlign(QString(recBuf.mid(20,17)),false,"VIN");
            }
            else
            {
                if(sendVinFlag)//vin download
                {
                    qDebug()<<"**********vin download**********";
                    sendVinFlag = 0;
                }
                else//read vin
                {
                    qDebug()<<"**********QueueAlign**********";
                    emit QueueAlign(QString(recBuf.mid(20,17)),false,"VIN");
                }
            }
        }
        break;
    case 61://Rev result data
                    timer5000ms->stop();
        nexoHandleFlag = 0x02000000;//result ACK
        ctlNexoHandle();            //send CMD to nexo
        timer5000ms->start(5000);

        yellow_led(1);//收到拧紧数据亮黄灯

//        if(SYSS == "ING")
        {
            revDataLen   = 0;
            revFinishLen = 0;
            curveBuf = "";
            curveBufTemp ="";
            curveBufTemp1 = "";
            curveFirstFlag = 0;
            curveDataFlag = 0;   //receive curve
            idCode_c = "";
            curve_AngleTorque = 0;

            nexoProNO = recBuf.mid(90,3);
            torqueValue = recBuf.mid(140,6);                           //torque value
            torqueValue = QByteArray::number(torqueValue.toDouble()/100);
            angleValue  = recBuf.mid(169,5);                           //angle value
            angleValue = QByteArray::number(angleValue.toDouble());
            tighenTime   = recBuf.mid(176,19);                          //Torque time
            tightenTimeTemp = tighenTime;//临时记录本次的拧紧时间
            tighteningID = recBuf.mid(221,10);                           //Tightening ID 10/08
            LastCycle = tighteningID.toInt();//add 20171228
            torqueMin = recBuf.mid(116,6);       //torque low limit
            torqueMin = QByteArray::number(torqueMin.toDouble()/100);
            torqueMax = recBuf.mid(124,6);       //torque high limit
            torqueMax = QByteArray::number(torqueMax.toDouble()/100);
            intReadTighteningID = tighteningID.toInt(&okFlag,10);
            intNexoMaxTighteningID = intReadTighteningID;
            if(intReadTighteningID == 0)
            {
                qDebug() << "data error ***********intReadTighteningID = 0****************";
                return ;
            }
            if(recBuf[107] == '0')
            {
                nexoResult = "NOK";   //0=tightening NOK ,1=OK
            }
            else
            {
                nexoResult = "OK" ;
                qDebug()<<"maxAndMinSet:"<<bound_enabled;
                if(bound_enabled)
                {
                    QSettings *config = new QSettings("/config_bound.ini", QSettings::IniFormat);
                    double torque_max = config->value("/ProNumber"+QString::number(nexoProNO.toInt())+"/Torque_max").toDouble();
                    double torque_min = config->value("/ProNumber"+QString::number(nexoProNO.toInt())+"/Torque_min").toDouble();
                    double Angle_max = config->value("/ProNumber"+QString::number(nexoProNO.toInt())+"/Angle_max").toDouble();
                    double Angle_min = config->value("/ProNumber"+QString::number(nexoProNO.toInt())+"/Angle_min").toDouble();
                    delete config;
                    qDebug()<<"torAngIni:"<<torque_min<<torque_max<<Angle_min<<Angle_max;
                    if(torque_max == 0)
                    {
                        torque_max = torqueValue.toDouble();
                        torque_min = torqueValue.toDouble();
                    }
                    if(torque_min == 0)
                        torque_min = torqueValue.toDouble();
                    if(Angle_max == 0)
                    {
                        Angle_max = angleValue.toDouble();
                        Angle_min = angleValue.toDouble();
                    }
                    if(Angle_min == 0)
                        Angle_min = angleValue.toDouble();
                    qDebug()<<"torAngChange:"<<torque_min<<torque_max<<Angle_min<<Angle_max
                           <<nexoProNO<<proNum ;
                    if((torqueValue.toDouble()<torque_min) || (torqueValue.toDouble()>torque_max) ||
                            (angleValue.toDouble()<Angle_min) || (angleValue.toDouble() >Angle_max)||
                            (nexoProNO.toInt() != proNum.toInt()) )
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
            qDebug()  << "thightenData:" << tighteningID << nexoProNO << torqueValue << angleValue << nexoResult << tighenTime<<curveNullBuf<<SYSS;
            data_model[0] = QString(tighenTime.mid(0,10));
            data_model[1] = QString(tighenTime.mid(11,8));
            data_model[2] = QString(nexoResult);
            data_model[3] = QString(torqueValue);
            data_model[4] = QString(angleValue);
            data_model[5] = QString(boltNumberBuf);
            data_model[6] = QString(vinBuf);
            data_model[7] = QString(tighteningID);
            data_model[8] = curveNullBuf;
            data_model[9] = QString(nexoProNO);
            data_model[10] = "1";
            emit sendfromworkthread(data_model);//send save SqlThread::sqlinsert
            emit send_mainwindow(QString(torqueValue),QString(angleValue),QString(nexoResult));
        }
        break;
    case 900:
        revDataLen   = revLen;
        revFinishLen = cmdLen;
        curveBuf = recBuf;
        curveFirstFlag = 1;
        curveDataFlag = 1;   //receive curve
        idCode_c = "";
        break;
    case 65:
    {
        int tempcycle = recBuf.mid(23,10).toInt();//add 20171228
        qDebug()<<"Old Tightening ID:"<<tempcycle;
        if(reconnectflag)
        {
            reconnectflag = false;
            if((tempcycle-LastCycle)>0)
            {
                qDebug()<<"TightenOpAtlasPFC data missed "<<tempcycle-LastCycle;
            }
            else
            {
                qDebug()<<"TightenOpAtlasPFC data not missed ";
            }
        }
    }
        break;
    default:
        break;
    }
}

void TightenOpAtlasPFC::slotRepairCurve(QString cycle)
{
    if(nexoLinkOk){
        strCycle = cycle ;
        nexoHandleFlag = 0x08000000 ;
        ctlNexoHandle();
    }
}


void TightenOpAtlasPFC::yellow_led(int leds)
{
    if(leds){
        system("echo 1 > /sys/class/leds/control_led4/brightness");
        qDebug()<<"open yellow led[1]";
    }
    else{
        QTimer::singleShot(100,this,SLOT(slotCloseYellowLED()));
    }
}

void TightenOpAtlasPFC::slotCloseYellowLED()
{
    qDebug()<<"close yellow led[0]";
    system("echo 0 > /sys/class/leds/control_led4/brightness");
}
