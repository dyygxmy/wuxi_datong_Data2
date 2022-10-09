#ifndef TIGHTENDATAANALYSIS_H
#define TIGHTENDATAANALYSIS_H

#include <QObject>
#include <QThread>
#include <QQueue>
#include <QTimer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSettings>

#include <QDebug>

#include "GlobalVarible.h"

class tightenDataAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit tightenDataAnalysis(QObject *parent = 0);
    QString searchScrewID(int);

private:
    QThread anyThread ;
    QQueue<QByteArray> dataQueue ;
    QTimer *timer;
    QSqlDatabase db;
    QSqlQuery query;

    void getCarType(QString) ;
    void mysqlConnect();
    bool mysqlIsOpen() ;
    void mysqlClose();

    int whichar ;
    int bufLsNum ;
    bool analysiaFlag ; //是否在解析过程中

//    int  nexoHandleFlag;
//    short programNO;
    short boltCount;
    short boltNokCount;
    int   intReadTighteningID;
//    int   intNexoMaxTighteningID;

//    int   nexoAliveCount;
//    bool  nexoLinkOk;
//    bool  readOldDataFlag;
//    bool  nexoStartFlag;
//    bool  readMaxTightenIDFlag;
//    short nexoReadyFlag;
//    int   revDataLen;
//    int   revFinishLen;
//    int   curveFirstFlag;
//    int   errCount;
//    int   angleSubFlag;
//    int   curveDataFlag;
//    int   sendVinFlag;
    int   tyreNum ;
//    QByteArray curveBuf;
//    QString curveType;
//    QString curveBufTemp;

    QByteArray vinBuf;
//    QByteArray boltNumberBuf;

    QByteArray nexoProNO;
    QByteArray TightenResult;
    QByteArray torqueValue;
    QByteArray angleValue;
    QByteArray tighenTime;
    QByteArray tighteningID;
//    QByteArray nexoCycleID;
//    QByteArray nexoVin;
//    QByteArray Channel;

//    QByteArray nexoOldTigheningID;
//    int StartBolt;
    QString idCode;
    int stationNo;
//    QString curveNullBuf;
    QString strVin ;

private slots:
    void analysisData() ;


signals:
    void sendfromworkthread(QVariant);
    void send_mainwindow(QString,QString,QString/*,int*/);
    void signalSendVin(QString,bool,QString) ;
    void signalSendTyre(QString,QString );

public slots:
    void init() ;
    void slotReceiveTightenData(QByteArray) ;

};

#endif // TIGHTENDATAANALYSIS_H
