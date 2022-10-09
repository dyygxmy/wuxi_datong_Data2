#include "tightenthread.h"

TightenThread::TightenThread(QObject *parent) :
    QObject(parent)
{
    gwkResultLen= 0;
    boltNokNum = 0;
    boltOkNum  = 0;
    programNO = 0;
    boltNumOk = 0;
    boltNumNok= 0;
    gwkResultBuf.clear();
    m_thread.start();
    this->moveToThread(&m_thread);
}
//线程开始
void TightenThread::tightenStart()
{
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    controlType = config->value("/baseinfo/controlType").toString();
    delete config;

    QString portName = "ttymxc3";   //获取串口名
    myCom3 = new QextSerialPort("/dev/" + portName);
    connect(myCom3, SIGNAL(readyRead()), this, SLOT(slot_read_com3()));
    //设置波特率
    myCom3->setBaudRate((BaudRateType)2400);

    //设置数据位
    myCom3->setDataBits((DataBitsType)8);

    //设置校验
    myCom3->setParity(PAR_NONE);

    //设置停止位
    myCom3->setStopBits(STOP_1);

    //设置数据流控制
    myCom3->setFlowControl(FLOW_OFF);
    //设置延时
    myCom3->setTimeout(20);

    if(myCom3->open(QIODevice::ReadWrite))
    {
        qDebug()<<"serial com3 open ok " << portName;
        SYSS = "Ready";
        emit  IsTigntenReady(true);
        CsIsConnect = true;

    }else
    {
        qDebug()<<"serial com3 open fail " << portName;
        emit IsTigntenReady(false);
        CsIsConnect = false;
    }
#if 0
    system("echo 0 > /sys/class/leds/OUTC1/brightness"); //Cleco disalbe tool
#else
    if(controlType == "Cleco"){
        system("echo 0 > /sys/class/leds/OUTC1/brightness");
    }
    else {
        system("echo 1 > /sys/class/leds/OUTC1/brightness");
    }
#endif
}
void TightenThread::slot_read_com3()
{
    //从串口中读取数据
    QByteArray revBuf;
    int revLen;
    revLen = myCom3->bytesAvailable();
    revBuf = myCom3->readAll();
    if (revLen > 0)
    {        
        gwkResultBuf.append(revBuf);
        while( (!gwkResultBuf.isEmpty())&&(!gwkResultBuf.startsWith("B")) )
        {
            qDebug()<< "1111111 cleol " << revBuf <<gwkResultBuf;
            gwkResultBuf.replace(0,1,"");
        }
        if(gwkResultBuf.size() >= 68)
        {
            qDebug() << "len:" << gwkResultBuf.size() <<"cleco data:" << gwkResultBuf;
            if(gwkResultBuf.startsWith("B"))
            {
                if( (QString(gwkResultBuf.mid(66,1)) == "\x0D")&&(QString(gwkResultBuf.mid(67,1)) == "\x0A") )
                {
                    readGWKResult(QString(gwkResultBuf));
                    if(gwkResultBuf.size() > 68)
                    {
                        gwkResultBuf.replace(0,68,"");  //clear 68
                        qDebug() << "&&&&&&&&& data len error &&&&&&&&&&";
                    }
                    else
                    {
                        gwkResultBuf.clear();
                    }
                }
                else
                {
                    qDebug() << "33 cleco error 33"  << gwkResultBuf;
                    gwkResultBuf.clear();
                }
            }
            else
            {
                qDebug()<< "cleol error"<<gwkResultBuf;
            }
        }
        else
        {
            if(gwkResultBuf.size() == 1)
            {
                qDebug() <<"first cleco data:" << gwkResultBuf;
            }
        }
    }
}

