#include "sqlthread.h"

  SqlThread::SqlThread(QObject *parent) :
      QObject(parent)
{
      this->moveToThread(&m_thread);
      m_thread.start();
      mysqlConnect();
}

void SqlThread::mysqlConnect()
{
    db=QSqlDatabase::addDatabase("QMYSQL","mysqlconnections");
    db.setHostName("localhost");
    db.setDatabaseName("Tighten");
    db.setUserName("root");
    db.setPassword("123456");
    query = QSqlQuery(db);

}
/*
     数据库关闭
*/
void SqlThread::sqlclose()
{
    if(db.isOpen())
        db.close();
}
//本地mysql open
bool SqlThread::mysqlIsOpen()
{
    if(!db.isOpen() || !db.contains("mysqlconnections")){
        if(db.open()){
            qDebug()<<"open mysqlconnections success";
        }else{
            qDebug()<<"open mysqlconnections faile:"<<db.lastError().text();
        }
    }

    if(db.isOpen() && db.contains("mysqlconnections")){
        return true;
    }else{
        return false;
    }
}

void SqlThread::sqlinsert(QString *data_models)
{

    DTdebug() << "here is sqlthread";

    /*******************************
     * 数据模型
    data_model[0] = DATE_blc;
    data_model[1] = TIME_blc;
    data_model[2] = STATE_blc;
    data_model[3] = MI_blc;
    data_model[4] = WI_blc;
    data_model[5] = SCREWID_SQL;
    data_model[6] = VIN_PIN_SQL;
    data_model[7] = Cycle_CSR;
    data_model[8] = CURVE_STR;
    data_model[9] = Program;
    data_model[10] = Channel;
    *******************************/
    //DTdebug() << data_model[0] << data_model[1] <<data_model[2] <<data_model[3] <<data_model[4] <<data_model[5] <<data_model[6] ;
    //bool datasql = false;
   // bool curvesql = false;
    int uploadmark = 0;
    QString msg="";
    QString *data_model = data_models;
    int screwid_sql = data_model[5].toInt();
    int Cycle = data_model[7].toInt();
    int Program = data_model[9].toInt();
    int Channel = data_model[10].toInt();
    QString vin =  data_model[6].mid(0,17); //本来在拧紧线程里截取过了，但有时候还是带着车型信息。至于我为什么写在这，因为第一次见这代码，急着改，就省事点。

    QString TighteningTime_date = data_model[0];
    QString TighteningTime_time = data_model[1];
    QString TighteningStatus = data_model[2];
    QString Torque = data_model[3];
    QString Angle = data_model[4];
    QString tighteningID = data_model[7];
    QString Curve = data_model[8];
    if(tighteningID == "-1")
    {
        uploadmark = 1;
    }
    else
    {
        uploadmark = 2;
    }

   //**************************本地数据库*******************************************
    if(mysqlIsOpen()){
        query.exec("SELECT MAX(RecordID) FROM tighteningDatas");
        query.next();
        int RecordIDMax = query.value(0).toInt();

        query.exec("SELECT TPS FROM tighteningDatas");
        query.next();
        QString tps = query.value(0).toString();

        query.exec("SELECT COUNT(*) FROM tighteningDatas");
        query.next();
        int numRows = query.value(0).toInt();
        if(numRows>10000)
        {
            DTdebug()<<"delete tighten data" ;
            query.exec("delete from tighteningDatas where RecordID in (select x.RecordID from (select RecordID from tighteningDatas order by RecordID limit  100) as  x)");
        }
        query.prepare("INSERT INTO tighteningDatas(RecordID, IDCode, TPS, ScrewID, Torque, Angle, Curve, TighteningStatus, TighteningTime, LocalDateTime, Operator, UploadMark, UploadTime, Cycle, Program, Channel)"
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, now(), ?, ?, ?, ?, ?, ?)");
        query.addBindValue(RecordIDMax+1);//RecordID
        query.addBindValue(vin);//IDCode
        query.addBindValue(tps);//TPS
        query.addBindValue(screwid_sql);//ScrewID
        query.addBindValue(Torque);//Torque
        query.addBindValue(Angle);//Angle

        if(Curve.size() < 32)//Curve
            query.addBindValue(Curve);
        else
            query.addBindValue(Curve.mid(32));
        query.addBindValue(TighteningStatus);//TighteningStatus
        query.addBindValue(TighteningTime_date + " " + TighteningTime_time);//TighteningTime
        //query.addBindValue(now());//LocalDateTime
        query.addBindValue(Operator);//Operator
        query.addBindValue(uploadmark);//UploadMark
        query.addBindValue("");//UploadTime
        query.addBindValue(Cycle);//Cycle
        query.addBindValue(Program);//Program
        query.addBindValue(Channel);//Channel


        if(!query.exec())
        {
            DTdebug() << query.lastError().text();
            if(!query.exec())
            {
                if(!query.exec())
                {
                    //插入3次不成功存文件
                    //重启mysql 服务记录 缓存文件
                    emit send_mysqlerror();
                }
                else
                {
                    msg= QString("SqlThread mysql insert success3: IDCode:")+vin+QString("||ScrewID:")+QString::number(screwid_sql)+QString("||Torque:")+data_model[3]+QString("||Angle:")+data_model[4]+QString("||TighteningStatus:")+data_model[2]+QString("||TighteningTime:")+data_model[0]+QString("||")+data_model[1]+QString("||LocalDateTime:")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd")+QString("||Operator:")+Operator+QString("||UploadMark:")+QString::number(uploadmark)+QString("||Cycle:")+data_model[7]+QString("||Program:")+data_model[9]+QString("||Channel:")+data_model[10];
                    DTdebug()<<msg;
                }
            }
            else
            {
                msg= QString("SqlThread mysql insert success2: IDCode:")+vin+QString("||ScrewID:")+QString::number(screwid_sql)+QString("||Torque:")+data_model[3]+QString("||Angle:")+data_model[4]+QString("||TighteningStatus:")+data_model[2]+QString("||TighteningTime:")+data_model[0]+QString("||")+data_model[1]+QString("||LocalDateTime:")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd")+QString("||Operator:")+Operator+QString("||UploadMark:")+QString::number(uploadmark)+QString("||Cycle:")+data_model[7]+QString("||Program:")+data_model[9]+QString("||Channel:")+data_model[10]+QString("||RecordID:")+QString::number(RecordIDMax+1);
                DTdebug()<<msg;
            }
        }
        else
        {
            msg= QString("SqlThread mysql insert success1: IDCode:")+vin+QString("||ScrewID:")+QString::number(screwid_sql)+QString("||Torque:")+data_model[3]+QString("||Angle:")+data_model[4]+QString("||TighteningStatus:")+data_model[2]+QString("||TighteningTime:")+data_model[0]+QString("||")+data_model[1]+QString("||LocalDateTime:")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd")+QString("||Operator:")+Operator+QString("||UploadMark:")+QString::number(uploadmark)+QString("||Cycle:")+data_model[7]+QString("||Program:")+data_model[9]+QString("||Channel:")+data_model[10]+QString("||RecordID:")+QString::number(RecordIDMax+1);
            DTdebug()<<msg;

        }
        sqlclose();
    }

}


