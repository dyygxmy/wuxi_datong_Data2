#include "mainwindow.h"
#include "GlobalVarible.h"
#include "changeof351andrfid.h"
#include "./TestInput_Cursor/inputmethod.h"
//#include "fisupdate.h"
#include <unistd.h>
#include "communication.h"
#include "tightenthread.h"
#include "tighten_op_net.h"
#include "xmlcreate.h"
#include "inputevents.h"
#include "wificonnect.h"
//#include "reinsertserverdb.h"
#include "taotong.h"
#include "sqlthread.h"
#include "split.h"
//#include "zigbeers232.h"
#include "logdelete.h"
#include "dt_http.h"
//#include "tightenatlasoppmm.h"
//#include "tightenatlasoppmm2.h"
#include "tighten_op_wheel.h"
#include "ftphandle.h"
#include "tightendataanalysis.h"
#include "tighten_op_atlas_PFC.h"
#include "tighten_op_atlas_PM.h"
#include "tighten_op_net.h"
#include "repaircurve.h"

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
bool bound_enabled = false;
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
QString status[100][5]={};
QString Version="";
int intDataMID = 0;
QString tablePreview="";
QString Localtable="";
int startNum = 1 ;
QString g_direction = "" ;
//QString idCode = "";
//int stationNo = 0;
QString curveNullBuf = "";
QString GTestTightenData = "";//测试用装拧紧结果数据

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
    QString message = QString("[%1] %2 %3").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz ddd")).arg(text).arg(msg);

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
#if DYTEST0^1
    QApplication::setOverrideCursor(Qt::BlankCursor);   //去掉光标
#endif
    qInstallMsgHandler(outputMessage);

    QTextCodec *code = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(code);
    QTextCodec::setCodecForLocale(code);
    QTextCodec::setCodecForCStrings(code);

    Version = "V21.0114.01";
    qDebug()<<"this dat@2 Version:"<<Version;

    tablePreview = "tighteningDatas" ;
    Localtable = "fisData";

    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    if(config->value(QString("baseinfo/GCpassword")).toString()==""||
           config->value(QString("baseinfo/cs351Ip")).toString()=="" )
    {
        system("cp /config1.ini /config.ini &");
    }

    QSettings *configIniRead = new QSettings("/config.ini", QSettings::IniFormat);
    configIniRead->value("baseinfo/serialMode").toInt()?SerialGunMode=true:SerialGunMode=false;
    isRFID = configIniRead->value("baseinfo/isRFID").toInt();
    Operator = configIniRead->value("baseinfo/Operator").toString();
    Line_ID = configIniRead->value("baseinfo/Line_ID").toInt();
    configIniRead->value("baseinfo/bound").toInt()?bound_enabled=true:bound_enabled=false;
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


    //if controller's type is atlas, give an initial value

    QString controlType = config->value("/baseinfo/controlType").toString();
    delete config;
    if(controlType == "Atlas"){
        system("echo 1 > /sys/class/leds/OUTC1/brightness");
    }
    qDebug() <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1"<< controlType ;
    //    TightenThread  tighten;
//#if 0
//        TightenOpNet tighten;
//#else
//    TightenOpAtlasPFC tighten ;
//    tighten.vari_2 = "1445";
////    tighten->vari_1 = main_variable1;
//#endif

    TightenOpAtlasPFC tighten ;
    tighten.vari_2 = "1445";
    TightenOpNet tighten_c ;



//    tightenAtlasOpPMM tighten_opnet ;
//    tightenAtlasOpPmm2 tighten_opnet2;
//    QString LeftIP = QSettings("/config.ini", QSettings::IniFormat).value("baseinfo/cs351Ip").toString();
//    QString RightIP = QSettings("/config.ini", QSettings::IniFormat).value("baseinfo/controlIP2").toString();
//    tighten_op_wheel wheelPMM_L(LeftIP,4545,"Left");
//    tighten_op_wheel wheelPMM_R(RightIP,4545,"Right");
    tightenDataAnalysis *analysis = new tightenDataAnalysis ;
