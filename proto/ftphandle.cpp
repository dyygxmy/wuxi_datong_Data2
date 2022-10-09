#include "ftphandle.h"
#include <unistd.h>
#include <QDateTime>
FtpHandle::FtpHandle(QObject *parent) :
    QObject(parent)
{
    this->moveToThread(&m_thread);
    m_thread.start();
    mysqlConnect();
}

void FtpHandle::ftpStart()
{
    DTdebug() << "ftpstart thread!!!!!!!!!!!!" ;
    QString path;
    path="/curveFile/";
    QDir dir(path);
    if(!dir.exists())
    {
        dir.mkpath(path);//创建多级目录
    }
    path="/curveFileInvalid/";
    QDir dir_wrong(path);
    if(!dir_wrong.exists())
    {
        dir_wrong.mkpath(path);//创建多级目录
    }
    parseFile();
}

void FtpHandle::mysqlConnect()
{
    db=QSqlDatabase::addDatabase("QMYSQL","ftpmysqlconnection");
    db.setHostName("localhost");
    db.setDatabaseName("Tighten");
    db.setUserName("root");
    db.setPassword("123456");
    query = QSqlQuery(db);
}

bool FtpHandle::mysqlIsOpen()
{
    if(!db.isOpen() || !db.contains("ftpmysqlconnection")){
        if(db.open()){
            qDebug()<<"open ftpmysqlconnection success";
        }else{
            qDebug()<<"open ftpmysqlconnection faile:"<<db.lastError().text();
        }
    }

    if(db.isOpen() && db.contains("ftpmysqlconnection")){
        return true;
    }else{
        return false;
    }
}

/*
*     数据库关闭
*/
void FtpHandle::sqlclose()
{
        if(db.isOpen())
            db.close();
}

//遍历文件夹获取有效文件的baseName和路径
void FtpHandle::FindFile()
{
    baseNameList.clear();
    filePathList.clear();
    QDir dir("/curveFile");
    QFileInfoList fileInfoList = dir.entryInfoList();
    for(int i = 0;i<fileInfoList.size();i++){
        QString baseName = fileInfoList.at(i).baseName();
        QString filePath = fileInfoList.at(i).filePath();
        if(baseName.size() > 0){
            baseNameList<<baseName;
            filePathList<<filePath;
//            break;//onece one
        }
    }
}

//管理 curveFileInvalid 文件夹
void FtpHandle::curveFileInvalidManage()
{
    QStringList filePathList;
    QDir dir("/curveFileInvalid");
    QFileInfoList fileInfoList = dir.entryInfoList();
    for(int i = 0;i<fileInfoList.size();i++){
        QString baseName = fileInfoList.at(i).baseName();
        QString filePath = fileInfoList.at(i).filePath();
        if(baseName.size() > 0){
            filePathList<<filePath;
        }
    }
//    qDebug()<<"curveFileInvalidFiles:"<<filePathList;
    while (filePathList.size() > 15) {
        QFile delFile(filePathList.first());
//        qDebug()<<"curveFileInvaliddelFile:"<<filePathList.first();
        delFile.remove();
        filePathList.removeFirst();
    }
}

