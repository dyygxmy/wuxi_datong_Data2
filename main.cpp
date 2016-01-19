#include "mainwindow.h"
#include "GlobalVarible.h"
#include "changeof351andrfid.h"
#include "./TestInput_Cursor/inputmethod.h"
#include "fisupdate.h"
#include <unistd.h>
#include "communication.h"
//#include "web.h"
#include "tightenthread.h"
//#include "sqloperate.h"
#include "xmlcreate.h"
#include "inputevents.h"
#include "wificonnect.h"
#include "reinsertserverdb.h"
//#include <QDateTime>
#include "taotong.h"
#include "sqlthread.h"
#include "split.h"
bool isJS = true;
bool isRFID = false;
bool isNormal = false;
bool workmode = false;
bool CsIsConnect = false;
bool RFIDISConnect = false;
bool RDYY  = false;
bool ISmaintenance = false;
bool ISRESET  = false;
bool ISWARNING = false;
bool Curve_Is_Null = false;
bool TaoTongState = false;
bool WIFI_STATE = false;
bool SerialGunMode = true;
bool DebugMode = false;
bool battery = true;
int Line_ID = 1;
QString SYSS = "";
QString SaveWhat="";
QString VIN_PIN_SQL= "";
QString SCREWID_SQL= "";
QByteArray time_info ="";
QString proNum="";      //当前程序号
QString lsNum="";       //额定螺栓数量
QString CURVE_STR="";
int QualifiedNum=0;  //合格数量
int TimeLeft = 0;
int enablenumberLeft = 0;
int BackTimeLeft = 0;  //归位剩余时间
int TAOTONG = -1;
QString Operator = "";
QString info[7] ={};
QString status[20][5]={};
QString Version="";

