#ifndef DT_HTTP_H
#define DT_HTTP_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QVariant>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>


#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>

#include <QSettings>
#include <QApplication>

#include<QDebug>

#include "GlobalVarible.h"
#include "./json/serializer.h"
#include "./json/parser.h"

class DT_HTTP : public QObject
{
    Q_OBJECT
public:
    explicit DT_HTTP(QObject *parent = 0);


private:
    void initTable() ;

    QThread m_thread;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QNetworkRequest req;
    QSqlDatabase db;
    QSqlQuery query;
    int GetTimes;
    bool isFirst;
    int wrongRecordID;
    int wrongTimes;
    QString Factory;
    int TIMEOUT;
    void mysqlConnect();
    bool mysqlIsOpen();
    void mysqlClose();

signals:

public slots:
    void init();
    void dataInsert();
};

#endif // DT_HTTP_H