void SqlThread::sqlinsert(QVariant DataVar)
{
    DTdebug() << "DataVar" << DataVar;
    DATA_STRUCT dataStruct;
    dataStruct = DataVar.value<DATA_STRUCT>();
    QString data_model[16];
    for(int i = 0; i<16; i++)
    {
        data_model[i] = dataStruct.data_model[i];
    }

//    QString *data_model = data_models;
//    DTdebug() << "here is sqlthread";


    int uploadmark = 0;
    QString msg="";
    int screwid_sql = data_model[5].toInt();
    int Cycle = data_model[7].toInt();
    int Program = data_model[9].toInt();
    int Channel = data_model[10].toInt();
    QString vin =  data_model[6].mid(0,17); //本来在拧紧线程里截取过了，但有时候还是带着车型信息。至于我为什么写在这，因为第一次见这代码，急着改，就省事点。
    qDebug()<<"saveTightenData:"<< Program << Channel << Cycle;

    if(data_model[7] == "-1")
    {
        uploadmark = 1;
    }
    else
    {
        uploadmark = 2;
    }
    if(mysqlIsOpen()){
        //**************************本地数据库*******************************************
        query.exec("SELECT MAX(RecordID) FROM tighteningDatas");
        query.next();
        int RecordIDMax = query.value(0).toInt();

        query.exec("SELECT TPS FROM tighteningDatas");
        query.next();
        QString tps = query.value(0).toString();

        query.exec("SELECT COUNT(*) FROM tighteningDatas");
        query.next();
        int numRows = query.value(0).toInt();
        if(numRows>10000)
        {
            DTdebug()<<"delete tighten data" ;
            query.exec("delete from tighteningDatas where RecordID in (select x.RecordID from (select RecordID from tighteningDatas order by RecordID limit  100) as  x)");
        }
        else {

        }
        query.prepare("INSERT INTO tighteningDatas(RecordID, IDCode, TPS, ScrewID, Torque, Angle, Curve, TighteningStatus, TighteningTime, LocalDateTime, Operator, UploadMark, UploadTime, Cycle, Program, Channel)"
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, now(), ?, ?, ?, ?, ?, ?)");
        query.addBindValue(RecordIDMax+1);
        query.addBindValue(vin);
        query.addBindValue(tps);
        query.addBindValue(screwid_sql);
        query.addBindValue(data_model[3]);
        query.addBindValue(data_model[4]);
        //曲线数据
        if(data_model[8].size() < 32)
            query.addBindValue(data_model[8]);
        else
            query.addBindValue(data_model[8].mid(32));

        query.addBindValue(data_model[2]);
        query.addBindValue(data_model[0]+" "+data_model[1]);
        //query.addBindValue(now());
        query.addBindValue(Operator);
        query.addBindValue(uploadmark);
        query.addBindValue("");
        query.addBindValue(Cycle);
        query.addBindValue(Program);
        query.addBindValue(Channel);
        if(!query.exec())
        {
            DTdebug() << query.lastError().text();
            if(!query.exec())
            {
                if(!query.exec())
                {
                    //插入3次不成功存文件
                    //重启mysql 服务记录 缓存文件
                    emit send_mysqlerror();
                }
                else
                {
                    msg= QString("SqlThread mysql insert success3: IDCode:")+vin+QString("||ScrewID:")+QString::number(screwid_sql)+QString("||Torque:")+data_model[3]+QString("||Angle:")+data_model[4]+QString("||TighteningStatus:")+data_model[2]+QString("||TighteningTime:")+data_model[0]+QString("||")+data_model[1]+QString("||LocalDateTime:")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd")+QString("||Operator:")+Operator+QString("||UploadMark:")+QString::number(uploadmark)+QString("||Cycle:")+data_model[7]+QString("||Program:")+data_model[9]+QString("||Channel:")+data_model[10];
                    DTdebug()<<msg;
                }
            }
            else
            {
                msg= QString("SqlThread mysql insert success2: IDCode:")+vin+QString("||ScrewID:")+QString::number(screwid_sql)+QString("||Torque:")+data_model[3]+QString("||Angle:")+data_model[4]+QString("||TighteningStatus:")+data_model[2]+QString("||TighteningTime:")+data_model[0]+QString("||")+data_model[1]+QString("||LocalDateTime:")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd")+QString("||Operator:")+Operator+QString("||UploadMark:")+QString::number(uploadmark)+QString("||Cycle:")+data_model[7]+QString("||Program:")+data_model[9]+QString("||Channel:")+data_model[10]+QString("||RecordID:")+QString::number(RecordIDMax+1);
                DTdebug()<<msg;
            }
        }
        else
        {
            msg= QString("SqlThread mysql insert success1: IDCode:")+vin+QString("||ScrewID:")+QString::number(screwid_sql)+QString("||Torque:")+data_model[3]+QString("||Angle:")+data_model[4]+QString("||TighteningStatus:")+data_model[2]+QString("||TighteningTime:")+data_model[0]+QString("||")+data_model[1]+QString("||LocalDateTime:")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd")+QString("||Operator:")+Operator+QString("||UploadMark:")+QString::number(uploadmark)+QString("||Cycle:")+data_model[7]+QString("||Program:")+data_model[9]+QString("||Channel:")+data_model[10]+QString("||RecordID:")+QString::number(RecordIDMax+1);
            DTdebug()<<msg;
        }
        sqlclose();
    }

}

