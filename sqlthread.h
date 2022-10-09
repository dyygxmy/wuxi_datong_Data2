#ifndef SQLTHREAD_H
#define SQLTHREAD_H
#include <QObject>
#include <QSettings>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include "GlobalVarible.h"
#include <QThread>
#include <QVariantMap>
class SqlThread : public QObject
{
    Q_OBJECT
public:
    explicit SqlThread(QObject *parent = 0);

public slots:
    void sqlinsert(QString *);
    void sqlinsert(QVariant);
    void receiveConfigureAll(int,int,int,int);
    void configOne(QString,QString,QString);
public:
    QThread m_thread;
private:
    QSqlDatabase db;
    QSqlQuery query;
    void mysqlConnect();
    bool mysqlIsOpen();
    void sqlclose();
public :signals:
    void send_mysqlerror();


};

#endif // SQLTHREAD_H
