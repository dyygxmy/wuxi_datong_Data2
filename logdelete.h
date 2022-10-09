#ifndef LOGDELETE_H
#define LOGDELETE_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QDir>
#include <QDate>
#include "unistd.h"

class LogDelete : public QObject
{
    Q_OBJECT
public:
    explicit LogDelete(QObject *parent = 0);

signals:
    void signalSyncTime(int) ;

public slots:
    void init();
    void logDeleteSlot();

private:
    QThread m_thread;
    QTimer LogTimer;
};

#endif // LOGDELETE_H
