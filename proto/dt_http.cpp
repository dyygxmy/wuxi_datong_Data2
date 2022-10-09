#include "dt_http.h"

DT_HTTP::DT_HTTP(QObject *parent) :
    QObject(parent)
{
    this->moveToThread(&m_thread);
    m_thread.start();
    mysqlConnect();
}

void DT_HTTP::init()
{
    DTdebug() << "http thread start" ;
    TIMEOUT = (5 * 1000);
    isFirst = true;
    GetTimes = 0;
    wrongRecordID = -1;
    wrongTimes = 0;
    initTable();    //建表
    QSettings *configIniRead = new QSettings("/config.ini", QSettings::IniFormat);
    QString DataServerIp = configIniRead->value("baseinfo/DataServerIp").toString();
    QString ServerPort = configIniRead->value("baseinfo/ServerPort").toString();
    delete configIniRead;
    manager = new QNetworkAccessManager(this);
    req.setUrl(QUrl("http://"+DataServerIp+":"+ServerPort+"/submit?"));
    QTimer::singleShot(1000,this,SLOT(dataInsert()));
}

void DT_HTTP::initTable()
{
    FUNC() ;
    QString strSqlCreate  = " " ;
    bool result ;
    if(mysqlIsOpen())
    {
        strSqlCreate= QString("CREATE TABLE IF NOT EXISTS %1 ("
                              "RecordID int not null primary key, "
                              "CarID    varchar(10) not null,"
                              "PID      varchar(30) ,"
                              "MaterialNumber varchar(30),"
                              "PIN      varchar(20),"
                              "TPS      varchar(100),"
                              "CarSignature varchar(10) not null,"
                              "TYPE     varchar(10),"
                              "VIN      varchar(20) not null,"
                              "LocalDateTime datetime not null,"
                              "FisMatch TEXT null)").arg(SQL_TABLE_FISDATA) ;
        result = query.exec(strSqlCreate) ;
        if(!result)
        {
            DTdebug()<<"create table fail"<<query.lastError();
        }

        strSqlCreate = QString("CREATE TABLE IF NOT EXISTS %1 ("
                               "RecordID int not null primary key auto_increment,"
                               "IDCode   varchar(128) not null,"
                               "TPS      varchar(50) null,"
                               "ScrewID  varchar(28) null,"
                               "Torque   real not null,"
                               "Angle    real not null,"
                               "Curve    text not null,"
                               "TighteningStatus char(3) not null,"
                               "TighteningTime   datetime not null,"
                               "LocalDateTime    datetime not null,"
                               "Operator char(15) null,"
                               "UploadMark       tinyint not null,"
                               "UploadTime       datetime null,"
                               "Cycle    int null,"
                               "Program  int null, "
                               "Channel  int null, "
                               "Type     char(20) not null, "
                               "Order_id int null, "
                               "`MaxValue` float null, "
                               "`MinValue` float null, "
                               "JobStatus  int null"
                               ") DEFAULT CHARSET=utf8").arg(SQL_TABLE_TIGHTENDATA) ;
        DTdebug() << "---initTable()---";
        result = query.exec(strSqlCreate) ;

        if(!result)
        {
            DTdebug()<<"create table fail"<<query.lastError();
        }
        mysqlClose();
    }
}

