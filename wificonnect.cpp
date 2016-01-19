#include "wificonnect.h"
#include <QDebug>
#include "GlobalVarible.h"

Wificonnect::Wificonnect(QObject *parent) :
    QObject(parent)
{
    countnum = 0;
    number = 0;
    wifiIn = false;
    wifiOut = false;
    countnum_data = 0;
    wifiIn_data = false;
    wifiOut_data = false;
    wificonnect_thread.start();
    this->moveToThread(&wificonnect_thread);
}

void Wificonnect::Wifi_ConnectStart()
{
    qDebug()<<"wificonnect_thread start";
    QObject::connect(&timerwifi,SIGNAL(timeout()),this,SLOT(timerWifi()));
    timerwifi.start(5000);
}

void Wificonnect::timerWifi()
{
    QSettings *configIniRead = new QSettings("/config.ini", QSettings::IniFormat);
    QString IP = configIniRead->value("baseinfo/gateway").toString();
    QString IP2 = configIniRead->value("baseinfo/DataServerIp").toString();
    if( system((QString("ping -w 2 ")+IP+QString(" >/dev/null")).toLocal8Bit().data())!= 0)
    {
        if(!wifiOut)
        {
            countnum++;
            if(countnum == 3)
            {
                qDebug()<<"wifi connect fail";
               // WIFI_STATE  = false;
                emit wifi_connect(false);
                wifiOut = true;
                wifiIn = false;
            }
        }
        number++;
        if(number == 10)
        {
            system("ifconfig wlan0 down");
            system("ifconfig wlan0 up");
            qDebug()<<"restart wlan0";
        }
    }
    else
    {
        number=0;
        if(!wifiIn)
        {
            qDebug()<<"wifi connect success";
            wifiIn =true;
            wifiOut = false;
            //WIFI_STATE  = true;
            emit wifi_connect(true);
            //emit send_unconnect(false);
            countnum = 0;
        }
    }

    if( system((QString("ping -w 2 ")+IP2+QString(" >/dev/null")).toLocal8Bit().data())!= 0)
    {
        if(!wifiOut_data)
        {
            countnum_data++;
            if(countnum_data == 2)
            {
                //wifi ce shi
                WIFI_STATE = false;
            }
            if(countnum_data == 3)
            {
                qDebug()<<"data source connect fail";
                //WIFI_STATE  = false;
                emit data_connect(false);
                wifiOut_data = true;
                wifiIn_data = false;
            }
        }
    }
    else
    {
        if(!WIFI_STATE)
           WIFI_STATE = true;
        if(!wifiIn_data)
        {
            qDebug()<<"data source connect success";
            wifiIn_data =true;
            wifiOut_data = false;
            // WIFI_STATE  = true;
            emit data_connect(true);
            // emit send_unconnect(false);
            countnum_data = 0;
        }
    }
    delete configIniRead;
}
