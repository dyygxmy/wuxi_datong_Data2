#include "tightendataanalysis.h"

tightenDataAnalysis::tightenDataAnalysis(QObject *parent) :
    QObject(parent)
{
//    curveNullBuf = "Curve is null";

    this->moveToThread(&anyThread);
    anyThread.start();
    mysqlConnect();
}

void tightenDataAnalysis::init()
{
    FUNC() ;
    analysiaFlag = false ;
    //mysqlopen();
    timer = new QTimer(this );
    connect(timer,SIGNAL(timeout()),this,SLOT(analysisData()));
}

void tightenDataAnalysis::slotReceiveTightenData(QByteArray buf)
{
    FUNC();
    dataQueue.enqueue(buf);

    if(!timer->isActive() && analysiaFlag == false)
    {
        timer->start(100);//开始处理拧紧结果
    }
}

void tightenDataAnalysis::analysisData()
{
//    qDebug()<<"point[analysisData_0]:";
    if(timer->isActive())
    {
        timer->stop();
    }
    analysiaFlag = true ;


    bool okFlag;
//    int nexoMID;
//    int cmdType;
//    int errCode;
//    int nullCount=0,i=0,j=0,k=0;
//    int hByte,lByte;
//    int revLen,cmdLen;
    int PM_Num = 0;
//    int PID_Len = 0;
//    int TempLen = 0;
//    int stationNoTemp=0;
//    QString CurveNO = "";
    QByteArray torqueMax = "";
    QByteArray torqueMin = "";
    int intAngle = 0;
//    double doubleTorque = 0 ;
    int okNum = 0 ;
//    QByteArray recBuf,hexBuf;//,hexBufTemp;
    QString screwid ;
    int NOKNUM = 0 ;

    QByteArray recBuf = dataQueue.dequeue() ;


    vinBuf       = recBuf.mid(121,17);//LSKG4GC18LA064456
    if(strVin != vinBuf)
    {
        tyreNum = 0 ;
        strVin = vinBuf ;
        getCarType(strVin);
    }
    Q_EMIT signalSendVin(strVin,false," ");//从拧紧结果中获取到的VIN码发给主页面

        tighteningID = recBuf.mid(31,9);          //Tightening ID max high not need
        tighteningID.append("0");
        idCode = tighteningID;
        stationNo = recBuf.mid(42,2).toInt();                 //stationNo
        tighenTime   = recBuf.mid(68,19);                           //Torque time
        nexoProNO    = recBuf.mid(89,2);                            //mode NO
        PM_Num       = recBuf.mid(163,2).toInt();                   //number of Bolts
        intReadTighteningID = tighteningID.toInt(&okFlag,10);

        g_direction = recBuf.mid(52,5) ;

        DTdebug() << tighteningID<<idCode<<stationNo<<tighenTime<<nexoProNO<<PM_Num << intReadTighteningID ;
        if(intReadTighteningID == 0)
        {
            DTdebug() << "data error **intReadTighteningID = 0***";
            return ;
        }
        if(PM_Num > 0)
        {

            QByteArray strTightenRestlt1 = recBuf.mid(171,1);
            QByteArray strTightenRestlt2 = recBuf.mid(238,1);
            QByteArray strTightenRestlt3 = recBuf.mid(305,1);
            QByteArray strTightenRestlt4 = recBuf.mid(372,1);
            QByteArray strTightenRestlt5 = recBuf.mid(439,1);

            if(strTightenRestlt1 == "1" &&  strTightenRestlt2 == "1"&&  strTightenRestlt3 == "1"&&  strTightenRestlt4 == "1"&&  strTightenRestlt5 == "1")
            {
                DTdebug() << "OK" ;
                TightenResult = "OK" ;
            }
            else {
                DTdebug() << "NOK" ;
                TightenResult = "NOK" ;
            }

            for(int n=0;n<PM_Num;n++)
            {
                DTdebug() << TightenResult ;
                tighteningID.replace(9,1,QByteArray::number(n+1));
                int addr = n*67;

                torqueValue = recBuf.mid(180+addr,7);                      //torque value
                torqueValue = QByteArray::number(torqueValue.toDouble());

                angleValue = recBuf.mid(189+addr,7);
                intAngle    = angleValue.toDouble()+0.5;
                angleValue  = QByteArray::number(intAngle,10);             //angle value

                torqueMax   = recBuf.mid(198+addr,7);                      //torque high limit
                torqueMin   = recBuf.mid(207+addr,7);                      //torque low limit

                if(TightenResult == "NOK")
                {
                    NOKNUM ++ ;
                    if(boltNokCount > 0)
                        boltNokCount --;
                    if(startNum == 21)
                    {
                        startNum = 1 ;
                    }
                    screwid = searchScrewID(startNum+n) ;
                    if(NOKNUM == 5)
                    {
                        emit signalSendTyre(g_direction,TightenResult);
                    }
                }
                else
                {
                    okNum ++ ;
                    if(boltCount > 0)
                        boltCount --;
                    if(startNum == 21)
                    {
                        startNum = 1 ;
                    }
                    screwid = searchScrewID(startNum) ;
                    startNum ++ ;
                    if(okNum == 5)
                    {
                        emit signalSendTyre(g_direction,TightenResult);
                    }
                }
                DTdebug()  << stationNo <<tighteningID << nexoProNO << torqueValue << angleValue << TightenResult << tighenTime<<torqueMax<<torqueMin;
                if(torqueValue == "0" || angleValue == "0")
                {
                    DTdebug()<<"torqueValue == 0 || angleValue == 0"<< recBuf;   //扭矩角度解析出来为0???
                }
                DATA_STRUCT demo;
                demo.data_model[0] = QString(tighenTime.mid(0,10));
                demo.data_model[1] = QString(tighenTime.mid(11,8));
                demo.data_model[2] = QString(TightenResult);
                demo.data_model[3] = QString(torqueValue);
                demo.data_model[4] = QString(angleValue);
                demo.data_model[5] = screwid;
                demo.data_model[6] = QString(vinBuf);
                demo.data_model[7] = QString(tighteningID);
                demo.data_model[8] = curveNullBuf;
                demo.data_model[9] = QString(nexoProNO);
                demo.data_model[10] = "0";

                QVariant DataVar;
                DataVar.setValue(demo);

                emit sendfromworkthread(DataVar);//sqlthread.cpp->sqlinsert()
                emit send_mainwindow(QString(torqueValue),QString(angleValue),QString(TightenResult)/*,n*/);
                DTdebug() << "sendSqlInsertEnd" ;
            }
        }

    if(dataQueue.isEmpty())
    {
        analysiaFlag = false ;
    }
    else {
        timer->start(100);
    }
//    qDebug()<<"point[analysisData_1]:";
}