void TightenThread::sendReadOperate()
{
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    controlType = config->value("/baseinfo/controlType").toString();
    delete config;

    if(ISRESET)
    {
#if 0
        system("echo 0 > /sys/class/leds/OUTC1/brightness"); //Cleco disalbe tool
#else
        if(controlType == "Cleco"){
            system("echo 0 > /sys/class/leds/OUTC1/brightness");
        }
        else {
            system("echo 1 > /sys/class/leds/OUTC1/brightness");
        }
#endif
        system("echo 0 > /sys/class/leds/OUTC0/brightness"); //Cleco Input1 0
        system("echo 0 > /sys/class/leds/OUTD7/brightness"); //Cleco Input2 0
        system("echo 0 > /sys/class/leds/OUTD6/brightness"); //Cleco Input3 0
        system("echo 0 > /sys/class/leds/OUTD5/brightness"); //Cleco Input5 0

        ISRESET = false;
    }
    else
    {
        boltOkNum = 0;
        boltNokNum = 0;

        programNO = proNum.toInt();
        boltNumOk = lsNum.toInt();
        boltNumNok= 3;// no ok count
        //    if(programNO < 17)
        if(1)
        {
            //        qDebug() << "tool enable"<< "programNO" << programNO ;
            if(programNO > 0)
            {
                programNO -= 1;
                if(programNO & 0x01)//
                {
                    system("echo 1 > /sys/class/leds/OUTC0/brightness"); //Cleco Input1 1
                }
                else
                {
                    system("echo 0 > /sys/class/leds/OUTC0/brightness"); //Cleco Input1 0
                }
                if(programNO & 0x02)
                {
                    system("echo 1 > /sys/class/leds/OUTD7/brightness"); //Cleco Input2 1
                }
                else
                {
                    system("echo 0 > /sys/class/leds/OUTD7/brightness"); //Cleco Input2 0
                }
                if(programNO & 0x04)
                {
                    system("echo 1 > /sys/class/leds/OUTD6/brightness"); //Cleco Input3 1
                }
                else
                {
                    system("echo 0 > /sys/class/leds/OUTD6/brightness"); //Cleco Input3 0
                }

                if(programNO & 0x08)
                {
                    system("echo 1 > /sys/class/leds/OUTD5/brightness"); //Cleco Input4 1
                }
                else
                {
                    system("echo 0 > /sys/class/leds/OUTD5/brightness"); //Cleco Input4 0
                }
#if 0
                system("echo 1 > /sys/class/leds/OUTC1/brightness"); //Cleco enable tool
#else
                if(controlType == "Cleco"){
                    system("echo 1 > /sys/class/leds/OUTC1/brightness"); //Cleco enable tool
                }
                else {
                    system("echo 0 > /sys/class/leds/OUTC1/brightness");
                }
#endif
            }
            else
            {
#if 0
                system("echo 0 > /sys/class/leds/OUTC1/brightness"); //Cleco disable tool
#else
                if(controlType == "Cleco"){
                    system("echo 0 > /sys/class/leds/OUTC1/brightness");
                }
                else {
                    system("echo 1 > /sys/class/leds/OUTC1/brightness");
                }
#endif
                system("echo 0 > /sys/class/leds/OUTC0/brightness"); //Cleco Input1 0
                system("echo 0 > /sys/class/leds/OUTD7/brightness"); //Cleco Input2 0
                system("echo 0 > /sys/class/leds/OUTD6/brightness"); //Cleco Input3 0
                system("echo 0 > /sys/class/leds/OUTD5/brightness"); //Cleco Input5 0
            }
        }
    }
}

