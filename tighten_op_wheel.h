#ifndef TIGHTEN_OP_WHEEL_H
#define TIGHTEN_OP_WHEEL_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QStringList>
#include "GlobalVarible.h"


class tighten_op_wheel : public QObject
{
    Q_OBJECT
public:
    explicit tighten_op_wheel(QString ip, int port ,QString cho,QObject *parent = 0);
//    tighten_op_wheel(QString ip, int port ,QString cho);
//    void setTcpSocket(QString,int,QString);
//    void run();
signals:
    void signalSendTightenData(QByteArray);
    void IsTigntenReady(bool);
//    void sendCurveData(QString,int);
public slots:
private slots:
    void disConnect();
    void socketManage();
    void readFunc();
    void waitSendCmd();
    void newConnect();
private:
    QTcpSocket *tcpSocket;
    QThread thread;
    QString strJobID;
    QString tighteningID;
    QString curveBufTemp;
    QString curveBufTemp1;
    QByteArray veceivedData;//接收完数据
    QList<QByteArray>foldList;//临时存储所有叠包
    QString vinCode;//VIN码
    QString Channel;//通道号
    int missCycle;//记录本次处理缺失曲线的循环号
    int programNO;//程序号
    int boltCount;//螺栓个数
    int boltNokCount;//容错个数
    bool startLiveFlag;//拧紧机启动成功开始心跳
    bool connectFlag;//连接状态标志
    bool taskCmdEndFlag;//任务结束了再发下一条指令
    bool newTightenFlag;//来了新的拧紧结果，准备订阅曲线
    //bool sendLiveFlag;//发心跳标志位
    //int curveCount;//收到的第几条曲线
    bool receiveCurveT;//收到扭矩曲线
    bool receiveCurveA;//收到角度曲线
    int disConnectTime;//记录一次未连接
    int onceTimeOut;//记录一次超时
    int waitTask;//存储本次不满足条件发送命令，等待满足后发送
    int dataMesSubType;//订阅的数据类型
    int currentMID;//当前在用的MID
    //QVariantMap tightenResultMap;//保存拧紧结果（含曲线字段）
    QString LeftOrRight;//左右轮
    QString thghtenID;//拧紧循环号

    QString ip;
    int port;
    QString cho;
    int countCycle;
    QByteArray writeBuf;//写入拧紧机的数据
    void sendCmd(int);
    void writeFunc(QByteArray,int);
    void receivenormaldata(int,int,int,QByteArray);
    void curveConversion(int,QByteArray,QString,QString);//曲线数据转换后存储
};

#endif // TIGHTEN_OP_WHEEL_H