void tightenDataAnalysis::getCarType(QString strVin)
{
    FUNC();
    QString strCarType = "" ;
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);

    QString strSqlSelect = QString("select CarID from %1 where VIN='%2'").arg(SQL_TABLE_FISDATA).arg(strVin);
    if(mysqlIsOpen()){
        if(!query.exec(strSqlSelect))
        {
            DTdebug() << query.lastError() << strSqlSelect;
        }
        else
        {
            if(query.next())
            {
                strCarType = query.value(0).toString();
            }
        }
        mysqlClose();
    }

    int i = 1;
    for(i = 1;i < 21;i++)
    {
        QString temp = config->value(QString("carinfo").append(QString::number(i)).append("/VIN")).toString();
        if((!strCarType.isEmpty()) && (strCarType == temp))
        {
            DTdebug() << "config" << temp << "sql:" << strCarType <<i;
            whichar = i;
            break;
        }
        else {
            DTdebug() << "config" << temp << "sql:" << strCarType ;
        }
    }
    delete config;
}

QString tightenDataAnalysis::searchScrewID(int lsNum)
{
    FUNC() ;
    DTdebug() << g_direction << lsNum << startNum;
    QString bufScrwid = "" ;
    if(whichar == 0)
    {
        DTdebug() << "catType is wrong";
    }
    else
    {
        if((startNum < 6 && g_direction=="Right") || (startNum >10 && startNum <16 && g_direction=="Right") )
        {
            lsNum = lsNum+5 ;
        }
        else if (startNum>5 && startNum<11 && g_direction=="Left " || (startNum >15 && startNum <21 && g_direction=="Left ")) {
            lsNum -= 5 ;
        }
        QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
        for(int i = lsNum ; i<21 ;i++)
        {
            bufScrwid = config->value(QString("carinfo").append(QString::number(whichar)).append("/LuoSuanNum").append(QString::number(i))).toString();
            int temp = bufScrwid.mid(6,1).toInt();
            if(g_direction == "Left ")
            {
                DTdebug() << "left" << bufScrwid << temp%2;
                if(temp%2 == 1)
                {
                    break ;
                }

            }
            else if (g_direction == "Right")
            {
                DTdebug() << "left" << bufScrwid  << temp;
                if(temp%2 == 0 && temp != 0)
                {
                    break ;
                }
            }

        }
        DTdebug() <<"screwid" <<bufScrwid;
        delete config;
    }
    return bufScrwid ;
}

void tightenDataAnalysis::mysqlConnect()
{
    db = QSqlDatabase::addDatabase("QMYSQL","analysis");
    db.setHostName("localhost");
    db.setDatabaseName("Tighten");
    db.setUserName("root");
    db.setPassword("123456");
    query = QSqlQuery(db);
}

bool tightenDataAnalysis::mysqlIsOpen()
{
    if(!db.isOpen() || !db.contains("analysis")){
        if(db.open()){
            qDebug()<<"open analysis success";
        }else{
            qDebug()<<"open analysis faile:"<<db.lastError().text();
        }
    }

    if(db.isOpen() && db.contains("analysis")){
        return true;
    }else{
        return false;
    }
}

void tightenDataAnalysis::mysqlClose()
{
    if(db.isOpen()){
        db.close();
    }
}
