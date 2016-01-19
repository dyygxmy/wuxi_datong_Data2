#ifndef SPLIT_H
#define SPLIT_H

#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
//#include <QSettings>
class Split : public QObject
{
    Q_OBJECT
public:
    explicit Split(QObject *parent = 0);
    
    QString add(int m, QString s);
//    QString addzero(int m, QString s);
signals:
    
public slots:
    void mysplit_timer();
    void connection();
    void sendMessage();
    void datas();

private:
    QThread split_thread;
    QTcpServer *tcpServer;
    QTcpSocket *clientConnection;
    QString data[109];
    QByteArray block;
};

#endif // SPLIT_H