//    repairCurve *repair = new repairCurve ;

    FtpHandle *ftp_handle = new FtpHandle;
    QTimer::singleShot(2500,ftp_handle,SLOT(ftpStart())); //PMM PFC 均需要

    if(controlType == "PMM")
    {
//        QTimer::singleShot(0,&tighten_opnet,SLOT(tightenStart()));
//        QTimer::singleShot(0,&tighten_opnet2,SLOT(tightenStart()));
//        QString LeftIP = QSettings("/config.ini", QSettings::IniFormat).value("baseinfo/cs351Ip").toString();
//        QString RightIP = QSettings("/config.ini", QSettings::IniFormat).value("baseinfo/controlIP2").toString();
//        wheelPMM_L.setTcpSocket(LeftIP,4545,"Left");
//        wheelPMM_R.setTcpSocket(RightIP,4545,"Right");
//        QTimer::singleShot(0,&wheelPMM_L,SLOT(tightenStart()));
//        QTimer::singleShot(0,&wheelPMM_R,SLOT(tightenStart()));
        QTimer::singleShot(0,analysis,SLOT(init()));
//        QTimer::singleShot(0,repair,SLOT(repairStart()));
//        QObject::connect(repair,SIGNAL(signalRepaieCurve(QString)),&tighten_opnet,SLOT(slotRepairCurve(QString)));
//        QObject::connect(repair,SIGNAL(signalRepaieCurve(QString)),&tighten_opnet2,SLOT(slotRepairCurve(QString)));
    }
    else if(controlType == "Atlas")
    {
        QTimer::singleShot(0,&tighten,SLOT(tightenStart()));
        QObject::connect(&tighten,SIGNAL(IsTigntenReady(bool)),&w,SLOT(TightenIsReady(bool)),Qt::AutoConnection);
//        QTimer::singleShot(0,repair,SLOT(repairStart()));
        QObject::connect(ftp_handle,SIGNAL(signalRepaieCurve(QString)),&tighten,SLOT(slotRepairCurve(QString)));
    }
    else if (controlType == "Cleco") {
        QTimer::singleShot(0,&tighten_c,SLOT(tightenStart()));
        QObject::connect(&tighten_c,SIGNAL(IsTigntenReady(bool)),&w,SLOT(TightenIsReady(bool)),Qt::AutoConnection);
    }

    XMLCreate XML_Create ;
//    QTimer::singleShot(0,&XML_Create,SLOT(XML_CreateStart()));

    Wificonnect Wifi_Connect ;
    QTimer::singleShot(0,&Wifi_Connect,SLOT(Wifi_ConnectStart()));

//    FisUpdate fisupdate;
//    QTimer::singleShot(0,&fisupdate,SLOT(myfistimer()));

//    /*****************数据库线程********************************/
//    SqlOperate  *sqloperate =  new SqlOperate;
//    QTimer::singleShot(0,sqloperate,SLOT(sqlInit()));
    SqlThread sqlthread;
//    QTimer::singleShot(0,&sqlthread,SLOT(sqlinit()));
    DT_HTTP *dtHttp = new DT_HTTP;              //data upload
    QTimer::singleShot(0,dtHttp,SLOT(init()));

    Communication communication ;

    Changeof351AndRfid change;
    QTimer::singleShot(0,&change,SLOT(comInit()));

    InputEvents inputevents ;
    QTimer::singleShot(0,&inputevents,SLOT(InputEventStart()));

    TaoTong taotong;
    QTimer::singleShot(0,&taotong,SLOT(T_start()));

    Split split;
    QTimer::singleShot(0,&split,SLOT(mysplit_timer()));

//    ZigbeeRS232 zigbee;
//    QTimer::singleShot(0,&zigbee,SLOT(zigbee_init()));

    LogDelete logDelete ;
    QTimer::singleShot(0,&logDelete,SLOT(init()));
//    QObject::connect(&zigbee,SIGNAL(IsTigntenReady(bool)),&w,SLOT(TightenIsReady(bool)),Qt::AutoConnection);


    QObject::connect(&w,SIGNAL(sendfromsecondthread(QString ,QString,QString)),&sqlthread,SLOT(configOne(QString,QString,QString)),Qt::AutoConnection);
    QObject::connect(&sqlthread,SIGNAL(send_mysqlerror()),&w,SLOT(signal_mysqlerror_do()),Qt::AutoConnection);

