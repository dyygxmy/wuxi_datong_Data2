#include "repaircurve.h"

repairCurve::repairCurve(QObject *parent) :
    QObject(parent)
{
    this->moveToThread(&repair_thread);
    repair_thread.start();
    mysqlConnect();
}

void repairCurve::repairStart()
{
    FUNC() ;
    sleep(5);
    connect(&selectTimer,SIGNAL(timeout()),this,SLOT(selectData()));
    selectTimer.start(10*1000);
}


void repairCurve::mysqlConnect()
{
    db=QSqlDatabase::addDatabase("QMYSQL","repairCurvemysqlconnection");
    db.setHostName("localhost");
    db.setDatabaseName("Tighten");
    db.setUserName("root");
    db.setPassword("123456");
    query = QSqlQuery(db);
}


bool repairCurve::mysqlIsOpen()
{
    if(!db.isOpen() || !db.contains("repairCurvemysqlconnection")){
        if(db.open()){
            qDebug()<<"open repairCurvemysqlconnection success";
        }else{
            qDebug()<<"open repairCurvemysqlconnection faile:"<<db.lastError().text();
        }
    }

    if(db.isOpen() && db.contains("repairCurvemysqlconnection")){
        return true;
    }else{
        return false;
    }
}

/*
*     数据库关闭
*/
void repairCurve::sqlclose()
{
    if(db.isOpen())
        db.close();
}

void repairCurve::selectData()
{
//    qDebug()<<"point[selectData_0]:";
    if(mysqlIsOpen())
    {
        //找最近10条的拧紧数据，如果有缺失曲线的用循环号去要曲线再补上
        QString strSelect = "select RecordID,Cycle from tighteningDatas "
                "where RecordID >(select max(RecordID)-10 from tighteningDatas) "
                "and Curve = 'Curve is null' order by RecordID DESC";
        bool selectSuccess = query.exec(strSelect);
        int numRows=query.numRowsAffected();

        if(selectSuccess && numRows>0)
        {
            query.numRowsAffected();
            if(query.next())
            {
                QString cycle = query.value(1).toString();
                qDebug()<< "missCurveCycle:" << cycle;
                Q_EMIT signalRepaieCurve(cycle);
            }
        }
        else if(!selectSuccess)
        {
            DTdebug() << query.lastError().text() ;
        }
        else
        {
            DTdebug()<< "no curve is null";
        }
        sqlclose();
    }
//    qDebug()<<"point[selectData_1]:";
}