void SqlThread::receiveConfigureAll(int howmuchProNnum,int whichar,int whichpronumis,int whichoption)
{
    QString screwid ="";
    QString protmp = "";
    QString vin_pin_sql = VIN_PIN_SQL;
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    QString data_model[11];

    for( int k = whichpronumis;k <21;k++)
    {

        if(!howmuchProNnum)  //非选配
        {
            //DTdebug() << "come all 2";
            lsNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/LSNumber").append(QString::number(k))).toString();
            protmp = config->value(QString("carinfo").append(QString::number(whichar)).append("/ProNum").append(QString::number(k))).toString();
            screwid = config->value(QString("carinfo").append(QString::number(whichar)).append("/LuoSuanNum").append(QString::number(k))).toString();

            if(enablenumberLeft)
            {
                DTdebug() << enablenumberLeft << "enablenum";
                lsNum = QString::number(enablenumberLeft);
            }

        }
        else
        {
            lsNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/OPLSNumber").append(QString::number(whichoption)).append(QString::number(k))).toString();
            protmp = config->value(QString("carinfo").append(QString::number(whichar)).append("/OPProNum").append(QString::number(whichoption)).append(QString::number(k))).toString();
            screwid = config->value(QString("carinfo").append(QString::number(whichar)).append("/OPLuoSuanNum").append(QString::number(whichoption)).append(QString::number(k))).toString();

        }
        if(lsNum.toInt())
        {
            QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
            for(int i = 0;i<lsNum.toInt();i++)
            {
                enablenumberLeft = 0;
                //Curve_Is_Null = true;
                data_model[0] = time.toString("yyyy-MM-dd");
                data_model[1] = time.toString("hh:mm:ss");
                data_model[2] = "NOK";
                data_model[3] = "-1";
                data_model[4] = "-1";
                data_model[5] = screwid;
                data_model[6] = vin_pin_sql.mid(0,17);
                data_model[7] = "-1";
                data_model[8] = "Curve is null";
                data_model[9] = protmp;
                data_model[10] = "-1";
                sqlinsert(data_model);
            }
        }
        else
        {
            continue;
        }
    }
    delete config;

}


//处理钥匙跳过一个的螺栓存储数据的赋值
void SqlThread::configOne(QString screwid, QString vin_pin_sql, QString protmp)
{
    QString data_model[11];
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    data_model[0] = time.toString("yyyy-MM-dd");
    data_model[1] = time.toString("hh:mm:ss");
    data_model[2] = "NOK";
    data_model[3] = "-1";
    data_model[4] = "-1";
    data_model[5] = screwid;
    data_model[6] = vin_pin_sql.mid(0,17);
    data_model[7] = "-1";
    data_model[8] = "Curve is null";
    data_model[9] = protmp;
    data_model[10] = "-1";
    sqlinsert(data_model);
}


