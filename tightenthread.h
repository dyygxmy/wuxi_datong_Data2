#ifndef TIGHTENTHREAD_H
#define TIGHTENTHREAD_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QMutex>
#include <QMutexLocker>
#include "GlobalVarible.h"
#include <QtNetwork>
#include <QTime>
#include "serialcom.h"
#include <QFile>
#include <QTextStream>
#include <qextserial/qextserialport.h>

class TightenThread : public QObject
{
    Q_OBJECT
public:
    explicit TightenThread(QObject *parent = 0);


    
signals:
    void IsTigntenReady(bool);
    void ReconnectSendOperate();
    void send_mainwindow(QString,QString,QString);
    void sendfromworkthread(QString *);
public slots:
    void tightenStart();
    void slot_read_com3();
    void sendReadOperate();
    void readGWKResult(QString buf);
private:
    QThread m_thread;
    QextSerialPort *myCom3;
//    SerialCom *myCom3;
//    int SerFd;
    QString timeValue;
    QString torqueValue;
    QString angleValue;
    QString gwkStatus;
    QTimer  coms;
//    char Buf[500];
    QString data_model[11];
    QString controlType;
//    char gwkResultBuf[200];
    QByteArray gwkResultBuf;
    int  gwkResultLen;
    int  boltOkNum;
    int  boltNokNum;
    int  programNO;
    int  boltNumOk;
    int  boltNumNok;

    QString debugBuf;
    QString strTime;
    QTimer  dataTimer;
    QDateTime cur_time;

};

#endif // TIGHTENTHREAD_H