void DT_HTTP::dataInsert()
{
    QString strSql = "" ;
    QString strSqlSelect = "" ;

//    qDebug()<<"point[201]:"<<GetTimes;

    if(GetTimes == 0)       //Time
    {
        GetTimes++;
        QVariantMap dataMap;
        dataMap.insert("Type","Get");
        dataMap.insert("Target","GetCurrentTime");
        QJson::Serializer serializer;
        bool ok;
        QByteArray json = serializer.serialize(dataMap, &ok);

        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        req.setHeader(QNetworkRequest::ContentLengthHeader, json.length());

        if (ok)
        {
            DTdebug() << "Get CurrentTime";
            QNetworkReply *reply = manager->post(req,json);
            reply->ignoreSslErrors();
            QTime t_time;
            t_time.start();

            bool timeout = false;

            while (!reply->isFinished())
            {
                QApplication::processEvents();
                if (t_time.elapsed() >= TIMEOUT)
                {
                    timeout = true;
                    DTdebug()<<"CurrentTime reply timeout";
                    break;
                }
            }
            if (!timeout && reply->error() == QNetworkReply::NoError)
            {
                QByteArray bytes = reply->readAll();

                QJson::Parser parser;
                bool ok;

                QVariantMap result = parser.parse(bytes, &ok).toMap();
                if (!ok)
                {
                    DTdebug()<<"Get CurrentTime An error occurred during parsing"<<bytes;
                }
                else
                {
                    if(result["Result"].toBool())
                    {
                        if(result["Type"].toString()=="Get" && result["Target"].toString()=="GetCurrentTime")
                        {
                            QString datetime = result["CurrentTime"].toString();
                            system((QString("date -s \"") +datetime+QString("\" &")).toLatin1().data());
                            //将系统时间写入RTC
                            system("hwclock -w &");
                            DTdebug()<<"GetCurrentTime success "<<datetime;
                        }
                        else
                            DTdebug()<<"What's wrong"<<bytes;
                    }
                    else
                    {
                        DTdebug()<<"GetCurrentTime fail ";
                        if(result["ErrorCode"].toString()== "1")
                        {
                            DTdebug()<<"Server Json parse fail"<<json;
                        }
                    }
                }
            }
            else if(reply->error() != QNetworkReply::NoError)
            {
                DTdebug()<<"GetCurrentTime handle errors here";
                QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
                //statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
                DTdebug( )<<"GetCurrentTime found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error();
                DTdebug()<<reply->errorString();
            }

            reply->deleteLater();
        }
        else
        {
            DTdebug() << "Something went wrong:" << serializer.errorMessage();
        }
    }
    else if(GetTimes%6 == 0)        //Fis
    {
        GetTimes++;
        if(mysqlIsOpen())
        {
            strSql = QString("SELECT MAX(RecordID) FROM %1").arg(SQL_TABLE_FISDATA) ;
            if(!query.exec(strSql))
            {
                DTdebug()<<"SELECT fail "<<query.lastError();
            }
            else
            {
                QVariantMap dataMap;
                dataMap.insert("Type","Get");
                dataMap.insert("Target","FisPreview");
                QVariantMap data;
                if(query.next())
                {
                    int ID = query.value(0).toInt();

                    if(ID == 0)
                        data.insert("ID",-1) ;
                    else {
                        data.insert("ID",ID);
                    }

                }
                else
                    data.insert("ID",-1);
                data.insert("Line_ID",Line_ID);
                dataMap.insert("Parameter",data);

                QJson::Serializer serializer;
                bool ok;
                QByteArray json = serializer.serialize(dataMap, &ok);

                req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
                req.setHeader(QNetworkRequest::ContentLengthHeader, json.length());
                DTdebug() << json;

                if (ok)
                {
                    DTdebug() << "post get FisPreview";   //<<json;
                    QNetworkReply *reply = manager->post(req,json);
                    reply->ignoreSslErrors();
                    QTime t_time;
                    t_time.start();

                    bool timeout = false;

                    while (!reply->isFinished()) {
                        QApplication::processEvents();
                        if (t_time.elapsed() >= TIMEOUT) {
                            timeout = true;
                            DTdebug()<<"FisPreview reply timeout";
                            break;
                        }
                    }
                    if (!timeout && reply->error() == QNetworkReply::NoError)
                    {
                        QByteArray bytes = reply->readAll();
                        QJson::Parser parser;
                        bool ok;

                        QVariantMap result = parser.parse(bytes, &ok).toMap();
                        if (!ok) {
                            DTdebug()<<"get FisPreview An error occurred during parsing"<<bytes;
                        }
                        else
                        {
                            if(result["Result"].toInt() >0)
                            {
                                if(result["Type"].toString()=="Get" && result["Target"].toString()=="FisPreview")
                                {
                                    DTdebug()<<"get FisPreview";
                                    foreach (QVariant Value, result["Value"].toList())
                                    {

                                        QVariantMap value = Value.toMap();

                                        strSql = QString("SELECT COUNT(*) FROM %1").arg(SQL_TABLE_FISDATA) ;
                                        if(!query.exec(strSql))
                                            DTdebug()<<"SELECT COUNT(*) FAIL "<<query.lastError();
                                        else
                                        {
                                            if(query.next())
                                            {
                                                int numRows = query.value(0).toInt();

                                                if (numRows > 7000)
                                                {
                                                    DTdebug() << "data delete" ;
                                                    query.exec("delete from "+Localtable+
                                                                   " where RecordID in (select x.RecordID from (select RecordID from "
                                                                    +Localtable+" order by RecordID limit  100) as  x)");

                                                }
                                                else
                                                {

                                                }
                                                //fisData
                                                query.prepare("insert into " +Localtable+ "(RecordID,VIN,CarID,PID,MaterialNumber,PIN, TPS, CarSignature, TYPE, LocalDateTime, FisMatch) values (?, ?, ?, ?, ?, ?, ?, ?, ?, now(),?)") ;


//                                                query.prepare("insert into " +Localtable+ "(RecordID,VIN,CarID,PID,MaterialNumber,PIN, TPS, CarSignature, TYPE, LocalDateTime, FisMatch) values (?, ?, ?, ?, ?, ?, ?, ?, ?, now(),?)") ;

                                                query.addBindValue(value["RecordID"].toInt());
                                                query.addBindValue(value["VIN"].toString());
                                                query.addBindValue(value["CarID"].toString());
                                                query.addBindValue(value["PID"].toString());
                                                query.addBindValue(value["MaterialNumber"].toString());
                                                query.addBindValue(value["PIN"].toString());
                                                query.addBindValue(value["TPS"].toString());
                                                query.addBindValue(value["CarSignature"].toString());
                                                query.addBindValue(value["TYPE"].toString());

                                                QJson::Serializer serializer;
                                                bool ok;
                                                QByteArray match = serializer.serialize(value["PRFAM"],&ok);

                                                if(ok)
                                                    query.addBindValue(match);
                                                else
                                                {
                                                    query.addBindValue(match);
                                                    DTdebug() << "match serialze fail:" << serializer.errorMessage()<<"FisMatch:"<<value["FisMatch"];
                                                }

                                                if(!query.exec())
                                                    DTdebug() <<"update FisPreview fail "<<query.lastError();
                                                else {
                                                    DTdebug() << "Fis dowload success" ;
                                                }
                                            }
                                        }
                                    }
                                }
                                else
                                    DTdebug()<<"What's wrong"<<bytes;
                            }
                            else
                            {
                                DTdebug()<<"Get FisPreview fail ";//    <<result["Error"].toString();
                                if(result["ErrorCode"].toString()== "1")
                                {
                                    DTdebug()<<"Server Json parse fail"<<json;
                                }
                            }
                        }
                    }
                    else if(reply->error() != QNetworkReply::NoError)
                    {
                        DTdebug()<<"FisPreview handle errors here";
                        QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
                        //statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
                        DTdebug( )<<"FisPreview found error "<< statusCodeV.toInt()<<(int)reply->error();
                        DTdebug()<<reply->errorString();
                    }

                    reply->deleteLater();
                }
                else
                {
                    DTdebug() << "Something went wrong:" << serializer.errorMessage();
                }

            }
            mysqlClose();
        }
    }
    else       //Insert
    {
        DTdebug()<<"come in insert";
        GetTimes++;
        if(GetTimes == 120)
            GetTimes = 0;

        if(mysqlIsOpen())
        {
            strSqlSelect = QString("SELECT RecordID, IDCode, TPS, ScrewID, Torque, Angle, Curve, "
                                   "TighteningStatus, TighteningTime, Cycle, Operator,  Program, "
                                   "JobStatus,  Order_id,  `MaxValue`, `MinValue`, Channel, Type "
                                   "FROM %1 Where UploadMark=1 or UploadMark=2 and Curve !='null'"
                                   "order by RecordID limit 1").arg(SQL_TABLE_TIGHTENDATA);
            bool result = query.exec(strSqlSelect) ;


            if(result)
            {
                if(query.next())
                {
                    QString ID = query.value(0).toString();
                    QVariantMap dataMap;
                    dataMap.insert("Type","Set");
                    dataMap.insert("Target","TighteningData");
                    QVariantMap data;
                    data.insert("Version",1);
                    data.insert("ID", query.value(0).toInt());
                    if(query.value(16).toString() == "manual")
                    {
                        data.insert("IDCode", "");
                        data.insert("TestVin",query.value(1).toString());
                    }
                    else
                        data.insert("IDCode", query.value(1).toString());
                    data.insert("TPS",query.value(2).toString());
                    data.insert("ScrewID", query.value(3).toString());
                    data.insert("Torque", query.value(4).toDouble());
                    data.insert("Angle", query.value(5).toDouble());
                    data.insert("Curve", query.value(6).toString());
                    data.insert("TighteningStatus", query.value(7).toString());
                    data.insert("TighteningTime", query.value(8).toString().left(10)+" "+query.value(8).toString().right(8));
                    data.insert("Cycle", query.value(9).toInt());
                    data.insert("Operator", query.value(10).toString());
                    data.insert("Program", query.value(11).toInt());
                    data.insert("JobStatus", query.value(12).toInt());
                    data.insert("IIO", query.value(13).toInt());

                    QString maxValue = QString::number(query.value(14).toDouble(), 10, 2);
                    QString minValue = QString::number(query.value(15).toDouble(), 10, 2);

                    data.insert("MaxValue", maxValue);
                    data.insert("MinValue", minValue);

                    data.insert("Channel", query.value(16).toInt());
                    data.insert("Line_ID", Line_ID);
//                        data.insert("Station", Station);
//                        data.insert("IpAddress", WirelessIp);
                    data.insert("Workshop", "Assembly");
                    data.insert("WorkShift", "");
                    dataMap.insert("Parameter",data);

                    QJson::Serializer serializer;
                    bool ok;
                    QByteArray json = serializer.serialize(dataMap, &ok);

                    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
                    req.setHeader(QNetworkRequest::ContentLengthHeader, json.length());

                    if (ok)
                    {
                        DTdebug() << "post RecordID:"<<query.value(0).toInt()<<"Cycle:"<<query.value(9).toInt();
                        QNetworkReply *reply = manager->post(req,json);
                        reply->ignoreSslErrors();
                        QTime t_time;
                        t_time.start();

                        bool timeout = false;

                        while (!reply->isFinished()) {
                            QApplication::processEvents();
                            if (t_time.elapsed() >= TIMEOUT) {
                                timeout = true;
                                DTdebug()<<"insert reply timeout";
                                break;
                            }
                        }
                        if (!timeout && reply->error() == QNetworkReply::NoError)
                        {
                            QByteArray bytes = reply->readAll();//上传拧紧数据后回复
                            QJson::Parser parser;
                            bool ok;

                            QVariantMap result = parser.parse(bytes, &ok).toMap();
                            if (!ok) {
                                DTdebug()<<"post Insert An error occurred during parsing"<<bytes;
                            }
                            else
                            {
                                if(result["Result"].toBool())//回复结果为true
                                {
                                    //确定是拧紧数据上传的回复
                                    if(result["Type"].toString()=="Set" && result["Target"].toString()=="TighteningData")
                                    {
                                        QString RecordID = result["ID"].toString();
                                        QString Cycle = result["Cycle"].toString();

                                        QString sqlUpdata = QString("UPDATE tighteningDatas SET UploadMark = 5,UploadTime = now() WHERE RecordID = %1").arg(RecordID);

                                        if(query.exec(sqlUpdata))
                                        {
                                            DTdebug()<<"update 5 success: RecordID:"<<RecordID<<"Cycle:"<<Cycle;
                                        }
                                        else
                                        {
                                            DTdebug()<<"update 5 fail: RecordID:"<<RecordID<<"Cycle:"<<Cycle<<query.lastError() << "sql:" <<sqlUpdata ;
                                        }
                                    }
                                    else
                                        DTdebug()<<"What's wrong"<<bytes;
                                }
                                else
                                {
                                    if(bytes == "")
                                    {
                                        DTdebug()<<"reply is null";
                                    }
                                    else
                                    {
                                        if(result["ErrorCode"].toString()== "1")
                                        {
                                            DTdebug()<<"Server Json parse fail"<<json;
                                        }
                                        QString RecordID = result["ID"].toString();
                                        QString Cycle = result["Cycle"].toString();
                                        DTdebug()<<"Reinsert fail RecordID:"<<RecordID<<"Cycle:"<<Cycle;
                                        if(wrongRecordID != RecordID.toInt())
                                        {
                                            wrongRecordID = RecordID.toInt();
                                            wrongTimes++;
                                        }
                                        else
                                        {
                                            wrongTimes++;
                                            if(wrongTimes == 10)
                                            {
                                                if(query.exec("UPDATE tighteningDatas SET UploadMark = 6, UploadTime = now() WHERE RecordID = "+RecordID))
                                                {
                                                    wrongRecordID = -1;
                                                    wrongTimes = 0;
                                                    DTdebug()<<"update 6 success: RecordID:"<<RecordID<<"Cycle:"<<Cycle;
                                                }
                                                else
                                                {
                                                    DTdebug()<<"update 6 fail: RecordID:"<<RecordID<<"Cycle:"<<Cycle<<query.lastError();
                                                }
                                            }
                                            else if(wrongTimes >10)
                                                wrongTimes = 0;
                                        }
                                    }
                                }
                            }
                        }
                        else if(reply->error() != QNetworkReply::NoError)
                        {
                            DTdebug()<<"insert handle errors here";
                            QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
                            //statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
                            DTdebug( )<<"insert found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error();
                            DTdebug()<<reply->errorString();
                        }

                        reply->deleteLater();
                    }
                    else
                    {
                        DTdebug() << "Something went wrong:" << serializer.errorMessage();
                    }
                }
                else {
                    DTdebug() << "have not data" ;
                }
            }
            else {
                DTdebug()<<"SELECT fail "<<query.lastError()<<strSqlSelect;
            }
            mysqlClose();
        }
    }

//    qDebug()<<"point[202]:"<<GetTimes;
    QTimer::singleShot(2000,this,SLOT(dataInsert()));
}

void DT_HTTP::mysqlConnect()
{
    db=QSqlDatabase::addDatabase("QMYSQL","ReinsertMySQL");
    db.setHostName("localhost");
    db.setDatabaseName("Tighten");
    db.setUserName("root");
    db.setPassword("123456");
    query = QSqlQuery(db);
}


// 本地mysql open
bool DT_HTTP::mysqlIsOpen()
{
    if(!db.isOpen() || !db.contains("ReinsertMySQL")){
        if(db.open()){
            qDebug()<<"open ReinsertMySQL success";
        }else{
            qDebug()<<"open ReinsertMySQL faile:"<<db.lastError().text();
        }
    }

    if(db.isOpen() && db.contains("ReinsertMySQL")){
        return true;
    }else{
        return false;
    }
}


void DT_HTTP::mysqlClose()
{
    if(db.isOpen()){
        db.close();
    }
}
