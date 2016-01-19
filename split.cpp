#include "split.h"
#include "GlobalVarible.h"
#include "iostream"
using namespace std;


Split::Split(QObject *parent) :
    QObject(parent)
{
    split_thread.start();
    this->moveToThread(&split_thread);
}

void Split::mysplit_timer()
{
    qDebug()<< "split thread start";
    tcpServer = new QTcpServer(this);
    clientConnection = new QTcpSocket(this);

    if(!tcpServer->listen(QHostAddress::Any,6666))
    {
        qDebug()<<tcpServer->errorString();
        clientConnection->close();
        qDebug()<<"split listen fail";
    }

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(connection()));
}

void Split::connection()
{
    // 获取已经建立的连接的套接字
    clientConnection=tcpServer->nextPendingConnection();
    connect(clientConnection,SIGNAL(readyRead()),this,SLOT(sendMessage()));
    connect(clientConnection, SIGNAL(disconnected()),
            clientConnection, SLOT(deleteLater()));
    qDebug()<<"connect sucess!";
}

void Split::sendMessage()
{
    clientConnection->readAll();
//    qDebug()<<"sendMessage";
    datas();
//    for(int i = 0;i< 109;i++)
//    {
//        qDebug() << "data[" << i  << "]"<< data[i];
//    }
//    qDebug()<<"sendMessage1";
    // 用于暂存我们要发送的数据

    QDataStream out(&block, QIODevice::WriteOnly);
    // 设置数据流的版本，客户端和服务器端使用的版本要相同
    out.setVersion(QDataStream::Qt_4_8);
    out << (quint16)0;
//    out << tr("hello TCP!!!");
    for(int i=0;i<109;i++)
    {
        out << data[i];
    }
    out.device()->seek(0);
//   qDebug()<<"block size"<<block.size()<<"  "<<sizeof(quint16)<<"  "<<(quint16)0;
    out << (quint16)(block.size() - sizeof(quint16));
//    QString str=QString(block);
//    std::cout<<block.data()<<endl;
//    qDebug() << "%%%%%%%%%%%" << QString::fromAscii(block.data());
   // clientConnection=tcpServer->nextPendingConnection();
//    qDebug() << "size block" << block.size();
//    qDebug()<<"block"<<block;
    clientConnection->write(block);
    clientConnection->waitForBytesWritten();
}

QString Split::add(int m, QString s)
 {
    int i;
    QString t= s;
    for(i=0;i<m-s.length();i++)
    {
        t.append(" ");
    }
    return t;
 }

//QString Split::addzero(int m, QString s)
// {
//    int i;
//    QString t=s;
//    for(i=0;i<m-s.length();i++)
//    {
//        t.prepend("0");
//    }
//    return t;
// }

void Split::datas()
{
    QString s;
    //QSettings *configIniRead = new QSettings("/config.ini", QSettings::IniFormat);
    //工位号
    s = info[6];
    //s = configIniRead->value("baseinfo/StationId").toString();
    //bzero(data2,sizeof(data2));
    data[0] = add(10, s);

    //运行模式
    if(!workmode)
        data[1]="2";
    else
        data[1]="1";

    //额定工艺时间
    s = info[5];
//    s = configIniRead->value("baseinfo/TackTime").toString();
    data[2]=add(3,s);

    //拧紧状态
    s=info[0];
    data[3]=add(1,s);

    //拧紧/RFID 状态
    if((!isRFID && !CsIsConnect)||
        (isRFID && info[1]=="0"))
        data[4]="2";
    else if((!isRFID && CsIsConnect)||
            (isRFID && info[1]=="1"))
        data[4]="1";

    //操作剩余时间
    s=info[2];
    data[5]=add(3,s);

    //条码
    s=VIN_PIN_SQL;
    data[6]=add(17,s);

    //PDM名称
    s=info[3];
    data[7]=add(10,s);

    //额定螺栓数量
//    int n = configIniRead->value("baseinfo/pdmmax").toInt();  //PDM   info数
//    int coord = 0;
//    int i;
//    for(i=1; i<n+1; i++)
//    {
//        if (configIniRead->value("pdminfo"+QString::number(i)+"/pdmname").toString() == info[3])
//        {
//            coord= configIniRead->value("pdminfo"+QString::number(i)+"/num").toInt();
//            break;
//        }
//    }
//    s=QString::number(coord);
    s = info[4];
    data[8]=add(2,s);
    //螺栓坐标
    int k;
    for(k=0;k<info[4].toInt();k++)
    {
        //螺栓坐标
//        dou = configIniRead->value("pdminfo"+QString::number(i)+"/tempx"+QString::number(k+1)).toDouble()/1000;
        s = status[k][3];
        data[9+k*5] = add(6,s);
//        dou = configIniRead->value("pdminfo"+QString::number(i)+"/tempy"+QString::number(k+1)).toDouble()/1000;
        s = status[k][4];
        data[10+k*5] = add(6,s);
        //螺栓状态
        s= status[k][0];
        data[11+k*5] = add(1,s);
        //螺栓扭矩
        s = status[k][1];
        data[12+k*5] = add(8,s);
        //螺栓角度
        s = status[k][2];
        data[13+k*5] = add(8,s);
    }
//    for(int i = 0;i< 109;i++)
//    {
//        qDebug() << "data[" << i  << "]"<< data[i];
//    }
//    delete configIniRead;
}
