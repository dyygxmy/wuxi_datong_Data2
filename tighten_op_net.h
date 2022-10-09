#ifndef TIGHTEN_OP_NET_H
#define TIGHTEN_OP_NET_H


#include <QObject>
#include <QThread>
#include "GlobalVarible.h"
#include <QtNetwork>
#include <QDateTime>
class TightenOpNet : public QObject
{
    Q_OBJECT
public:
    explicit TightenOpNet(QObject *parent = 0);

signals:
    void sendfromworkthread(QString *);
    void send_mainwindow(QString,QString,QString);
    void IsTigntenReady(bool);
    void sendconfigwarning(bool);//跳过螺栓
private:
    QThread m_thread;
    QTcpSocket *tcpSocket;
    QTimer *timer5000ms;
    QTimer *timerMs;
    bool oldTightenRedly;//收到按拧紧ID请求的结果
    int timeOut1;
    QStringList tightenResultTempList;//临时存储拧紧结果数据
    int  nexoHandleFlag;             // NC/Time set/set time/system error system/system error system ACK/old data upload/data ACK/data subscribe
                                    // Alive/NC/NC/NC/NC/NC/NC/vin download
                                    // curve Angle subscribe/curve Torque subscribe/curve ACK/71 alarm ack/NC/enable tool/disable tool/tool data
                                    // Tightening program numbers/NC/NC/commucation stop/reset batch counter/set batch size/selected program/commucaiton start
    short boltCount;
    short boltNokCount;
    int   intReadTighteningID;//收到正常（MID:61）拧紧结果的拧紧ID+1
    int   intPreTighteningID;
    int   intOldTighteningID;//
    int   timerCount;
    int sendTightenCount;//发送按拧紧ID请求后等待时间
//    int   dataCount;
    QList<int> requestList;//准备请求拧紧结果的列表
    QList<int> tightenIDTemp;//缓存的拧紧数据的拧紧ID
    int   nexoAliveCount;
    bool  nexoLinkOk;
    bool  nexoStartFlag;
    bool  readMaxTightenIDFlag;
    short nexoReadyFlag;
    bool  powerOnFlag;
    int   revDataLen;
    int   revFinishLen;
    int   curveFirstFlag;
    int   errCount;
    int   errType;
    int   angleSubFlag;
    int   curveDataFlag;
    int   sendVinFlag;
    int   sendNextEnableFlag;
    int   sendDisableFlag;
    QByteArray curveBuf;
    QString curveType;
    QString curveBufTemp;
    QString idCode;
    QByteArray vinBuf;
    QByteArray boltNumberBuf;

//    QByteArray nexoProNO;
//    QByteArray nexoResult;
//    QByteArray torqueValue;
//    QByteArray angleValue;
//    QByteArray tightenTime;
    QByteArray tighteningID;
//    QByteArray nexoCycleID;
    QByteArray nexoVin;
    QByteArray Channel;

    QByteArray oldTighteningID;
    QString data_model[15];
    QString controlType;
    void manageTightenResult(int,QString);
    QString judgeOKStatus(int,double,double,QString);
private slots:
    void tightenStart();
    void disConnectDO();
    void newConnects();
    void ctlNexoHandle();
    void revNexoData();
    void timerFuncXms();
//    void setNexoTighten(QByteArray vin, QByteArray boltNumber, short pid, short okCount, short nokCount);
    void sendReadOperate();
};
#endif