//PFC
//    QObject::connect(tighten,SIGNAL(IsTigntenReady(bool)),
//                     w,SLOT(TightenIsReady(bool)),Qt::AutoConnection);
//    QObject::connect(w,SIGNAL(sendOperate1(bool,int)),
//                     tighten,SLOT(sendReadOperate(bool,int)),Qt::AutoConnection);
//    QObject::connect(tighten,SIGNAL(QueueAlign(QString,bool,QString)),
//                     w,SLOT(getSerialNum(QString,bool,QString)),Qt::AutoConnection);


    if(controlType == "PMM")
    {
//        QObject::connect(&tighten_opnet,SIGNAL(signalSendTightenData(QByteArray)),
//                         analysis,SLOT(slotReceiveTightenData(QByteArray)));
//        QObject::connect(&tighten_opnet2,SIGNAL(signalSendTightenData(QByteArray)),
//                         analysis,SLOT(slotReceiveTightenData(QByteArray)));

        QString LeftIP = QSettings("/config.ini", QSettings::IniFormat).value("baseinfo/cs351Ip").toString();
        QString RightIP = QSettings("/config.ini", QSettings::IniFormat).value("baseinfo/controlIP2").toString();
        tighten_op_wheel wheelPMM_L(LeftIP,4545,"Left");
        tighten_op_wheel wheelPMM_R(RightIP,4545,"Right");
        QObject::connect(&wheelPMM_L,SIGNAL(signalSendTightenData(QByteArray)),
                         analysis,SLOT(slotReceiveTightenData(QByteArray)));
        QObject::connect(&wheelPMM_R,SIGNAL(signalSendTightenData(QByteArray)),
                         analysis,SLOT(slotReceiveTightenData(QByteArray)));
        QObject::connect(analysis,SIGNAL(sendfromworkthread(QVariant)),&sqlthread,SLOT(sqlinsert(QVariant)),Qt::AutoConnection);
        QObject::connect(analysis,SIGNAL(send_mainwindow(QString,QString,QString)),&w,SLOT(fromsecondthreaddata(QString,QString,QString/*,int*/)),Qt::AutoConnection);
        QObject::connect(analysis,SIGNAL(signalSendVin(QString,bool,QString)),
                         &w,SLOT(getSerialNum(QString,bool,QString)));
        QObject::connect(analysis,SIGNAL(signalSendTyre(QString,QString)),
                         &w,SLOT(showTyreNum(QString,QString)));

//        QObject::connect(&tighten_opnet,SIGNAL(sendfromworkthread(QVariant)),&sqlthread,SLOT(sqlinsert(QVariant)),Qt::AutoConnection);
//        QObject::connect(&tighten_opnet,SIGNAL(send_mainwindow(QString,QString,QString)),&w,SLOT(fromsecondthreaddata(QString,QString,QString/*,int*/)),Qt::AutoConnection);
//        QObject::connect(&tighten_opnet,SIGNAL(IsTigntenReady(bool)),&w,SLOT(TightenIsReady(bool)),Qt::AutoConnection);
//        QObject::connect(&tighten_opnet,SIGNAL(signalSendVin(QString,bool,QString)),
//                         &w,SLOT(getSerialNum(QString,bool,QString)));
//        QObject::connect(&tighten_opnet,SIGNAL(signalSendTyre(QString,QString)),
//                         &w,SLOT(showTyreNum(QString,QString)));


//        QObject::connect(&tighten_opnet2,SIGNAL(sendfromworkthread(QVariant)),&sqlthread,SLOT(sqlinsert(QVariant)),Qt::AutoConnection);
//        QObject::connect(&tighten_opnet2,SIGNAL(send_mainwindow(QString,QString,QString)),&w,SLOT(fromsecondthreaddata(QString,QString,QString/*,int*/)),Qt::AutoConnection);
//        QObject::connect(&tighten_opnet2,SIGNAL(IsTigntenReady(bool)),&w,SLOT(TightenIsReady(bool)),Qt::AutoConnection);
//        QObject::connect(&tighten_opnet2,SIGNAL(signalSendVin(QString,bool,QString)),
//                         &w,SLOT(getSerialNum(QString,bool,QString)));
//        QObject::connect(&tighten_opnet2,SIGNAL(signalSendTyre(QString,QString)),
//                         &w,SLOT(showTyreNum(QString,QString)));

//        QObject::connect(&w,SIGNAL(signalSendLeft()),&tighten_opnet,SLOT(revNexoData()));
//        QObject::connect(&w,SIGNAL(signalSendRight()),&tighten_opnet2,SLOT(revNexoData()));

        QObject::connect(&wheelPMM_L,SIGNAL(IsTigntenReady(bool)),&w,SLOT(TightenIsReady(bool)),Qt::AutoConnection);
        QObject::connect(&wheelPMM_R,SIGNAL(IsTigntenReady(bool)),&w,SLOT(TightenIsReady(bool)),Qt::AutoConnection);
    }
    else if (controlType == "Cleco") {
        QObject::connect(&w,SIGNAL(sendTestTightenData()),&tighten_c,SLOT(revNexoData()));
        QObject::connect(&tighten_c,SIGNAL(sendfromworkthread(QString *)),&sqlthread,SLOT(sqlinsert(QString *)),Qt::AutoConnection);
        QObject::connect(&tighten_c,SIGNAL(send_mainwindow(QString,QString,QString)),&w,SLOT(fromsecondthreaddata(QString,QString,QString)),Qt::AutoConnection);
        QObject::connect(&w,SIGNAL(sendoperate()),&tighten_c,SLOT(sendReadOperate()),Qt::AutoConnection);
    }
    else if(controlType == "PM")
    {
        TightenOpAtalsPM    *tighten_PM = new TightenOpAtalsPM;
        QTimer::singleShot(0,tighten_PM,SLOT(tightenStart()));
        QObject::connect(tighten_PM,SIGNAL(sendfromworkthread(QVariant)),&sqlthread,SLOT(sqlinsert(QVariant)),Qt::AutoConnection);
        QObject::connect(tighten_PM,SIGNAL(send_mainwindow(QString,QString,QString)),&w,SLOT(fromsecondthreaddata(QString,QString,QString)),Qt::AutoConnection);
        QObject::connect(tighten_PM,SIGNAL(IsTigntenReady(bool)),&w,SLOT(TightenIsReady(bool)),Qt::AutoConnection);
        QObject::connect(&w,SIGNAL(sendoperate()),tighten_PM,SLOT(sendReadOperate()),Qt::AutoConnection);
        QObject::connect(tighten_PM,SIGNAL(signalSendVin(QString,bool,QString)),
                                 &w,SLOT(getSerialNum(QString,bool,QString)));
    }
    else {
        QObject::connect(&tighten,SIGNAL(sendfromworkthread(QString *)),&sqlthread,SLOT(sqlinsert(QString *)),Qt::AutoConnection);
        QObject::connect(&tighten,SIGNAL(send_mainwindow(QString,QString,QString)),&w,SLOT(fromsecondthreaddata(QString,QString,QString)),Qt::AutoConnection);
        QObject::connect(&w,SIGNAL(sendoperate()),&tighten,SLOT(sendReadOperate()),Qt::AutoConnection);
    }

    QObject::connect(&w,SIGNAL(sendConfigureAll(int,int,int,int)),&sqlthread,SLOT(receiveConfigureAll(int,int,int,int)),Qt::AutoConnection);
    QObject::connect(&change,SIGNAL(serialCom(QString,bool,QString)),&w,SLOT(getSerialNum(QString,bool,QString)),Qt::AutoConnection);
    QObject::connect(&change,SIGNAL(sendSerial(QString)),w.newconfiginfo,SLOT(receiveDebug(QString)),Qt::AutoConnection);
