#ifndef CHANGEOF351ANDRFID_H
#define CHANGEOF351ANDRFID_H

#include <QObject>
#include <QThread>
#include <QtNetwork>
#include <QDebug>
#include "serialcom.h"

class Changeof351AndRfid : public QObject
{
    Q_OBJECT
public:
    explicit Changeof351AndRfid(QObject *parent = 0);
    
signals:
    void serialCom(QString,bool,QString);
    void sendSerial(QString);
public slots:
    void comInit();
    void receivemss();
    void newConnect();
    void slot_read_com0();

private:
    QThread m_thread;
    QTcpSocket *m_pTcpSocket;
    SerialCom serial_Com;      //串口类
    QTimer comsTimer;
    QString serialNums;
    QString sendMSG;
    char buff[20];
    bool flag_l;
    int Ser_Fd;               //串口文件描述符
    bool isequeal;
    bool codeUsing;
};

#endif // CHANGEOF351ANDRFID_H
