﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GlobalVarible.h"
#include <QSettings>
#include "newconfiginfo.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include "save.h"
#include <QTextCodec>
#include <QTimer>
#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);
public:
    void searchVinNum();//匹配vin
    void searchG9Num();//匹配G9
    void judge();
    void Start(int interval, int maxValue);
    void Stop();
    void red_led(int);
    void green_led(int);
    void yellow_led(int);
    void white_led(int);
    void nok_led(int);
    void mysqlopen();
    void mysqlclose();
    void sendWebValue(int states,QString namepdm);

public slots:

    void fromsecondthreaddata(QString,QString,QString);
    void getSerialNum(QString,bool,QString);
    void connectMysql();
    void init();
    void wifishow(bool);
    void datashow(bool);
    void batteryshow(bool);
    void time_warning(bool);
    void ReceGunNotReady();

public :
signals:
    void clo();
    void clo1();
    void sendoperate();
    void sendfromsecondthread(QString ,QString,QString);
    void sendConfigureAll(int isoption,int whicharis,int whichpro,int whichoptionis);
    void sendnexo(QString);



public slots:
    void TightenIsReady(bool);
    void receiveOperate();
    void timerDelay();
    //void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_0_clicked();
    void ShowTime();
    void UpdateSlot();
    void PdmFlicker();//pdm flicker
    void on_pushButton_18_clicked();
    void on_pushButton_reset_clicked();
    void receiveCloseInput(bool);
    void configwarning(bool);
    void taotong_main(int);
    void shutdown(int);
    void clocked();

private slots:
    void on_pushButton_17_clicked();
    void signal_mysqlerror_do();
    void on_pushButton_shutdown_clicked();

private:
    Ui::MainWindow *ui;
    QString message;
    QString serialNums;
    QString tempPin;
    QString tempG9;

    QByteArray Data_Xml_Txheart;
    int isFull;
    QString temp;
    QString PDM_PATH;
    int person;
    int howmuchProNnum;  //匹配成功后有几个 程序号要使能
    int whichar;  //匹配出来的是哪个车型
    int enableLsnumber;
    int whichpronumis;//当前程序号
    int whichoption;
    QSqlDatabase db;
    QSqlQuery query;
    QSqlRecord record;
    QSqlField field;
    int  equeloptionbnum;
    int  equeloptionknum;
    QString selectVin;//sql
    int bxuannumtmp;
    QString PDMCurrentState;
    bool pdmnowromisOk;
    int m_CurrentValue;         //当前值
    int m_UpdateInterval;       //更新间隔
    int m_MaxValue;             //最大值
    QTimer m_Timer;
    QTimer timerpdm;
    QTimer shutdown_timer;
    int numpdm;
    QPushButton *butt[50];
    QLabel *label1[50];
    QLabel *label2[50];
    int tempnumdpm; //螺丝个数
    bool pdmflicker; //闪烁状态
    int whichpdmnumnow; //当前第几个闪烁
    int Tacktime;
    int ScrewWhichExit;
    int battry_num;

public:
    Newconfiginfo * newconfiginfo;
    QGraphicsOpacityEffect *e3;
    Save * save;
    bool ConfigOneOrAll;



};

#endif // MAINWINDOW_H