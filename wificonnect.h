#ifndef WIFICONNECT_H
#define WIFICONNECT_H

#include <QObject>
#include <QThread>
#include <QSettings>
#include <QTimer>
class Wificonnect : public QObject
{
    Q_OBJECT
public:
    explicit Wificonnect(QObject *parent = 0);
    
signals:
    void wifi_connect(bool);
    void data_connect(bool);
    //void send_unconnect(bool);
    
public slots:
    void Wifi_ConnectStart();
    void timerWifi();

private:
    QThread wificonnect_thread;
    QTimer timerwifi;
    int countnum;
    int number;
    bool wifiIn;
    bool wifiOut;
    int countnum_data;
    bool wifiIn_data;
    bool wifiOut_data;
    
};

#endif // WIFICONNECT_H
