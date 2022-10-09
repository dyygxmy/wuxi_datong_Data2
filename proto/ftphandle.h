#ifndef FTPHANDLE_H
#define FTPHANDLE_H

#include <QObject>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QTimer>
#include "GlobalVarible.h"
#include <QSettings>
#include <QDebug>

class FtpHandle : public QObject
{
    Q_OBJECT
public:
    explicit FtpHandle(QObject *parent = 0);

signals:
    void signalRepaieCurve(QString);
public slots:
    void ftpStart();
private slots:
    void parseFile();
private:
    QThread m_thread;
    QSqlDatabase db;
    QSqlQuery query;
    QTimer  ftpupload;
    QStringList baseNameList;
    QStringList filePathList;

    void mysqlConnect();
    bool mysqlIsOpen();
    void sqlclose();
    void FindFile();
    void deleteFile();
    void curveFileInvalidManage();
    void checkMissCurve(QString);//¼ì²é¶ªÊ§ÇúÏß
    void deleteFile2(QString);
};

#endif // FTPHANDLE_H
