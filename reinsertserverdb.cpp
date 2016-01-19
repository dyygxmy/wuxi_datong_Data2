#include "reinsertserverdb.h"
#include "GlobalVarible.h"
ReInsertServerDb::ReInsertServerDb(QObject *parent) :
    QObject(parent)
{
    m_thread.start();
    this->moveToThread(&m_thread);
    connect(&m_thread,SIGNAL(finished()),this,SLOT(printDead()));
}


void ReInsertServerDb::reinsert_start()
{
    qDebug()<<"reInsertServerDb thread start";

    QSettings *configIniRead = new QSettings("/config.ini", QSettings::IniFormat);
    db1=QSqlDatabase::addDatabase("QODBC","ReinsertCurve");
    db1.setConnectOptions("SQL_ATTR_LOGIN_TIMEOUT=1;SQL_ATTR_CONNECTION_TIMEOUT=1");
    db1.setDatabaseName("sqlcurve");
    db1.setPort(1433);
    db1.setUserName(configIniRead->value("baseinfo/SQLUserName").toString());
    db1.setPassword(configIniRead->value("baseinfo/SQLPassword").toString());
    query1 = QSqlQuery(db1);

    db2=QSqlDatabase::addDatabase("QMYSQL","ReinsertMySQL");
    db2.setHostName("localhost");
    db2.setDatabaseName("Tighten");
    db2.setUserName("root");
    db2.setPassword("123456");
    query2 = QSqlQuery(db2);
    query4 = QSqlQuery(db2);

    db3=QSqlDatabase::addDatabase("QODBC","ReinsertData");
    db3.setConnectOptions("SQL_ATTR_LOGIN_TIMEOUT=1;SQL_ATTR_CONNECTION_TIMEOUT=1");
    db3.setDatabaseName("sqltighten");
    db3.setPort(1433);
    db3.setUserName(configIniRead->value("baseinfo/SQLUserName").toString());
    db3.setPassword(configIniRead->value("baseinfo/SQLPassword").toString());
    query3 = QSqlQuery(db3);

    delete configIniRead;
    //    if(!db1.isOpen())
    //        curvesqlopen();
    //    if(!db2.isOpen())
    //        mysqlopen();
    //    if(!db3.isOpen())
    //        datasqlopen();

    connect(&m_insert,SIGNAL(timeout()),this,SLOT(timer_insert()));
    m_insert.start(5000);
}

