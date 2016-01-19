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
    bzero(&gwkResultBuf, sizeof(gwkResultBuf));
    SerFd= -1;
    m_thread.start();
    this->moveToThread(&m_thread);
}
//线程开始
void TightenThread::tightenStart()
{
    myCom = new SerialCom;
    SerFd = open(TTYMX3, O_RDWR|O_NOCTTY|O_NDELAY);
    if (0 < SerFd)
    {
        myCom->set_opt(SerFd, BAUD_9600, DATA_BIT_8, PARITY_NONE, STOP_BIT_1);//设置串口参数
        connect(&coms,SIGNAL(timeout()),this,SLOT(slot_read_com()));
        coms.start(300);
        SYSS = "Ready";
        emit  IsTigntenReady(true);
        CsIsConnect = true;
    }
    else
    {
        IsTigntenReady(false);
    }
    qDebug() << "SerFd" <<SerFd ;
    system("echo 0 > /sys/class/leds/OUTC1/brightness"); //Cleco disalbe tool
}
void TightenThread::slot_read_com()
{
    //从串口中读取数据
    bzero(&Buf, sizeof(Buf));
    int  nTmp = myCom->read_datas_tty(SerFd, Buf, 100, 100);
    if (nTmp > 0)
    {
        printf("rcv len=%d,data:%s\n",nTmp,Buf);
        if((Buf[0] == 0x42)&&(Buf[nTmp-1] == 0x0A)) //receive finished
        {
            memcpy(gwkResultBuf,Buf,68);
            readGWKResult(QString(gwkResultBuf));
            bzero(&gwkResultBuf, sizeof(gwkResultBuf));
            gwkResultLen = 0;
//            qDebug() << "11111111111";
        }
        else if(Buf[0] == 0x42)//start reveive
        {
            gwkResultLen = nTmp;
            memcpy(gwkResultBuf,Buf,gwkResultLen);
        }
        else if(Buf[nTmp-1] == 0x0A)//reveive finished
        {
            if(gwkResultLen>0)
            {
                memcpy((char *)&gwkResultBuf[gwkResultLen],Buf,nTmp);
                readGWKResult(QString(gwkResultBuf));
                bzero(&gwkResultBuf, sizeof(gwkResultBuf));
                gwkResultLen = 0;
//                qDebug() << "2222222222";
            }
        }
        else
        {
            if(gwkResultLen > 0)
            {
                memcpy((char *)&gwkResultBuf[gwkResultLen],Buf,nTmp);
                gwkResultLen += nTmp;
            }
        }
    }
}

void TightenThread::sendReadOperate()
{
    if(ISRESET)
    {
        system("echo 0 > /sys/class/leds/OUTC1/brightness"); //Cleco disalbe tool
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
    if(programNO < 17)
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
                system("echo 1 > /sys/class/leds/OUTD5/brightness"); //Cleco Input5 1
            }
            else
            {
                system("echo 0 > /sys/class/leds/OUTD5/brightness"); //Cleco Input5 0
            }
            system("echo 1 > /sys/class/leds/OUTC1/brightness"); //Cleco enable tool
        }
        else
        {
            system("echo 0 > /sys/class/leds/OUTC1/brightness"); //Cleco disable tool
            system("echo 0 > /sys/class/leds/OUTC0/brightness"); //Cleco Input1 0
            system("echo 0 > /sys/class/leds/OUTD7/brightness"); //Cleco Input2 0
            system("echo 0 > /sys/class/leds/OUTD6/brightness"); //Cleco Input3 0
            system("echo 0 > /sys/class/leds/OUTD5/brightness"); //Cleco Input5 0
        }
    }
    else
    {
//        qDebug() << "1111 tool disable";
        system("echo 0 > /sys/class/leds/OUTC1/brightness"); //Cleco disalbe tool
        system("echo 0 > /sys/class/leds/OUTC0/brightness"); //Cleco Input1 0
        system("echo 0 > /sys/class/leds/OUTD7/brightness"); //Cleco Input2 0
        system("echo 0 > /sys/class/leds/OUTD6/brightness"); //Cleco Input3 0
        system("echo 0 > /sys/class/leds/OUTD5/brightness"); //Cleco Input5 0
    }

    }
}

void TightenThread::readGWKResult(QString buf)
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
    qDebug() << "okValue" << okValue << "nokValue "<< nokValue << "buf" << buf;
   // qDebug() << "JJJJJJJJJJJ" << buf.mid(61,1);
    timeValue   = buf.mid(5,12);
    torqueValue = buf.mid(17,7);
    angleValue  = buf.mid(39,7);
    gwkStatus   = buf.mid(61,1);
    if((gwkStatus == "A")&&(okValue == 0))
    {
        gwkStatus = "OK";
        boltOkNum ++ ;
 //       qDebug() << boltNumOk  << boltOkNum << "999999999999999999";
        if(boltNumOk == boltOkNum)
        {
 //           qDebug() << boltNumOk  << boltOkNum << "888888888888888888";
            system("echo 0 > /sys/class/leds/OUTC1/brightness"); //Cleco disalbe tool
        }
    }
    else
    {
        gwkStatus = "NOK";
        boltNokNum ++;
    }
//    qDebug() << timeValue;
//    qDebug() << "torquevalue" << torqueValue;
//    qDebug() << angleValue;
    torqueValue = QString::number(torqueValue.toDouble());
    angleValue  = QString::number(angleValue.toDouble());
    QString DateS = "";
    QString TimeS = "";
    DateS = DateS+"20"+timeValue.mid(0,2)+":"+timeValue.mid(2,2)+":"+timeValue.mid(4,2);
    TimeS = TimeS+timeValue.mid(6,2)+":"+timeValue.mid(8,2)+":"+timeValue.mid(10,2);
//     qDebug() << DateS << TimeS;
    data_model[0] = DateS;
    data_model[1] = TimeS;
    data_model[2] = gwkStatus;
    data_model[3] = torqueValue;
    data_model[4] = angleValue;
    data_model[5] = SCREWID_SQL;
    data_model[6] = VIN_PIN_SQL.mid(0,17);
    data_model[7] = VIN_PIN_SQL.mid(19,2);
    data_model[8] = "NULL";
    data_model[9] = proNum;
    data_model[10] = "1";
    qDebug() << torqueValue;
    qDebug() << angleValue;
    qDebug() << gwkStatus;
    qDebug() << proNum;
    emit send_mainwindow(torqueValue,angleValue,gwkStatus);
    emit sendfromworkthread(data_model);


}
