#ifndef REPAIRCURVE_H
#define REPAIRCURVE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <GlobalVarible.h>

class repairCurve : public QObject
{
    Q_OBJECT
public:
    explicit repairCurve(QObject *parent = 0);

signals:
    void signalRepaieCurve(QString) ;
public slots:
    void repairStart();
    void selectData();

private:
    QThread repair_thread;
    QSqlDatabase db;
    QSqlQuery query;
    QTimer  selectTimer;
    void mysqlConnect();
    bool mysqlIsOpen();
    void sqlclose();

};

#endif // REPAIRCURVE_H