void ReInsertServerDb::timer_insert()
{
    //5秒 遍历本地数据库标志位 处理
    if(WIFI_STATE)
    {
        if(!db1.isOpen()||!QSqlDatabase::contains("ReinsertCurve"))
            curvesqlopen();
        if(!db2.isOpen()||!QSqlDatabase::contains("ReinsertMySQL"))
            mysqlopen();
        if(!db3.isOpen()||!QSqlDatabase::contains("ReinsertData"))
            datasqlopen();
        bool datasql = false;
        bool curvesql = false;
        int uploadmark = 0;
        QString msg="";
        if(db2.isOpen() && QSqlDatabase::contains("ReinsertMySQL"))
        {
            query2.exec("SELECT RecordID, IDCode, ScrewID, Torque, Angle, Curve, TighteningStatus, TighteningTime,UploadMark,Cycle,Operator,Program,Channel FROM TighteningDatas Where UploadMark >1 order by RecordID limit 10");
            while(query2.next())
            {

                QByteArray VIN_PIN_byte = query2.value(1).toString().toAscii();
                for (int i = 0; i < VIN_PIN_byte.length();i += 2)
                {
                    VIN_PIN_byte[i] = ~VIN_PIN_byte[i];       //偶数位取反
                }
                QString vin_pin_sql;
                vin_pin_sql = QString(VIN_PIN_byte.toBase64());

                if(query2.value(8).toInt()==2)
                {
                    if(db3.isOpen() && QSqlDatabase::contains("ReinsertData"))
                    {
                        qDebug()<<"*****************come in 2*************************";
                        query3.prepare("INSERT INTO Data.TighteningData(IDCode, ScrewID, Torque, Angle, TighteningStatus, TighteningTime, Cycle, Operator, Program, Channel, Line_ID)"
                                       "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
                        query3.addBindValue(vin_pin_sql);
                        query3.addBindValue(query2.value(2).toInt());
                        query3.addBindValue(query2.value(3).toString());
                        query3.addBindValue(query2.value(4).toString());
                        query3.addBindValue(query2.value(6).toString());
                        query3.addBindValue(query2.value(7).toString());
                        query3.addBindValue(query2.value(9).toInt());
                        query3.addBindValue(query2.value(10).toString());
                        query3.addBindValue(query2.value(11).toInt());
                        query3.addBindValue(query2.value(12).toInt());
                        query3.addBindValue(Line_ID);
                        if(query3.exec())
                        {
                            //msg= QString("reinsertserverdb datasql insert success: Cycle")+query2.value(9).toString();
                          // qDebug()<<msg;
                            if(query4.exec("UPDATE TighteningDatas SET UploadMark = 1,UploadTime = now() WHERE RecordID = "+query2.value(0).toString()))
                            {
                                msg= QString("reinsertserverdb datasql update success: Cycle:")+query2.value(9).toString()+QString("||UploadMark:1");
                                qDebug()<<msg;
                            }
                            else
                            {
                                msg= QString("reinsertserverdb datasql update fail: Cycle:")+query2.value(9).toString()+QString("||UploadMark:2");
                                qDebug()<<msg;
                            }
                        }
                        else
                        {
                            msg= QString("reinsertserverdb datasql insert fail: Cycle:")+query2.value(9).toString();
                            qDebug()<<msg;
                        }
                    }
                }
                else if(query2.value(8).toInt()==3)
                {
                    if(db1.isOpen()&& QSqlDatabase::contains("ReinsertCurve"))
                    {
                        qDebug()<<"*****************come in 3*************************";
                        query1.prepare("INSERT INTO Curve.Curves(Curve) VALUES (?)");
                        query1.addBindValue(query2.value(5).toString());

                        if(!query1.exec())
                        {

                            msg= QString("reinsertserverdb curvesql Curves insert fail: Cycle:")+query2.value(9).toString();
                            qDebug()<<msg;
                        }
                        else
                        {
                            msg= QString("reinsertserverdb curvesql Curves insert success: Cycle:")+query2.value(9).toString();
                            qDebug()<<msg;
                            curvesql = true;

                        }

                        query1.prepare("INSERT INTO Data.TighteningDatas(IDCode, ScrewID, Torque, Angle, Curve, TighteningStatus, TighteningTime, Cycle, Operator, Program, Channel, Line_ID)"
                                       "VALUES (?, ?, ?, ?, @@IDENTITY, ?, ?, ?, ?, ?, ?, ?)");
                        query1.addBindValue(vin_pin_sql);
                        query1.addBindValue(query2.value(2).toInt());
                        query1.addBindValue(query2.value(3).toString());
                        query1.addBindValue(query2.value(4).toString());
                        //query1.addBindValue("@@IDENTITY");
                        query1.addBindValue(query2.value(6).toString());
                        query1.addBindValue(query2.value(7).toString());
                        //query1.addBindValue("convert(varchar(10),getdate(),120)");
                        query1.addBindValue(query2.value(9).toInt());
                        query1.addBindValue(query2.value(10).toString());
                        query1.addBindValue(query2.value(11).toInt());
                        query1.addBindValue(query2.value(12).toInt());
                        query1.addBindValue(Line_ID);

                        if(!query1.exec())
                        {
                            curvesql = false;
                            msg= QString("reinsertserverdb curvesql TighteningDatas insert fail: Cycle:")+query2.value(9).toString();
                            qDebug()<<msg;
                        }
                        else
                        {
                            msg= QString("reinsertserverdb curvesql TighteningDatas insert success: Cycle:")+query2.value(9).toString();
                            qDebug()<<msg;
                            //curvesql = true;

                        }

                        if(curvesql)
                        {
                            if(query4.exec("UPDATE TighteningDatas SET UploadMark = 1,UploadTime = now() WHERE RecordID = "+query2.value(0).toString()))
                            {
                                msg= QString("reinsertserverdb curvesql update success: Cycle:")+query2.value(9).toString()+QString("||UploadMark:1");
                                qDebug()<<msg;
                            }
                            else
                            {
                                msg= QString("reinsertserverdb curvesql update fail: Cycle:")+query2.value(9).toString()+QString("||UploadMark:3");
                                qDebug()<<msg;
                            }
                        }
                    }
                }
                else if(query2.value(8).toInt()==4)
                {
                    if(db3.isOpen()&& QSqlDatabase::contains("ReinsertData"))
                    {
                        qDebug()<<"*****************come in 4*************************";
                        query3.prepare("INSERT INTO Data.TighteningData(IDCode, ScrewID, Torque, Angle, TighteningStatus, TighteningTime, Cycle, Operator, Program, Channel, Line_ID)"
                                       "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
                        query3.addBindValue(vin_pin_sql);
                        query3.addBindValue(query2.value(2).toInt());
                        query3.addBindValue(query2.value(3).toString());
                        query3.addBindValue(query2.value(4).toString());
                        query3.addBindValue(query2.value(6).toString());
                        query3.addBindValue(query2.value(7).toString());
                        query3.addBindValue(query2.value(9).toInt());
                        query3.addBindValue(query2.value(10).toString());
                        query3.addBindValue(query2.value(11).toInt());
                        query3.addBindValue(query2.value(12).toInt());
                        query3.addBindValue(Line_ID);
                        if(!query3.exec())
                        {
                            datasql = false;
                            msg= QString("reinsertserverdb datasql insert fail: Cycle:")+query2.value(9).toString();
                            qDebug()<<msg;
                        }
                        else
                        {
                            msg= QString("reinsertserverdb datasql insert success: Cycle:")+query2.value(9).toString();
                            qDebug()<<msg;
                            datasql = true;
                        }
                    }
                    if(db1.isOpen()&& QSqlDatabase::contains("ReinsertCurve"))
                    {
                        query1.prepare("INSERT INTO Curve.Curves(Curve) VALUES (?)");
                        query1.addBindValue(query2.value(5).toString());

                        if(!query1.exec())
                        {

                            msg= QString("reinsertserverdb curvesql Curves insert fail: Cycle:")+query2.value(9).toString();
                            qDebug()<<msg;
                        }
                        else
                        {
                            msg= QString("reinsertserverdb curvesql Curves insert success: Cycle:")+query2.value(9).toString();
                            qDebug()<<msg;
                            curvesql = true;
                        }

                        query1.prepare("INSERT INTO Data.TighteningDatas(IDCode, ScrewID, Torque, Angle, Curve, TighteningStatus, TighteningTime, Cycle, Operator, Program, Channel, Line_ID)"
                                       "VALUES (?, ?, ?, ?, @@IDENTITY, ?, ?, ?, ?, ?, ?, ?)");
                        query1.addBindValue(vin_pin_sql);
                        query1.addBindValue(query2.value(2).toInt());
                        query1.addBindValue(query2.value(3).toString());
                        query1.addBindValue(query2.value(4).toString());
                        //query1.addBindValue("@@IDENTITY");
                        query1.addBindValue(query2.value(6).toString());
                        query1.addBindValue(query2.value(7).toString());
                        //query1.addBindValue("convert(varchar(10),getdate(),120)");
                        query1.addBindValue(query2.value(9).toInt());
                        query1.addBindValue(query2.value(10).toString());
                        query1.addBindValue(query2.value(11).toInt());
                        query1.addBindValue(query2.value(12).toInt());
                        query1.addBindValue(Line_ID);

                        if(!query1.exec())
                        {
                            curvesql = false;
                            msg= QString("reinsertserverdb curvesql TighteningDatas insert fail: Cycle:")+query2.value(9).toString();
                            qDebug()<<msg;
                        }
                        else
                        {
                            msg= QString("reinsertserverdb curvesql TighteningDatas insert success: Cycle:")+query2.value(9).toString();
                            qDebug()<<msg;
                            //curvesql = true;
                        }
                    }
                    if(curvesql && datasql)
                        uploadmark = 1;//all successful
                    else if(curvesql && !datasql)
                        uploadmark = 2;//data not successful
                    else if(!curvesql && datasql)
                        uploadmark = 3;
                    else if(!curvesql && !datasql)
                        uploadmark = 4;

                    if(uploadmark!=4)
                    {
                        if(query4.exec("UPDATE TighteningDatas SET UploadMark = "+QString::number(uploadmark)+",UploadTime = now() WHERE RecordID = "+query2.value(0).toString()))
                        {
                            msg= QString("reinsertserverdb update success: Cycle:")+query2.value(9).toString()+QString("||UploadMark:")+QString::number(uploadmark);
                            qDebug()<<msg;
                        }
                        else
                        {
                            msg= QString("reinsertserverdb update fail: Cycle:")+query2.value(9).toString()+QString("||UploadMark:")+QString::number(uploadmark);
                            qDebug()<<msg;
                        }
                    }
                }
            }
        }
        sqlclose();
    }
}

void ReInsertServerDb::printDead()
{
    qFatal("the thread reinsertserverdb  deaded") ;
}

//数据服务器open
void ReInsertServerDb::datasqlopen()
{
    if(QSqlDatabase::contains("ReinsertData")){
        db3 = QSqlDatabase::database("ReinsertData");
    }else{
        db3=QSqlDatabase::addDatabase("QODBC","ReinsertData");
        db3.setConnectOptions("SQL_ATTR_LOGIN_TIMEOUT=1;SQL_ATTR_CONNECTION_TIMEOUT=1");

        QSettings *configIniRead = new QSettings("/config.ini", QSettings::IniFormat);
        db3.setDatabaseName("sqltighten");
        db3.setPort(1433);
        db3.setUserName(configIniRead->value("baseinfo/SQLUserName").toString());
        db3.setPassword(configIniRead->value("baseinfo/SQLPassword").toString());
        query3 = QSqlQuery(db3);
        delete configIniRead;
    }
    if(!db3.open())
    {
        if(!db3.open())
        {
            qDebug()<< "reinsert datasql "<<db3.lastError().text();
        }else
        {
            qDebug()<< "reinsert datasql open ok 2";
        }
    }else
    {
        //qDebug()<< "reinsert datasql open ok 1";
    }
}

//曲线服务器open
void ReInsertServerDb::curvesqlopen()
{
    if(QSqlDatabase::contains("ReinsertCurve")){
        db1 = QSqlDatabase::database("ReinsertCurve");
    }else{
        db1=QSqlDatabase::addDatabase("QODBC","ReinsertCurve");
        db1.setConnectOptions("SQL_ATTR_LOGIN_TIMEOUT=1;SQL_ATTR_CONNECTION_TIMEOUT=1");
        QSettings *configIniRead = new QSettings("/config.ini", QSettings::IniFormat);
        db1.setDatabaseName("sqlcurve");
        db1.setPort(1433);
        db1.setUserName(configIniRead->value("baseinfo/SQLUserName").toString());
        db1.setPassword(configIniRead->value("baseinfo/SQLPassword").toString());
        query1 = QSqlQuery(db1);
        delete configIniRead;
    }

    if(!db1.open())
    {
        if(!db1.open())
        {
            qDebug()<<"reinsert curvesql"<<db1.lastError().text();
        }
        else
        {
            qDebug()<< "reinsert curvesql open ok 2";
        }

    }else
    {
        //qDebug()<< "reinsert curvesql open ok 1";
    }
}

//本地mysql open
void ReInsertServerDb::mysqlopen()
{
    if(QSqlDatabase::contains("ReinsertMySQL")){
        db2 = QSqlDatabase::database("ReinsertMySQL");
    }else{
        db2=QSqlDatabase::addDatabase("QMYSQL","ReinsertMySQL");
        db2.setHostName("localhost");
        db2.setDatabaseName("Tighten");
        db2.setUserName("root");
        db2.setPassword("123456");
        query2 = QSqlQuery(db2);
        query4 = QSqlQuery(db2);
    }

    if(!db2.open())
    {
        if(!db2.open())
        {
            qDebug()<< "reinsert localmysql "<< db2.lastError().text();
        }else
        {
            qDebug()<< "reinsert localmysql open ok 2";
        }
    }else
    {
        //qDebug()<< "reinsert localmysql open ok 1";
    }
}

//数据库关闭
void ReInsertServerDb::sqlclose()
{
    if(db1.isOpen())
        db1.close();
    if(db2.isOpen())
        db2.close();
    if(db3.isOpen())
        db3.close();
}