//打开数据库处理相关的任务
void FtpHandle::parseFile()
{
//    qDebug()<<"point[301]";
    QDateTime startTime = QDateTime::currentDateTime();
    curveFileInvalidManage();

    FindFile();
    for(int i = 0;i<baseNameList.size();i++){//遍历曲线文件夹
        QString cycle = QString::number(baseNameList.at(i).toInt());
        QString path = filePathList.at(i);
        QString dataStr;
        QFile file(path);
        if(file.open(QFile::ReadOnly)){
            dataStr = file.readAll();//从文件中读取到的曲线数据
            file.close();
        }else{
            qDebug()<<"openFileError:"<<file.errorString();
        }

        if(mysqlIsOpen()){
            //查看当前曲线文件是否无对应拧紧数据，无效曲线文件移动到待删除文件夹
            bool isValid = query.exec("select * from tighteningDatas where Cycle="+cycle);
            int validRows = query.numRowsAffected();
            if(!isValid){
                qDebug() << "select curve valid fail:" << query.lastError().text() <<"cycle:"+cycle;
            }else{
                if(validRows > 0){
                    qDebug()<<"select curve is valid:"<<cycle;
                }else{
                    qDebug()<<"select curve is invalid:"<<cycle;
                    QString mvBash = "mv " + path + " /curveFileInvalid/";
                    system(mvBash.toLatin1().data());
                }
            }

            //获取文件baseName（即循环号）和文件内容，满足条件(Curve != '*%' and != 'Curve is null')放入表内字段
            bool inserttmp = query.exec("update tighteningDatas set Curve ='"+dataStr+"' where Cycle="+cycle+" and Curve NOT LIKE '*%'  AND Curve != 'Curve is null' order by RecordID desc limit 1");
            int numRows=query.numRowsAffected();
//            qDebug()<<"update[1]:"<<inserttmp<<numRows;
            if(!inserttmp){
                qDebug() << "curve insert fail:" << query.lastError().text() <<"cycle:"+cycle;
            }else{
                if(numRows > 0){
                    qDebug()<<"updateCurveSuccess:"<<cycle;
                }
            }

            if(QSettings("/config.ini", QSettings::IniFormat).value("/baseinfo/controlType").toString() == "Atlas"){
                //Atlas的找最近10条拧紧数据，如果有缺失曲线的用循环号去要曲线再补上
                QString strSelect = "select RecordID,Cycle from tighteningDatas "
                        "where RecordID >(select max(RecordID)-10 from tighteningDatas) "
                        "and Curve = 'Curve is null' order by RecordID DESC";
                bool selectSuccess = query.exec(strSelect);
                if(selectSuccess){
                    if(query.next()){
                        QString missCycle = query.value(1).toString();
                        qDebug()<< "missCurveCycle:" << missCycle;
                        if(missCycle.toInt() > 0){
                            emit signalRepaieCurve(missCycle);
                        }
                    }
                }else{
                    qDebug()<<"selectMissCurveCycleError:"<<query.lastError().text() ;
                }
            }

            //方法二，用当前文件去查看循环号是否已经上传成功，成功的删除
            bool isUpload = query.exec("select * from tighteningDatas where (uploadmark = 5 or uploadmark = 6) and Cycle="+cycle);
            int uploadRows = query.numRowsAffected();
            if(!isUpload){
                qDebug() << "select uploadmark fail:" << query.lastError().text() <<"cycle:"+cycle;
            }else{
                if(uploadRows > 0){
                    qDebug()<<"select uploadmark:"<<cycle;
                    QString fullCycle = cycle;
                    while(fullCycle.size() < 10){
                        fullCycle.insert(0,"0");
                    }
                    int fileIndexOf = baseNameList.indexOf(fullCycle);
                    if(fileIndexOf >= 0){
                        qDebug()<<"deleteCurveFile2:"<<filePathList.at(fileIndexOf);
                        unlink(filePathList.at(baseNameList.indexOf(fullCycle)).toLatin1().data());
                    }
                }else{
                    qDebug()<<"select no uploadmark"<<cycle;
                }
            }

        }
    }

    if(baseNameList.size() > 0){//每次处理最后一个
        checkMissCurve(QString::number(baseNameList.at(0).toInt()));
    }

//    deleteFile();

    QDateTime endTime = QDateTime::currentDateTime();
    if(startTime.msecsTo(endTime) >= 2500){
        QTimer::singleShot(0,this,SLOT(parseFile()));
    }else{
        QTimer::singleShot(2500-startTime.msecsTo(endTime),this,SLOT(parseFile()));
    }
}

void FtpHandle::deleteFile()
{
    //方法一:从数据库中查询到已经上传的循环号，删除其对应文件(这个方法不好，因为数据库中数据比较多)
    if(mysqlIsOpen()){
        bool result = query.exec("select cycle,uploadmark from tighteningDatas where uploadmark = 5 or uploadmark = 6");
        if(result){
            while(query.next()){
                QString cycle = query.value(0).toString();
                while(cycle.size() < 10){
                    cycle.insert(0,"0");
                }
                int fileIndexOf = baseNameList.indexOf(cycle);
                if(fileIndexOf >= 0){
                    qDebug()<<"deleteCurveFile:"<<filePathList.at(fileIndexOf);
                    unlink(filePathList.at(baseNameList.indexOf(cycle)).toLatin1().data());
                }
            }
        }else{
            qDebug()<<"selectUploadmarkError:"<<query.lastError().text();
        }
    }
}


void FtpHandle::checkMissCurve(QString cycle)
{
    //当前循环号前第10次拧紧有没有Curve != '*%' and != 'Curve is null'，如果有把字段变成Curve is null方便上传
    int groupBlot = 1;
    if(QSettings("/config.ini", QSettings::IniFormat).value("/baseinfo/controlType").toString() == "PMM"){
        groupBlot = 5*4;
    }
	
	QString lowCycle = QString::number(cycle.toInt() - groupBlot*10);//当前拧紧号前的第5个车的拧紧数据(一车4组螺栓，十位记一组)
    lowCycle.replace(cycle.size() - 2,2,"00");
    if(mysqlIsOpen()){
        //满足条件(Curve != '*%' and != 'Curve is null')
        bool setUpResult = query.exec("update tighteningDatas set Curve ='Curve is null' where Curve NOT LIKE '*%'  AND Curve != 'Curve is null' and Cycle < "+lowCycle);
        int setRows = query.numRowsAffected();
        if(setUpResult){
            if(setRows > 0){
                qDebug()<<"setUpCurveSuccess:"<<lowCycle<<cycle;
            }
        }else{
            qDebug()<<"setUpCurveError:"<<query.lastError().text();
        }
    }
}


void FtpHandle::deleteFile2(QString cycle)
{
    //方法二，用当前文件去查看循环号是否已经上传成功，成功的删除
}