void outputMessage(QtMsgType type, const char *msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
       text = QString("Debug:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
        abort();
    }
    QString message = QString("[%1] %2 %3").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd")).arg(text).arg(msg);

    QDateTime time = QDateTime::currentDateTime();
    QString date = time.toString("yyyy-MM-dd");

    QFile file(QString("/log/")+date+QString(".log"));
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << endl;
    file.flush();
    file.close();
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOverrideCursor(Qt::BlankCursor);   //去掉光标
    qInstallMsgHandler(outputMessage);
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    if(config->value(QString("baseinfo/GCpassword")).toString()==""||
           config->value(QString("baseinfo/cs351Ip")).toString()=="" )
    {
        system("cp /config1.ini /config.ini &");
    }
    delete config;
    QSettings *configIniRead = new QSettings("/config.ini", QSettings::IniFormat);
    configIniRead->value("baseinfo/serialMode").toInt()?SerialGunMode=true:SerialGunMode=false;
    isRFID = configIniRead->value("baseinfo/isRFID").toInt();
    Operator = configIniRead->value("baseinfo/Operator").toString();
    Line_ID = configIniRead->value("baseinfo/Line_ID").toInt();
    Version = "V4.001";
    system((QString("ifconfig wlan0 ")+configIniRead->value("baseinfo/WirelessIp").toString()+" netmask "+configIniRead->value("baseinfo/netmask").toString()+" &").toLatin1().data());
    system((QString("ifconfig eth0 ")+configIniRead->value("baseinfo/LocalIp").toString()+" &").toLatin1().data());
    QString freetds = "/usr/local/arm/freetds/etc/freetds.conf";
    QFile file1(freetds);
    if(!file1.open(QIODevice::ReadOnly| QIODevice::Text)){
        qDebug()   << "Cannot open testdsn file1 for Reading";
    }
    QString str1 (file1.readAll());
    if(str1.contains("[testdsn1]", Qt::CaseInsensitive)&&str1.contains("[testdsn2]", Qt::CaseInsensitive)){
        str1.replace(QRegExp("\\[testdsn1\\]\\s*host = \\S*"),QString("[testdsn1]\n\thost = ")+configIniRead->value("baseinfo/CurveServerIp").toString());
        str1.replace(QRegExp("\\[testdsn2\\]\\s*host = \\S*"),QString("[testdsn2]\n\thost = ")+configIniRead->value("baseinfo/DataServerIp").toString());
    }
    file1.close();
    if(!file1.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
        qDebug()   << "Cannot open testdsn file1 for Writing";
    }
    file1.write(str1.toUtf8());
    file1.close();

    QString wpa_conf = "/etc/wpa_supplicant.conf";
    QFile file2(wpa_conf);
    if(!file2.open(QIODevice::ReadOnly| QIODevice::Text)){
        qDebug()   << "Cannot open wifi file2 for Reading";
    }
    QString str2 (file2.readAll());
    if(str2.contains("ssid=", Qt::CaseInsensitive)&&str2.contains("psk=", Qt::CaseInsensitive)){
        str2.replace(QRegExp("\nssid=\\S*"),QString("\nssid=\"")+configIniRead->value("baseinfo/SSID").toString()+QString("\""));
        str2.replace(QRegExp("psk=\\S*"),QString("psk=\"")+configIniRead->value("baseinfo/psk").toString()+QString("\""));
    }
    file2.close();
    if(!file2.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
        qDebug()   << "Cannot open wifi file2 for Writing";
    }
    file2.write(str2.toUtf8());
    file2.close();

    system((QString("wpa_cli set_network 0 ssid '\"")+configIniRead->value("baseinfo/SSID").toString()+QString("\"'")+" &").toLatin1().data());
    system((QString("wpa_cli set_network 0 psk  '\"")+configIniRead->value("baseinfo/psk").toString()+QString("\"'")+" &").toLatin1().data());
    system("wpa_cli disable_network 0 &");
    system("wpa_cli enable_network 0 &");
    delete configIniRead;
    time_info.resize(7);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    QString k_power;
    QFile power("/var/power");
    power.open(QIODevice::ReadOnly);
    QTextStream in_power(&power);
    in_power >> k_power;
    if(k_power=="11")
        battery=false;

    MainWindow w ;
    w.show();

    TightenThread  tighten;
    QObject::connect(&tighten,SIGNAL(IsTigntenReady(bool)),&w,SLOT(TightenIsReady(bool)),Qt::AutoConnection);
    QTimer::singleShot(0,&tighten,SLOT(tightenStart()));

    XMLCreate XML_Create ;
    QTimer::singleShot(0,&XML_Create,SLOT(XML_CreateStart()));

    Wificonnect Wifi_Connect ;
    QTimer::singleShot(0,&Wifi_Connect,SLOT(Wifi_ConnectStart()));

    FisUpdate fisupdate;
    QTimer::singleShot(0,&fisupdate,SLOT(myfistimer()));

//    /*****************数据库线程********************************/
//    SqlOperate  *sqloperate =  new SqlOperate;
//    QTimer::singleShot(0,sqloperate,SLOT(sqlInit()));
    SqlThread sqlthread;
    QTimer::singleShot(0,&sqlthread,SLOT(sqlinit()));
    Communication communication ;
    QTimer::singleShot(0,&communication,SLOT(mycommunicationtimer()));

    ReInsertServerDb reinsert;
    QTimer::singleShot(0,&reinsert,SLOT(reinsert_start()));

    //QTimer::singleShot(0,w,SLOT(configInit()));
   // Web server;
    //Q_UNUSED(server);
    //QTimer::singleShot(0,&server,SLOT(mywebtimer()));
    Changeof351AndRfid change;
    QTimer::singleShot(0,&change,SLOT(comInit()));

    InputEvents inputevents ;
    QTimer::singleShot(0,&inputevents,SLOT(InputEventStart()));

    TaoTong taotong;
    QTimer::singleShot(0,&taotong,SLOT(T_start()));

    Split split;
    QTimer::singleShot(0,&split,SLOT(mysplit_timer()));

    QObject::connect(&tighten,SIGNAL(sendfromworkthread(QString *)),&sqlthread,SLOT(sqlinsert(QString *)),Qt::AutoConnection);
    QObject::connect(&tighten,SIGNAL(send_mainwindow(QString,QString,QString)),&w,SLOT(fromsecondthreaddata(QString,QString,QString)),Qt::AutoConnection);
    QObject::connect(&w,SIGNAL(sendfromsecondthread(QString ,QString,QString)),&sqlthread,SLOT(configOne(QString,QString,QString)),Qt::AutoConnection);
    QObject::connect(&sqlthread,SIGNAL(send_mysqlerror()),&w,SLOT(signal_mysqlerror_do()),Qt::AutoConnection);

    QObject::connect(&w,SIGNAL(sendConfigureAll(int,int,int,int)),&sqlthread,SLOT(receiveConfigureAll(int,int,int,int)),Qt::AutoConnection);
    QObject::connect(&change,SIGNAL(serialCom(QString,bool,QString)),&w,SLOT(getSerialNum(QString,bool,QString)),Qt::AutoConnection);
    QObject::connect(&change,SIGNAL(sendSerial(QString)),w.newconfiginfo,SLOT(receiveDebug(QString)),Qt::AutoConnection);
//    QObject::connect(&work,SIGNAL(havedconnect(bool)),&tighten,SLOT(receivehavedconnect(bool)),Qt::AutoConnection);
//    QObject::connect(&w,SIGNAL(clo()),&work,SLOT(fromNew1thread()),Qt::AutoConnection);

    QObject::connect(&w,SIGNAL(sendoperate()),&tighten,SLOT(sendReadOperate()),Qt::AutoConnection);
    QObject::connect(&communication,SIGNAL(update()),&w,SLOT(init()),Qt::AutoConnection);
    QObject::connect(w.newconfiginfo,SIGNAL(sendGetTime()),&fisupdate,SLOT(QueryTime()),Qt::AutoConnection);
    QObject::connect(&fisupdate,SIGNAL(sendTime(QString)),w.newconfiginfo,SLOT(receivetime(QString)),Qt::AutoConnection);
    QObject::connect(&communication,SIGNAL(xmlcreate()),&XML_Create,SLOT(updateXML()),Qt::AutoConnection);
    QObject::connect(w.newconfiginfo,SIGNAL(xmlcreate()),&XML_Create,SLOT(updateXML()),Qt::AutoConnection);
    QObject::connect(&Wifi_Connect,SIGNAL(wifi_connect(bool)),&w,SLOT(wifishow(bool)),Qt::AutoConnection);
    QObject::connect(&Wifi_Connect,SIGNAL(data_connect(bool)),&w,SLOT(datashow(bool)),Qt::AutoConnection);

    QObject::connect(&inputevents,SIGNAL(sendconfigwarning(bool)),&w,SLOT(configwarning(bool)),Qt::AutoConnection);
    QObject::connect(&inputevents,SIGNAL(sendbatterysta(bool)),&w,SLOT(batteryshow2(bool)),Qt::AutoConnection);
    QObject::connect(&taotong,SIGNAL(sendbattery(QString)),&w,SLOT(batteryshow1(QString)),Qt::AutoConnection);
    QObject::connect(&taotong,SIGNAL(taotong_num(int)),&w,SLOT(taotong_main(int)),Qt::AutoConnection);
    QObject::connect(&fisupdate,SIGNAL(time_error(bool)),&w,SLOT(time_warning(bool)),Qt::AutoConnection);
    QObject::connect(w.newconfiginfo,SIGNAL(column_update(QString)),&fisupdate,SLOT(update_column(QString)),Qt::AutoConnection);

    QInputContext *im = new InputMethod();
    a.setInputContext( im );


    return a.exec();
}
