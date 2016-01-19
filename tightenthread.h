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
    void slot_read_com();
    void sendReadOperate();
    void readGWKResult(QString buf);
private:
    QThread m_thread;
    SerialCom *myCom;
    int SerFd;
    QString timeValue;
    QString torqueValue;
    QString angleValue;
    QString gwkStatus;
    QTimer  coms;
    char Buf[100];
    QString data_model[11];
    char gwkResultBuf[100];
    int  gwkResultLen;
    int  boltOkNum;
    int  boltNokNum;
    int  programNO;
    int  boltNumOk;
    int  boltNumNok;



};

#endif // TIGHTENTHREAD_H
