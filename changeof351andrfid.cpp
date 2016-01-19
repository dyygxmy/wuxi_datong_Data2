#include "changeof351andrfid.h"
#include "GlobalVarible.h"
#include <QStringList>
#include <unistd.h>
Changeof351AndRfid::Changeof351AndRfid(QObject *parent) :
    QObject(parent)
{
    serialNums = "";
    flag_l = false;
    bzero(&buff,sizeof(buff));
    codeUsing = false;
    m_thread.start();
    this->moveToThread(&m_thread);
}

void Changeof351AndRfid::newConnect()
{
    m_pTcpSocket->abort(); //取消已有的连接
    //连接到主机，这里从界面获取主机地址和端口号
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    QString l_strHostIp(config->value("baseinfo/RfidIp").toString()),l_strHostPort(config->value("baseinfo/RfidPort").toString());
    m_pTcpSocket->connectToHost(l_strHostIp,l_strHostPort.toInt());
    m_pTcpSocket->waitForConnected();
    //qDebug() << " the socket state is " << m_pTcpSocket->state();
    if(m_pTcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        RFIDISConnect = true;
    }else
    {

        //ui->pushButton->setText("NOK");
    }


}
void Changeof351AndRfid::receivemss()
{
    QByteArray a =  m_pTcpSocket->readAll();
    QString hex = QString(a);
    QByteArray ret;
    QString &org = hex;
    hex=hex.trimmed();
    int n =2;
    int size= org.size();
    int space= qRound(size*1.0/n+0.5)-1;
    if(space<=0)
        return ;
    for(int i=0,pos=n;i<space;++i,pos+=(n+1))
    {
        org.insert(pos,' ');
    }

    QStringList sl=hex.split(" ");
    foreach(QString s,sl)
    {
        if(!s.isEmpty())
            ret.append((char)s.toInt(0,16)&0xFF);
    }
    QString pin = QString(ret);

    QString temppin = pin.mid(2,14);
    QString tempG9  = pin.mid(16,2);
    isequeal = false;

    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);

    if(temppin.length() == 14)
    {

        for(int i = 1;i<11;i++)
        {
            QString tmp = config->value(QString("vininfo/info").append(QString::number(i))).toString();
            int x = QString::compare(temppin, tmp, Qt::CaseSensitive);
            if(!x)
            {
                isequeal = true;
                break;
            }
        }
    }
    if((!isequeal) && (temppin.length() == 14))
    {

        int tmp = config->value(QString("vininfo/insertwhich")).toInt();


        config->setValue(QString("vininfo/info").append(QString::number(tmp)),temppin);
        if(10 == tmp)
        {
            tmp = 1;
        }else
        {
            tmp++;
        }
        config->setValue(QString("vininfo/insertwhich"),QString::number(tmp));
    }

    delete config;
    emit serialCom(temppin,isequeal,tempG9);

}
void Changeof351AndRfid::slot_read_com()
{
    //从串口中读取数据
    int  nTmp = serial_Com.read_datas_tty(Ser_Fd, buff, 200, 20);
  // qDebug() << "nTmp come in " << nTmp;
    if(nTmp > 0)
    {
        flag_l = true;
        serialNums = serialNums+QString(QLatin1String(buff));
        nTmp=0;
    }
    else
    {
        if(flag_l)
            nTmp = 10;
        else
            nTmp = 0;
        flag_l = false;
    }
    bzero(&buff,sizeof(buff));
    //  qDebug() << "serialNums" << serialNums << serialNums.size();
    if (0 < nTmp && serialNums.size() < 22 && serialNums.size() > 13)
    {
        serialNums = serialNums.mid(0,17);
       qDebug() << "serialNumsnn" ;
        if(DebugMode)
        {
            emit sendSerial(serialNums.mid(0,17));
        }
       //  qDebug() << serialNums << serialNums.size() << serialNums.mid(16,1);
         qDebug()<< CsIsConnect << ISmaintenance << SYSS;
        if(CsIsConnect && !ISmaintenance  && SYSS!="ING")
        {
            qDebug() << "fdfdfdfdfdfdf";
            isequeal = false;
            QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
            if(serialNums.mid(0,1) =="L")
            {
                if(serialNums.length() == 17)
                {
                    if(SerialGunMode)
                    {
                        system("echo 1 > /sys/class/leds/control_uart2/brightness");
                    }
                    for(int i = 1;i<11;i++)
                    {
                        QString tmp = config->value(QString("vininfo/info").append(QString::number(i))).toString();
                        int x = QString::compare(serialNums, tmp, Qt::CaseSensitive);
                        if(!x)
                        {
                            isequeal = true;
                            break;
                        }
                    }
                }
                if((!isequeal) && (serialNums.length() == 17))
                {
                    int tmp = config->value(QString("vininfo/insertwhich")).toInt();
                    config->setValue(QString("vininfo/info").append(QString::number(tmp)),serialNums);
                    if(10 == tmp)
                    {
                        tmp = 1;
                    }else
                    {
                        tmp++;
                    }
                    config->setValue(QString("vininfo/insertwhich"),QString::number(tmp));
                }
            }
            delete config;

            if(serialNums.mid(0,1)=="L" && codeUsing)
            {
                sendMSG = serialNums;
               emit serialCom(serialNums,isequeal," ");
               qDebug() << "sdfsdfsdf2";
            }
            if(serialNums.mid(0,1)=="L" && !codeUsing)
            {
                if(!isequeal)
                {
                    codeUsing = true;
                    sendMSG = serialNums;
                    emit serialCom(serialNums,isequeal," ");
                }
                else
                {
                  emit serialCom(serialNums,isequeal," ");
                  serialNums = "";
                }
               qDebug() << "sdfsdfsdf1";
            }
            qDebug() << serialNums << serialNums.mid(0,1) << codeUsing;
            if(serialNums.mid(0,1)!="L" && codeUsing)
            {
                serialNums = sendMSG+"  "+serialNums.mid(11,2);
                qDebug() << "sdfsdfsdf3" << serialNums << serialNums.size();
                emit serialCom(serialNums,false," ");
                codeUsing = false;
            }
        }
            serialNums.clear();
    }

}

void Changeof351AndRfid::comInit()
{
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    for(int i = 1;i< 11;i++)
    {
        config->setValue(QString("vininfo/info").append(QString::number(i)),"");
    }
    config->setValue("vininfo/insertwhich",1);
    isRFID  = config->value("baseinfo/isRFID").toInt();
    delete config;
    if(isRFID)
    {
        m_pTcpSocket = new QTcpSocket;
        newConnect();
        connect(m_pTcpSocket,SIGNAL(readyRead()),this,SLOT(receivemss()));
    }
    else
    {
        Ser_Fd = open(TTYMX0, O_RDWR|O_NOCTTY|O_NDELAY);
        if (0 < Ser_Fd)
        {
            serial_Com.set_opt(Ser_Fd, BAUD_9600, DATA_BIT_8, PARITY_NONE, STOP_BIT_1);//设置串口参数
        }
        else
        {
            qDebug() << "serial open fail";
        }
        connect(&comsTimer,SIGNAL(timeout()),this,SLOT(slot_read_com()));
        comsTimer.start(200);
    }
}