void TightenThread::readGWKResult(QString buf)
{
    if(SYSS == "ING")
    {
        int okValue,nokValue;
        QFile cleco1("/sys/class/gpio/gpio147/value"); //cleco OK
        QFile cleco2("/sys/class/gpio/gpio176/value"); //cleco NOK
        cleco1.open(QIODevice::ReadOnly);
        cleco2.open(QIODevice::ReadOnly);
        QTextStream in1(&cleco1);
        QTextStream in2(&cleco2);
        in1 >> okValue;
        in2 >> nokValue;
        cleco1.close();
        cleco2.close();
        timeValue   = buf.mid(5,12);
        torqueValue = buf.mid(17,7);
        angleValue  = buf.mid(39,7);
        gwkStatus   = buf.mid(61,1);
//        qDebug() << "okValue" << okValue << "nokValue "<< nokValue << "gwkStatus" << gwkStatus;
        if((gwkStatus == "A")&&(okValue == 0))
        {
            gwkStatus = "OK";
        }
        else
        {
            gwkStatus = "NOK";
        }
        torqueValue = QString::number(torqueValue.toDouble());
        angleValue  = QString::number(angleValue.toDouble());
        QString DateS = "";
        QString TimeS = "";
        DateS = DateS+"20"+timeValue.mid(0,2)+":"+timeValue.mid(2,2)+":"+timeValue.mid(4,2);
        TimeS = TimeS+timeValue.mid(6,2)+":"+timeValue.mid(8,2)+":"+timeValue.mid(10,2);
        //     qDebug() << DateS << TimeS;
        intDataMID++;
        QString strMid = QString::number(intDataMID);
/*************************************************/
//        cur_time = QDateTime::currentDateTime();
//        strTime = cur_time.toString("yyyy-MM-dd:hh:mm:ss.zzz");
//        DateS = strTime.mid(0,10);
//        TimeS = strTime.mid(11,8);
/*************************************************/

        if(gwkStatus == "OK")
        {
            if(bound_enabled)
            {

                QSettings *config = new QSettings("/config_bound.ini", QSettings::IniFormat);
                double torque_max = config->value("/ProNumber"+proNum+"/Torque_max").toDouble();
                double torque_min = config->value("/ProNumber"+proNum+"/Torque_min").toDouble();
                double Angle_max = config->value("/ProNumber"+proNum+"/Angle_max").toDouble();
                double Angle_min = config->value("/ProNumber"+proNum+"/Angle_min").toDouble();
                delete config;
//                qDebug() <<"bound_en" << bound_enabled  << torque_max<<torque_min <<Angle_max<< Angle_min;
                if(torque_max == 0)
                {
//                    qDebug() <<"bound_en1";
                    torque_max = torqueValue.toDouble();
                    torque_min = torqueValue.toDouble();
                }
                if(torque_min == 0)
                    torque_min = torqueValue.toDouble();
                if(Angle_max == 0)
                {
//                     qDebug() <<"bound_en2";
                    Angle_max = angleValue.toDouble();
                    Angle_min = angleValue.toDouble();
                }
                if(Angle_min == 0)
                    Angle_min = angleValue.toDouble();
                if((torqueValue.toDouble()<torque_min) || (torqueValue.toDouble()>torque_max) ||
                        (angleValue.toDouble()<Angle_min) || (angleValue.toDouble() >Angle_max))
                {
//                     qDebug() <<"bound_en3";
                    gwkStatus = "NOK";
                }
            }
        }

        if(gwkStatus == "OK")
        {
            boltOkNum ++ ;
            if(boltNumOk == boltOkNum)
            {
//                system("echo 0 > /sys/class/leds/OUTC1/brightness"); //Cleco disalbe tool
            }
        }
        else
        {
            boltNokNum ++;
        }

        data_model[0] = DateS;
        data_model[1] = TimeS;
        data_model[2] = gwkStatus;
        data_model[3] = torqueValue;
        data_model[4] = angleValue;
        data_model[5] = SCREWID_SQL;
        data_model[6] = VIN_PIN_SQL.mid(0,17);
        data_model[7] = strMid;
        data_model[8] = "NULL";
        data_model[9] = proNum;
        data_model[10] = "1";
        qDebug() << torqueValue;
        qDebug() << angleValue;
        qDebug() << gwkStatus;
        qDebug() << strMid;
        emit send_mainwindow(torqueValue,angleValue,gwkStatus);
        emit sendfromworkthread(data_model);
    }
    else
    {
        qDebug() << "not ING receive data!!";
    }
}