//    QObject::connect(&work,SIGNAL(havedconnect(bool)),&tighten,SLOT(receivehavedconnect(bool)),Qt::AutoConnection);
//    QObject::connect(&w,SIGNAL(clo()),&work,SLOT(fromNew1thread()),Qt::AutoConnection);


    QObject::connect(&communication,SIGNAL(update()),&w,SLOT(init()),Qt::AutoConnection);
//    QObject::connect(w.newconfiginfo,SIGNAL(sendGetTime()),&fisupdate,SLOT(QueryTime()),Qt::AutoConnection);
//    QObject::connect(&fisupdate,SIGNAL(sendTime(QString)),w.newconfiginfo,SLOT(receivetime(QString)),Qt::AutoConnection);
    QObject::connect(&communication,SIGNAL(xmlcreate()),&XML_Create,SLOT(updateXML()),Qt::AutoConnection);
    QObject::connect(w.newconfiginfo,SIGNAL(xmlcreate()),&XML_Create,SLOT(updateXML()),Qt::AutoConnection);
//    QObject::connect(&zigbee,SIGNAL(wifi_connect(bool)),&w,SLOT(datashow(bool)),Qt::AutoConnection);
//    QObject::connect(&Wifi_Connect,SIGNAL(wifi_connect(bool)),&w,SLOT(wifishow(bool)),Qt::AutoConnection);
    QObject::connect(&Wifi_Connect,SIGNAL(data_connect(bool)),&w,SLOT(datashow(bool)),Qt::AutoConnection);

    QObject::connect(&tighten_c,SIGNAL(sendconfigwarning(bool)),&w,SLOT(configwarning(bool)),Qt::AutoConnection);

    QObject::connect(&inputevents,SIGNAL(sendconfigwarning(bool)),&w,SLOT(configwarning(bool)),Qt::AutoConnection);
    QObject::connect(&inputevents,SIGNAL(sendbatterysta(bool)),&w,SLOT(batteryshow2(bool)),Qt::AutoConnection);
    QObject::connect(&taotong,SIGNAL(sendbattery(QString)),&w,SLOT(batteryshow1(QString)),Qt::AutoConnection);
    QObject::connect(&taotong,SIGNAL(taotong_num(int)),&w,SLOT(taotong_main(int)),Qt::AutoConnection);
//    QObject::connect(&fisupdate,SIGNAL(time_error(bool)),&w,SLOT(time_warning(bool)),Qt::AutoConnection);
//    QObject::connect(w.newconfiginfo,SIGNAL(column_update(QString)),&fisupdate,SLOT(update_column(QString)),Qt::AutoConnection);

    QInputContext *im = new InputMethod();
    a.setInputContext( im );


    return a.exec();
}
