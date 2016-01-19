#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setGeometry(QRect(0, 0, 1366, 768));

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    //this->setCursor(Qt::BlankCursor); //去掉光标

    init();
    this->setFixedSize(1366,768);
    this->setWindowTitle("B.I.W @Data2.1.0");
    connectMysql();
    ui->stackedWidget->setCurrentIndex(0);
    howmuchProNnum = 0;
    whichar = 0;
    whichpronumis = 1;
    equeloptionbnum= 0;
    equeloptionknum= 0;
    enableLsnumber = 0;
    pdmnowromisOk = true;
    numpdm = 0;
    tempnumdpm = 0;
    pdmflicker = true;
    whichpdmnumnow = 0;
    battry_num= 0;

    ui->label_black->hide();
    ui->pushButton_reset->hide();
    ui->pushButton_17->hide();
    QTimer *timer=new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(ShowTime()));
    if(SerialGunMode)
    {
        system("echo 0 > /sys/class/leds/control_uart2/brightness");
    }
    timer->start(1000);
    ScrewWhichExit = 0;
    ui->progressBar->setValue(0);
    // ui->label_9->hide();
    // ui->label_ss2->hide();
    ui->label_wifi->hide();
    if(!battery)
    {
        ui->label_battery->hide();
    }
    m_CurrentValue = m_MaxValue = m_UpdateInterval = 0;
    connect(&m_Timer, SIGNAL(timeout()), this, SLOT(UpdateSlot()));
    connect(&timerpdm, SIGNAL(timeout()), this, SLOT(PdmFlicker()));
    connect(&shutdown_timer,SIGNAL(timeout()),this,SLOT(clocked()));
    connect(&timer_showdown,SIGNAL(timeout()),this,SLOT(battery15()));
    yellow_led(1);
    red_led(0);
    green_led(0);
    white_led(0);
    newconfiginfo = new Newconfiginfo;
    connect(newconfiginfo,SIGNAL(closeconfig()),this,SLOT(init()));
    newconfiginfo->pdminit();
}

/*****************断开重新连接*******************/
void MainWindow::receiveOperate()
{
    TightenIsReady(true);
    if(SYSS == "ING")
    {
        fromsecondthreaddata("","","Reconnect");
    }
}
/*****************拧紧枪是否准备*******************/
void MainWindow::TightenIsReady(bool isready)
{
    if(isready)
    {
        ui->label_ss1->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/68.bmp);");
        if(SYSS == "Ready")
        {
            ui->pushButton_16->setText("Ready");
            ui->pushButton_16->setStyleSheet("font: 30pt ; background-color: rgb(51, 153, 255); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
        }
        else if(SYSS == "ING")
        {
            ui->pushButton_16->setText("ING");
            ui->pushButton_16->setStyleSheet("font: 50pt ; background-color: rgb(250, 225, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
        }
        else if(SYSS == "OK")
        {
            ui->pushButton_16->setText("OK");
            ui->pushButton_16->setStyleSheet("font: 60pt ; background-color: rgb(25, 125, 44); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
        }
        else if(SYSS == "NOK")
        {
            ui->pushButton_16->setText("NOK");
            ui->pushButton_16->setStyleSheet("font: 40pt ; background-color: rgb(255, 0, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
        }
        yellow_led(0);
        ui->label_tiaomastate->setText("");

    }
    else
    {
        yellow_led(1);
        ui->label_tiaomastate->setText(tr("拧紧控制器断开连接"));
        ui->label_ss1->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/69.bmp);");
        ui->pushButton_16->setText("Not Ready");
        ui->pushButton_16->setStyleSheet("font: 19pt ; background-color: rgb(250, 0, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
    }
}
/*****************匹配G9码*********************/
void MainWindow::searchG9Num()
{
    //匹配G9
    int i = 0;
    QString temp;
    bool flagss = false;
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    for(i = 1;i < 21;i++)
    {
        temp = config->value(QString("carinfo").append(QString::number(i)).append("/G9")).toString();
        if(temp == tempG9)
        {
            i = whichar;
            flagss = true;
            break;
        }
    }
    if(flagss)//flaggs 为真匹配成功
    {
        howmuchProNnum = config->value(QString("carinfo").append(QString::number(i)).append("/IsOptionalStation")).toInt();
        if(!howmuchProNnum) //判断是否选配
        {

        }else
        {
            //不选配  直接下发
            //设置获取匹配成功后的 程序号
            if(howmuchProNnum > 0)
            {
                whichpronumis = 1;
                proNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/ProNum")).toString();
                lsNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/LSNumber")).toString();
                SCREWID_SQL = config->value(QString("carinfo").append(QString::number(whichar)).append("/LuoSuanNum")).toString();
                if(lsNum.toInt())
                {
                    enableLsnumber = lsNum.toInt();
                    ui->label_pronum->setText(proNum);
                    ui->label_lsnum->setText(lsNum);
                    qDebug() << "pronum ==" << proNum;
                    qDebug() << "lsnum ==" << lsNum;
                }
            }

        }
    }
    delete config;
}
/**********************************连接mysql数据库*/
void ::MainWindow::connectMysql()
{
    db=QSqlDatabase::addDatabase("QMYSQL","mysqlconnectionmatch");
    db.setHostName("localhost");
    db.setDatabaseName("Tighten");
    db.setUserName("root");
    db.setPassword("123456");
    if(!db.open()){
        qDebug()<< db.lastError().text();
        qDebug()<< "mainwindow open mysql fail";
    }else{
        qDebug()<< "mainwindow open mysql ok";
    }
    query = QSqlQuery(db);

}

void MainWindow::mysqlopen()
{
    if(QSqlDatabase::contains("mysqlconnectionmatch")){
        db = QSqlDatabase::database("mysqlconnectionmatch");
    }else{
        db = QSqlDatabase::addDatabase("QMYSQL","mysqlconnectionmatch");
        db.setHostName("localhost");
        db.setDatabaseName("Tighten");
        db.setUserName("root");
        db.setPassword("123456");
        query = QSqlQuery(db);
    }

    if(!db.open())
    {
        if(!db.open())
        {
            qDebug()<< "mainwindow localmysql "<< db.lastError().text();
        }else
        {
            qDebug()<< "mainwindow localmysql open ok 2";
        }
    }else
    {
        //qDebug()<< "mainwindow localmysql open ok 1";
    }
}

void MainWindow::mysqlclose()
{
    if(db.isOpen())
        db.close();
}
void MainWindow::sendWebValue(int states,QString namepdm)
{
    //##############################################
    //传给web端螺丝数据状态

    if(states == 1)
    {
        ScrewWhichExit = 0;
        status[ScrewWhichExit][0] = "3";  //螺栓状态
        status[ScrewWhichExit][1] = "";//螺栓扭矩
        status[ScrewWhichExit][2] = "";// 螺栓角度

        info[0] = "1";
        info[1] = RFIDISConnect?"1":"0";
        info[2] = QString::number(TimeLeft);
        info[3] = namepdm;


        for(int j = 1;j < tempnumdpm;j++)
        {
            status[j][0] = "4";
            status[j][1] = "";//螺栓扭矩
            status[j][2] = "";// 螺栓角度
        }
    }

    //##############################################
}
/*******************匹配VIN码***************************/
void MainWindow::searchVinNum()
{
    //匹配VIN码
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    bool flags = false;
    int i = 1;
    for(i = 1;i < 21;i++)
    {
        QString temp = config->value(QString("carinfo").append(QString::number(i)).append("/VIN")).toString();
        //        if(temp.length()!=5)
        //        {
        //            continue;
        //        }
        //        int replacetmp = 0;
        //        flags = true;
        //        for(int k = 3;k < 8;k++)
        //        {
        //            replacetmp = k-3;
        //            if(temp.at(replacetmp) == '?')
        //            {
        //                continue;
        //            }else
        //            {
        //                if(serialNums.at(k) != temp.at(replacetmp))
        //                {
        //                    flags = false;
        //                    break;
        //                }else
        //                {
        //                    continue;
        //                }
        //            }

        //        }
        if(temp.right(2) == serialNums.right(2))
            flags = true;

        if(flags)
        {
            ui->label_tiaomastate->setText(tr(""));
            break;
        }

    }

    if(flags)
    {
        sendnexo(serialNums);
        whichar = i;
        howmuchProNnum = config->value(QString("carinfo").append(QString::number(i)).append("/IsOptionalStation")).toInt();

        //匹配成功,再判断是否选配
        if(howmuchProNnum)
        {
            //选配
            //匹配 数据库中的vin码
            bxuannumtmp= 0;
            int k =1;
            for(k = 1;k<6;k++)
            {
                int tt = 0;

                for(int n = 1;n < 21;n++)
                {

                    tt = config->value(QString("carinfo").append(QString::number(whichar)).append("/OPLSNumber").append(QString::number(k)).append(QString::number(n))).toInt();
                    if(tt)
                        break;
                }
                whichoption = k;
                if(tt)
                {
                    // qDebug() << "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII whichoption" << whichoption;
                    for(int t = 1;t < 6;t++)
                    {
                        QString bxname = config->value(QString("carinfo").append(QString::number(whichar)).append("/bxuanname").append(QString::number(whichoption)).append(QString::number(t))).toString();
                        QString bxcode = config->value(QString("carinfo").append(QString::number(whichar)).append("/bxuancode").append(QString::number(whichoption)).append(QString::number(t))).toString();
                        if(bxname!="" && bxcode!="")
                        {
                            bxuannumtmp++;
                        }
                    }
                    if(!bxuannumtmp)
                        continue;
                    //  qDebug() << "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII bxuannumtmp" << bxuannumtmp;
                    //取出选配，查询FIS 数据库，比对 必选fis信息
                    selectVin = "select * from FisPreview where VIN ='";
                    QString  tmpserial = serialNums;
                    query.exec(selectVin+tmpserial.append("'"));
                    // query.exec("select * from FisPreview where VIN ='LSVAE45E2EN111125'");
                    //  qDebug() << "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII selectVIN + serialNums" << selectVin+serialNums;
                    query.next();
                    if(query.isValid())
                    {
                        //查到了匹配
                        // qDebug() << " VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV" << query.isValid();
                        record = query.record();
                        for(int j = 1;j < 6;j++)
                        {
                            QString bxname = config->value(QString("carinfo").append(QString::number(whichar)).append("/bxuanname").append(QString::number(whichoption)).append(QString::number(j))).toString();
                            QString bxcode = config->value(QString("carinfo").append(QString::number(whichar)).append("/bxuancode").append(QString::number(whichoption)).append(QString::number(j))).toString();

                            if(bxname == "" || bxcode == "")
                            {
                                continue;
                            }
                            for(int m = 0;m< record.count();m++)
                            {
                                field = record.field(m);
                                //  qDebug() << "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII field.name" << field.name();
                                if(field.name() == bxname)
                                {
                                    if(field.value().toString() == bxcode)
                                    {
                                        equeloptionbnum++;
                                        //   qDebug() << "必选匹配成功+1" << equeloptionbnum ;
                                    }else
                                    {
                                        //没有跟它匹配的 选配值
                                        equeloptionbnum = 0;
                                        qDebug() << "bixuan match fail" ;
                                        break;
                                    }
                                }else
                                {
                                    continue;
                                }
                                if(equeloptionbnum == bxuannumtmp)
                                {
                                    break;
                                }
                            }
                            if(equeloptionbnum == bxuannumtmp)
                            {
                                break;
                            }
                        }

                    }else
                    {
                        //查不着 快速请求
                        continue;
                    }
                }
                else
                {
                    continue;
                }
                //  qDebug() << "NMNMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNequeloptionbnum " << equeloptionbnum;

                //取出选配，查询FIS 数据库，比对 可选fis信息
                QString  tmpserial = serialNums;
                query.exec(selectVin+tmpserial.append("'"));
                query.next();
                if(query.isValid())
                {
                    //查到了匹配
                    record = query.record();
                    for(int j = 1;j < 6;j++)
                    {
                        QString kxname = config->value(QString("carinfo").append(QString::number(whichar)).append("/kxuanname").append(QString::number(whichoption)).append(QString::number(j))).toString();
                        QString kxcode = config->value(QString("carinfo").append(QString::number(whichar)).append("/kxuancode").append(QString::number(whichoption)).append(QString::number(j))).toString();
                        if(kxname == "" || kxcode == "")
                        {
                            equeloptionknum++;
                            continue;
                        }
                        for(int m = 0;m< record.count();m++)
                        {
                            field = record.field(m);
                            if(field.name() == kxname)
                            {
                                if(field.value().toString() == kxcode)
                                {
                                    equeloptionknum = 5;
                                    //  qDebug() << "可选匹配成功" ;
                                    break;

                                }else
                                {
                                    // //没有跟它匹配的 选配值
                                    equeloptionknum = 0;

                                }
                            }else
                            {
                                continue;
                            }
                        }
                        if(equeloptionknum == 5)
                        {
                            break;
                        }else
                        {
                            continue;
                        }
                    }

                }else
                {
                    //查不着 快速请求
                }
                //  qDebug() << "NMNMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNequeloptionknum " << equeloptionknum;
                if(equeloptionbnum == bxuannumtmp && equeloptionknum == 5)
                {
                    whichpronumis = 1;
                    int statusop = 0;
                    for(int j = 1;j< 21;j++)
                    {
                        proNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/OPProNum").append(QString::number(whichoption)).append(QString::number(j))).toString();
                        lsNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/OPLSNumber").append(QString::number(whichoption)).append(QString::number(j))).toString();
                        SCREWID_SQL = config->value(QString("carinfo").append(QString::number(whichar)).append("/OPLuoSuanNum").append(QString::number(whichoption)).append(QString::number(j))).toString();
                        VIN_PIN_SQL = serialNums;
                        enableLsnumber = lsNum.toInt();
                        if(enableLsnumber)
                        {
                            ui->label_pronum->setText(proNum);
                            ui->label_lsnum->setText(lsNum);
                            QString namepdm =  config->value(QString("carinfo").append(QString::number(whichar)).append("/pdmyinyong").append(QString::number(whichoption))).toString();
                            tempnumdpm = 0;
                            QString pathpdm;
                            int j = 1;
                            for( j = 1;j<250;j++)
                            {
                                if(namepdm == config->value(QString("pdminfo").append(QString::number((j))).append("/pdmname")))
                                {
                                    tempnumdpm = config->value(QString("pdminfo").append(QString::number((j))).append("/num")).toInt();
                                    pathpdm = config->value(QString("pdminfo").append(QString::number((j))).append("/pdmpath")).toString();
                                    break;
                                }
                            }
                            sendWebValue(1,pathpdm);
                            ui->label_pdmarea->setStyleSheet(QString("border-image: url(/PDM/").append(pathpdm).append(")"));

                            numpdm = 0;
                            info[4] =QString::number(tempnumdpm);
                            for(int i = 0;i < tempnumdpm;i++)
                            {

                                butt[i] = new QPushButton(this);
                                label1[i] = new QLabel(this);
                                label2[i] = new QLabel(this);
                                butt[i]->raise();
                                butt[i]->setFlat(true);
                                label1[i]->setAlignment(Qt::AlignLeft);
                                label2[i]->setAlignment(Qt::AlignLeft);
                                butt[i]->setFocusPolicy(Qt::NoFocus);
                                label1[i]->setFocusPolicy(Qt::NoFocus);
                                label2[i]->setFocusPolicy(Qt::NoFocus);
                                butt[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
                                label1[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
                                label2[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
                                numpdm++;
                                // temppdm = numpdm -1;

                                butt[i]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/w01.png);");
                                butt[i]->setText(QString::number((i+1)));

                                int tempx = config->value(QString("pdminfo").append(QString::number((j))).append("/tempx").append(QString::number((i+1)))).toInt();
                                int tempy =  config->value(QString("pdminfo").append(QString::number((j))).append("/tempy").append(QString::number((i+1)))).toInt();
                                status[i][3] =QString::number(tempx);
                                status[i][4] =QString::number(tempy);
                                double x = (double)tempx/1000 * 1166 +  200;
                                double y = (double)tempy/1000 * 598+ 170;
                                butt[i]->setGeometry(x,y,46,46);
                                label1[i]->setGeometry(x+23,y,130,23);
                                label2[i]->setGeometry(x+23,y+23,130,23);
                                label1[i]->setStyleSheet("background:transparent;");
                                label2[i]->setStyleSheet("background:transparent;");
                                butt[i]->show();
                                label1[i]->show();
                                label2[i]->show();
                            }
                            ui->progressBar->setValue(0);
                            //   ui->progressBar->setTextVisible(false);
                            m_CurrentValue  = 0;
                            Start(100, Tacktime*10);
                            ISmaintenance = true;
                            workmode = true;
                            //config->setValue("baseinfo/workmode","1");
                            QualifiedNum = 0;
                            whichpdmnumnow = 0;
                            timerpdm.start(500);
                            white_led(1);
                            ui->pushButton_16->setText("ING");
                            ui->pushButton_16->setStyleSheet("font: 50pt ; background-color: rgb(250, 225, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                            SYSS = "ING";
                            emit sendoperate();
                            statusop = 1;
                            equeloptionbnum = 0;
                            equeloptionknum = 0;
                            bxuannumtmp = 0;
                            break;
                        }
                        else
                        {
                            whichpronumis++;
                            continue;
                        }
                    }
                    if(statusop)
                        break;
                }
                else
                {
                    equeloptionknum = 0;
                    equeloptionbnum = 0;
                    bxuannumtmp = 0;
                    continue;
                    // ui->label_tiaomastate->setText(tr("条码无效"));

                }
            }
            if(k == 6)
            {
                ui->label_tiaomastate->setText(tr("选配匹配失败"));
                ISmaintenance = false;
                workmode = false;
                system("echo 0 > /sys/class/leds/control_uart2/brightness");
            }
        }else
        {
            //不选配
            //设置获取匹配成功后的 程序号
            //再判断是否有套筒
            if(!howmuchProNnum)
            {
                //判断是否有套筒
                //   qDebug() << "fei xuan pei is  come in !!!!!!!";
                whichpronumis = 1;
                int j = 1;
                for(j = 1;j< 21;j++)
                {
                    int tao_tong = config->value(QString("carinfo").append(QString::number(whichar)).append("/Taotong").append(QString::number(j))).toInt();
                    if(tao_tong >0 && tao_tong < 9)
                    {
                        // qDebug() << "tao tong fei xuan pei is  come in !!!!!!!";
                        VIN_PIN_SQL = serialNums;
                        TAOTONG = tao_tong;
                        QString namepdm =  config->value(QString("carinfo").append(QString::number(whichar)).append("/pdmyinyong")).toString();
                        tempnumdpm = 0;
                        whichpronumis=1;
                        QString pathpdm;
                        int j = 1;
                        for( j = 1;j<250;j++)
                        {
                            if(namepdm == config->value(QString("pdminfo").append(QString::number((j))).append("/pdmname")))
                            {
                                tempnumdpm = config->value(QString("pdminfo").append(QString::number((j))).append("/num")).toInt();
                                pathpdm = config->value(QString("pdminfo").append(QString::number((j))).append("/pdmpath")).toString();
                                break;
                            }
                        }
                        if(PDM_PATH != pathpdm)
                        {
                            if(j!=250)
                            {
                                ui->label_pdmarea->setStyleSheet(QString("border-image: url(/PDM/").append(pathpdm).append(")"));
                            }
                            PDM_PATH = pathpdm;
                        }
                        numpdm = 0;
                        //************套筒值为web****************
                        sendWebValue(1,pathpdm);
                        info[4] =QString::number(tempnumdpm);
                        for(int i = 0;i < tempnumdpm;i++)
                        {
                            butt[i] = new QPushButton(this);
                            label1[i] = new QLabel(this);
                            label2[i] = new QLabel(this);
                            butt[i]->raise();
                            butt[i]->setFlat(true);
                            label1[i]->setAlignment(Qt::AlignLeft);
                            label2[i]->setAlignment(Qt::AlignLeft);
                            butt[i]->setFocusPolicy(Qt::NoFocus);
                            label1[i]->setFocusPolicy(Qt::NoFocus);
                            label2[i]->setFocusPolicy(Qt::NoFocus);
                            butt[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
                            label1[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
                            label2[i]->setAttribute(Qt::WA_TransparentForMouseEvents);

                            numpdm++;


                            butt[i]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/w01.png);");
                            butt[i]->setText(QString::number((i+1)));

                            int tempx = config->value(QString("pdminfo").append(QString::number((j))).append("/tempx").append(QString::number((i+1)))).toInt();
                            int tempy =  config->value(QString("pdminfo").append(QString::number((j))).append("/tempy").append(QString::number((i+1)))).toInt();
                            status[i][3] =QString::number(tempx);
                            status[i][4] =QString::number(tempy);
                            double x = (double)tempx/1000 * 1166 + 200;
                            double y = (double)tempy/1000 * 598 + 170;
                            butt[i]->setGeometry(x,y,46,46);
                            label1[i]->setGeometry(x+23,y,130,23);
                            label2[i]->setGeometry(x+23,y+23,130,23);
                            label1[i]->setStyleSheet("background:transparent;");
                            label2[i]->setStyleSheet("background:transparent;");
                            butt[i]->show();
                            label1[i]->show();
                            label2[i]->show();
                        }

                        ui->progressBar->setValue(0);
                        m_CurrentValue  = 0;
                        Start(100, Tacktime*10);
                        ISmaintenance = true;
                        workmode = true;
                        //config->setValue("baseinfo/workmode","1");
                        QualifiedNum = 0;
                        whichpdmnumnow = 0;
                        timerpdm.start(500);
                        ui->pushButton_16->setText("ING");
                        qDebug() << "here";
                        white_led(1);
                        ui->pushButton_16->setStyleSheet("font: 50pt ; background-color: rgb(250, 225, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                        SYSS = "ING";
                        TaoTongState = true;

                        break;
                    }

                    proNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/ProNum").append(QString::number(j))).toString();
                    lsNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/LSNumber").append(QString::number(j))).toString();
                    SCREWID_SQL = config->value(QString("carinfo").append(QString::number(whichar)).append("/LuoSuanNum").append(QString::number(j))).toString();
                    QString carname = "";
                    carname =  config->value(QString("carinfo").append(QString::number(whichar).append("/carcx"))).toString();
                    VIN_PIN_SQL = serialNums;
                    enableLsnumber = lsNum.toInt();
                    if(enableLsnumber)
                    {
                        ui->label_pronum->setText(proNum);
                        ui->label_lsnum->setText(lsNum);
                         qDebug() << "pronum ==" << proNum;
                          qDebug() << "lsnum ==" << lsNum;
                        QString namepdm =  config->value(QString("carinfo").append(QString::number(whichar)).append("/pdmyinyong")).toString();
                        tempnumdpm = 0;
                        QString pathpdm;
                        int j = 1;
                        for( j = 1;j<250;j++)
                        {
                            if(namepdm == config->value(QString("pdminfo").append(QString::number((j))).append("/pdmname")))
                            {
                                tempnumdpm = config->value(QString("pdminfo").append(QString::number((j))).append("/num")).toInt();
                                pathpdm = config->value(QString("pdminfo").append(QString::number((j))).append("/pdmpath")).toString();
                                break;
                            }
                        }
                        if(PDM_PATH != pathpdm)
                        {
                            if(j!=250)
                            {
                                ui->label_pdmarea->setStyleSheet(QString("border-image: url(/PDM/").append(pathpdm).append(")"));
                            }
                            PDM_PATH = pathpdm;
                        }

                        //  qDebug() << pathpdm;
                        numpdm = 0;
                        /************发给web端空白螺栓****************/
                        sendWebValue(1,pathpdm);
                        info[4] =QString::number(tempnumdpm);
                        for(int i = 0;i < tempnumdpm;i++)
                        {
                            butt[i] = new QPushButton(this);
                            label1[i] = new QLabel(this);
                            label2[i] = new QLabel(this);
                            butt[i]->raise();
                            butt[i]->setFlat(true);
                            label1[i]->setAlignment(Qt::AlignLeft);
                            label2[i]->setAlignment(Qt::AlignLeft);
                            butt[i]->setFocusPolicy(Qt::NoFocus);
                            label1[i]->setFocusPolicy(Qt::NoFocus);
                            label2[i]->setFocusPolicy(Qt::NoFocus);
                            butt[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
                            label1[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
                            label2[i]->setAttribute(Qt::WA_TransparentForMouseEvents);

                            numpdm++;
                            // temppdm = numpdm -1;

                            butt[i]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/w01.png);");
                            butt[i]->setText(QString::number((i+1)));

                            int tempx = config->value(QString("pdminfo").append(QString::number((j))).append("/tempx").append(QString::number((i+1)))).toInt();
                            int tempy =  config->value(QString("pdminfo").append(QString::number((j))).append("/tempy").append(QString::number((i+1)))).toInt();
                            status[i][3] =QString::number(tempx);
                            status[i][4] =QString::number(tempy);
                            double x = (double)tempx/1000 * 1166 + 200;
                            double y = (double)tempy/1000 * 598 + 170;
                            butt[i]->setGeometry(x,y,46,46);
                            label1[i]->setGeometry(x+23,y,130,23);
                            label2[i]->setGeometry(x+23,y+23,130,23);
                            label1[i]->setStyleSheet("background:transparent;");
                            label2[i]->setStyleSheet("background:transparent;");
                            butt[i]->show();
                            label1[i]->show();
                            label2[i]->show();
                        }
                        ui->progressBar->setValue(0);
                        // ui->progressBar->setTextVisible(false);
                        m_CurrentValue  = 0;
                        Start(100, Tacktime*10);
                        // isworking = true;
                        ISmaintenance = true;
                        workmode = true;
                        //config->setValue("baseinfo/workmode","1");
                        QualifiedNum = 0;
                        whichpdmnumnow = 0;
                        timerpdm.start(500);
                        ui->pushButton_16->setText("ING");
                        white_led(1);
                        ui->pushButton_16->setStyleSheet("font: 50pt ; background-color: rgb(250, 225, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                        SYSS = "ING";
                        emit sendoperate();
                        break;
                    }
                    else
                    {
                        whichpronumis++;
                        continue;
                    }
                }
                if(j == 21)
                {
                    ui->label_tiaomastate->setText(tr("螺栓数量为0"));
                    if(SerialGunMode)
                    {
                        system("echo 0 > /sys/class/leds/control_uart2/brightness");
                    }
                    ISmaintenance = false;
                    workmode = false;
                }
            }
        }
    }else
    {
        ui->label_tiaomastate->setText(tr("特征码匹配失败"));
        if(SerialGunMode)
        {
            system("echo 0 > /sys/class/leds/control_uart2/brightness");
        }
        ISmaintenance = false;
        workmode = false;
    }

    delete config;

}

/********************获取扫描枪的条码**************************/
void MainWindow::getSerialNum(QString serialNum,bool equeled,QString tempp)
{
    ui->label_tiaomastate->setText("");
    ui->label_17->setText(serialNums);
    if(isRFID)
    {  // 接收RFID G9 pin
        tempPin = serialNum;
        tempG9  = tempp;
        if(equeled)//pin码重复
        {
            ui->label_tiaomastate->setText("PIN码重复");
        }else //不重复匹配
        {
            searchG9Num();
        }

    }else
    {
        //接收ＶＩＮ
        serialNums = serialNum;
        //设置条码
        // echo 0
        ui->label_17->setText(serialNums);
        if(equeled)
        {
            ui->label_tiaomastate->setText(tr("条码重复"));
            if(SerialGunMode)
            {
                system("echo 0 > /sys/class/leds/control_uart2/brightness");
            }
            ISmaintenance = false;
            workmode = false;
        }else
        {
            //关闭条码枪
            ui->label_17->setText(serialNums);
            if(CsIsConnect && serialNums.size() == 21) //351没连接 不匹配
            {
                if(SYSS == "OK" || SYSS == "NOK")
                {
                    timerDelay();
                    ui->label_17->setText(serialNums);
                }
                searchVinNum();
            }
        }


    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    emit clo();
    // tcpSocket->close();
    event->accept();
}






/**********************PDM闪烁*****************************/

void MainWindow::PdmFlicker()
{
    if(pdmflicker)
        pdmflicker = false;
    else
        pdmflicker = true;
    if(whichpdmnumnow == tempnumdpm)
    {
        timerpdm.stop();

    }
    else
    {
        if(PDMCurrentState == "NOK")
        {
            if(pdmflicker)
            {
                butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/r01.png);");
            }
            else
            {
                butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/y01.png);");
            }
        }
        else
        {
            if(pdmflicker)
            {
                butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/y01.png);");
            }
            else
            {
                butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/w01.png);");
            }
        }
    }
}
/**********************一个条码拧紧完成OK后操作*****************************/
void MainWindow::timerDelay()
{
    // timerdelay.stop();
    ui->label_pronum->setText("");
    ui->label_lsnum->setText("");
    whichpronumis = 1;
    // isworking = false;
    //    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    //    config->setValue("baseinfo/workmode","0");
    ui->label_17->setText("");
    timerpdm.stop();
    int tempdata = tempnumdpm;
    // ui->label_17->setText(tr("等待车辆进站..."));
    for(int i = 0;i<tempdata;i++)
    {
        delete butt[i];
        delete label1[i];
        delete label2[i];
        tempnumdpm--;
    }
    ui->label_hege->setText("");
    ui->pushButton_16->setText("Ready");
    SYSS = "Ready";
    ui->pushButton_16->setStyleSheet("font: 30pt ; background-color: rgb(51, 153, 255); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");

    QualifiedNum = 0;
    ui->label_hege->setText("");
    PDMCurrentState = "OK";
    pdmnowromisOk = true;
    //enablenumberLeft = 0;
    //delete config;
    white_led(0);
    red_led(0);
    green_led(0);

}

/**********************一个螺丝拧紧完成后返回数据获取，下一个使能下发*****************************/
void MainWindow::fromsecondthreaddata(QString MI,QString WI,QString IsOk)
{

    //0 dat  1 time   2 state   3  扭矩 4 角度 5 螺栓编号   6 vin pin 码   7 循环号  8 曲线
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    if(IsOk== "Reconnect")  //重新连接
    {
        if(enableLsnumber)
        {
            sendnexo(serialNums);
            enablenumberLeft = enableLsnumber;
            emit sendoperate();
        }
        else if(!enableLsnumber)
        {

            int k = 0;
            for( k = whichpronumis;k <21;k++)
            {
                if(!howmuchProNnum)  //非选配
                {
                    proNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/ProNum").append(QString::number(k))).toString();
                    lsNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/LSNumber").append(QString::number(k))).toString();
                    SCREWID_SQL = config->value(QString("carinfo").append(QString::number(whichar)).append("/LuoSuanNum").append(QString::number(k))).toString();
                    //ScrewWhichExit = 0;
                    //info[1] = "0"; //归位状态
                    //info[4] = "0";//归位剩余时间
                }
                else
                {
                    proNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/OPProNum").append(QString::number(whichoption)).append(QString::number(whichpronumis))).toString();
                    lsNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/OPLSNumber").append(QString::number(whichoption)).append(QString::number(whichpronumis))).toString();
                    SCREWID_SQL = config->value(QString("carinfo").append(QString::number(whichar)).append("/OPLuoSuanNum").append(QString::number(whichoption)).append(QString::number(whichpronumis))).toString();

                }
                if(lsNum.toInt())
                {
                    emit sendoperate();
                    whichpronumis=k;
                    break;
                }
                else
                {
                    whichpronumis=k;
                    continue;
                }
            }

        }


    }
    else  //非重新连接
    {
        //        double torque = MI.toDouble();
        //        double angle = WI.toDouble();
        //        status[whichpdmnumnow][1] = QString::number(torque, 'f', 2);//螺栓扭矩
        //        status[whichpdmnumnow][2] = QString::number(angle, 'f', 2); // 螺栓角度
        status[whichpdmnumnow][1] = MI; // 螺栓扭矩
        status[whichpdmnumnow][2] = WI; // 螺栓角度
        //status[whichpdmnumnow][4] = data_model.DATE_b+" "+data_model.TIME_b;//螺栓拧紧时间
        if(IsOk == "NOK") // 本次螺栓不合格nok
        {
            status[whichpdmnumnow][0] = "5";  //螺栓状态
            info[0] = "1"; //拧紧状态
            ui->label_ceshipronum->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/32.bmp);");
            if(whichpdmnumnow < tempnumdpm)
            {
                label1[whichpdmnumnow]->setText(QString(tr("   T:").append(MI).append("Nm")));
                label2[whichpdmnumnow]->setText(QString(tr("   A:").append(WI).append("°")));
                label1[whichpdmnumnow]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);");
                label2[whichpdmnumnow]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);");
                butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/r01.png);");
            }
            nok_led(1);
            PDMCurrentState = "NOK";
            //timerpdm.stop();

        }
        else  //本次螺栓合格ok
        {
            ui->label_ceshipronum->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/70.bmp);");
            if(MI!= "-1" && WI != "-1")
                QualifiedNum++;//合格数加1
            ui->label_hege->setText(QString::number(QualifiedNum));
            enableLsnumber--;   //结果ok 数量减1
            //qDebug() << "enableLsnumber1" << enableLsnumber;
            if(whichpdmnumnow < tempnumdpm)
            {

                if(MI == "-1" && WI == "-1")
                { //nok确认1 个
                    status[whichpdmnumnow][0] = "2";  //螺栓状态
                    pdmnowromisOk = false;
                    butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/r01.png);");
                    if(PDMCurrentState != "NOK")
                    {
                        // qDebug() << "psmdfpsdmfsdfsdfsfsdf";

                        label1[whichpdmnumnow]->setText(QString(tr("   T:").append("-1").append("Nm")));
                        label2[whichpdmnumnow]->setText(QString(tr("   A:").append("-1").append("°")));
                        label1[whichpdmnumnow]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);");
                        label2[whichpdmnumnow]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);");
                        //存入数据库
                    }
                    nok_led(0);
                    whichpdmnumnow++;
                    timerpdm.start();
                }
                else
                {
                    //正常
                    nok_led(0);
                    butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/g01.png);");

                    label1[whichpdmnumnow]->setText(QString(tr("   T:").append(MI).append("Nm")));
                    label2[whichpdmnumnow]->setText(QString(tr("   A:").append(WI).append("°")));
                    label1[whichpdmnumnow]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);");
                    label2[whichpdmnumnow]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);");
                    status[whichpdmnumnow][0] = "1";  //螺栓状态
                    whichpdmnumnow++;
                    status[whichpdmnumnow][0] = "3";

                }
            }
            enablenumberLeft = enableLsnumber;
            PDMCurrentState = "OK";
            if(!enableLsnumber)
            {
                if(whichpronumis == 20)
                {
                    TaoTongState = false;
                    white_led(0);
                    //程序号 打完
                    if(SerialGunMode)
                    {
                        system("echo 0 > /sys/class/leds/control_uart2/brightness");
                    }
                    ISmaintenance = false;
                    workmode = false;
                    if(MI!= "-1" && WI != "-1")
                    {
                        ui->pushButton_16->setText("OK");
                        status[whichpdmnumnow][0] = "1";  //螺栓状态
                        info[0] = "2"; //拧紧状态
                        SYSS = "OK";
                        ui->pushButton_16->setStyleSheet("font: 60pt ; background-color: rgb(25, 125, 44); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                        green_led(1);
                        white_led(0);

                        if(!pdmnowromisOk)
                        {
                            ui->pushButton_16->setStyleSheet("font: 40pt ; background-color: rgb(255, 0, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                            ui->pushButton_16->setText("NOK");
                            status[whichpdmnumnow][0] = "2";  //螺栓状态
                            info[0] = "3"; //拧紧状态
                            SYSS = "NOK";
                            green_led(0);
                            red_led(1);
                            ISRESET  = true;
                            emit sendoperate();
                        }
                        else
                        {
                            status[whichpdmnumnow][0] = "1";  //螺栓状态
                            info[0] = "2"; //拧紧状态
                        }

                    }
                    else
                    {
                        SYSS = "NOK";
                        ui->pushButton_16->setStyleSheet("font: 40pt ; background-color: rgb(255, 0, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                        ui->pushButton_16->setText("NOK");
                        red_led(1);
                        ISRESET  = true;
                        emit sendoperate();
                    }
                    m_Timer.stop();
                    Stop();
                    ui->progressBar->setValue(0);
                    m_CurrentValue  = 0;
                    //  timerdelay.start(25000);
                }else
                {

                    QualifiedNum = 0;
                    whichpronumis++;
                    int k = 0;
                    for( k = whichpronumis;k <21;k++)
                    {
                        if(!howmuchProNnum)  //非选配
                        {
                            int tao_tong = config->value(QString("carinfo").append(QString::number(whichar)).append("/Taotong").append(QString::number(whichpronumis))).toInt();
                            if(tao_tong>0 && tao_tong < 9)
                            {
                                //qDebug() << "TAO TONG taoTONg tao tong" << tao_tong;
                                TaoTongState = true;
                                TAOTONG = tao_tong;
                                break;
                            }
                            TaoTongState = false;
                            proNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/ProNum").append(QString::number(k))).toString();
                            lsNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/LSNumber").append(QString::number(k))).toString();
                            SCREWID_SQL = config->value(QString("carinfo").append(QString::number(whichar)).append("/LuoSuanNum").append(QString::number(k))).toString();
                            //ScrewWhichExit = 0;
                            //info[1] = "0"; //归位状态
                            //info[4] = "0";//归位剩余时间
                        }
                        else
                        {
                            proNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/OPProNum").append(QString::number(whichoption)).append(QString::number(whichpronumis))).toString();
                            lsNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/OPLSNumber").append(QString::number(whichoption)).append(QString::number(whichpronumis))).toString();
                            SCREWID_SQL = config->value(QString("carinfo").append(QString::number(whichar)).append("/OPLuoSuanNum").append(QString::number(whichoption)).append(QString::number(whichpronumis))).toString();

                        }
                        if(lsNum.toInt())
                        {
                            ui->label_hege->setText("0");
                            emit sendoperate();
                            ui->label_pronum->setText(proNum);
                            enableLsnumber = lsNum.toInt();
                            ui->label_lsnum->setText(lsNum);
                            whichpronumis=k;
                            break;
                        }
                        else
                        {
                            whichpronumis=k;
                            continue;
                        }
                    }
                    if(k == 21)
                    {
                        TaoTongState = false;
                        workmode = false;
                        white_led(0);
                        Stop();
                        ui->progressBar->setValue(0);
                        m_CurrentValue  = 0;
                        if(MI!= "-1" && WI != "-1")
                        {
                            ui->pushButton_16->setText("OK");
                            SYSS = "OK";
                            ui->pushButton_16->setStyleSheet("font: 60pt ; background-color: rgb(25, 125, 44); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                            green_led(1);
                            if(!pdmnowromisOk)
                            {
                                ui->pushButton_16->setStyleSheet("font: 40pt ; background-color: rgb(255, 0, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                                ui->pushButton_16->setText("NOK");
                                status[whichpdmnumnow][0] = "2";  //螺栓状态
                                info[0] = "3"; //拧紧状态
                                SYSS = "NOK";
                                red_led(1);
                                green_led(0);
                                white_led(0);
                                ISRESET  = true;
                                emit sendoperate();
                            }
                            else
                            {
                                status[whichpdmnumnow][0] = "1";  //螺栓状态
                                info[0] = "2"; //拧紧状态
                            }
                        }
                        else
                        {
                            SYSS = "NOK";
                            red_led(1);
                            ui->pushButton_16->setStyleSheet("font: 40pt ; background-color: rgb(255, 0, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                            ui->pushButton_16->setText("NOK");
                            ISRESET  = true;
                            emit sendoperate();
                        }
                        m_Timer.stop();
                        // timerdelay.start(25000);
                        ISmaintenance = false;
                        if(SerialGunMode)
                        {
                            system("echo 0 > /sys/class/leds/control_uart2/brightness");
                        }

                    }
                }
            }
            else
            {
                if(MI == "-1" && WI == "-1")
                {
                    lsNum = QString::number(enableLsnumber);
                    emit sendoperate();
                }
            }

        }
    }
    delete config;
}


/**********************主界面维护模式 登陆按钮*****************************/
void MainWindow::on_pushButton_12_clicked()
{
    //GO login
    //QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    system("echo 0 > /sys/class/leds/control_uart2/brightness");
    if(!ISmaintenance)
    {
        ISmaintenance = true;
        workmode = true;
        if(SYSS == "OK" || SYSS == "NOK")
        {
            timerDelay();
            PDM_PATH="";
            ui->label_17->setText(tr("等待车辆进站..."));
            ui->label_pdmarea->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/DWIN_SET/home.bmp);");
        }
        ui->stackedWidget->setCurrentIndex(2);
        isFull = 0;
        person = 0;
        temp = "";
        ui->pushButton_13->setStyleSheet("border-image : url(:/re/93.bmp)");
        ui->pushButton_password->setStyleSheet("border-image : url(:/re/94.bmp)");

        //config->setValue("baseinfo/workmode","1");
    }

    //delete config;
}



void MainWindow::on_pushButton_1_clicked()
{
    temp.append("1");
    isFull++;
    judge();
}

void MainWindow::on_pushButton_2_clicked()
{
    temp.append("2");
    isFull++;
    judge();
}

void MainWindow::on_pushButton_3_clicked()
{
    temp.append("3");
    isFull++;
    judge();
}

void MainWindow::on_pushButton_4_clicked()
{
    temp.append("4");
    isFull++;
    judge();
}

void MainWindow::on_pushButton_5_clicked()
{
    temp.append("5");
    isFull++;
    judge();
}

void MainWindow::on_pushButton_6_clicked()
{
    temp.append("6");
    isFull++;
    judge();
}

void MainWindow::on_pushButton_7_clicked()
{
    temp.append("7");
    isFull++;
    judge();
}

void MainWindow::on_pushButton_8_clicked()
{
    temp.append("8");
    isFull++;
    judge();
}

void MainWindow::on_pushButton_9_clicked()
{
    temp.append("9");
    isFull++;
    judge();
}

void MainWindow::on_pushButton_0_clicked()
{
    temp.append("0");
    isFull++;
    judge();
}


void MainWindow::on_pushButton_delete_clicked()
{
    if(isFull == 1)
    {
        ui->pushButton_password->setStyleSheet("border-image : url(:/re/94.bmp)");
        isFull--;
        temp.resize(temp.size() - 1);
    }
    else if(isFull == 2)
    {
        ui->pushButton_password->setStyleSheet("border-image : url(:/re/95.bmp)");
        isFull--;
        temp.resize(temp.size() - 1);
    }
    else if(isFull == 3)
    {
        ui->pushButton_password->setStyleSheet("border-image : url(:/re/96.bmp)");
        isFull--;
        temp.resize(temp.size() - 1);
    }
}

void MainWindow::judge()
{
    if(isFull == 1)
    {
        ui->pushButton_password->setStyleSheet("border-image : url(:/re/95.bmp)");
        ui->pushButton_error->setStyleSheet("border-image: url(:/re/142.bmp)");
    }
    else if(isFull == 2)
        ui->pushButton_password->setStyleSheet("border-image : url(:/re/96.bmp)");
    else if(isFull == 3)
        ui->pushButton_password->setStyleSheet("border-image : url(:/re/97.bmp)");
    else if(isFull == 4)
    {
        ui->pushButton_password->setStyleSheet("border-image : url(:/re/98.bmp)");
        QSettings *configIniRead = new QSettings("/config.ini", QSettings::IniFormat);
        if(configIniRead->value(QString("baseinfo/GCpassword")).toString()==""||
                configIniRead->value(QString("baseinfo/cs351Ip")).toString()=="" )
        {
            system("cp /config1.ini /config.ini &");
        }
        delete configIniRead;
        QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
        if (person ==0)
        {
            if(temp == config->value(QString("baseinfo/GCpassword")).toString()||
                    temp == "5027")
            {
                isJS = false;
                ui->stackedWidget->setCurrentIndex(0);
                newconfiginfo->initui();
                //newconfiginfo->clearCache();
                newconfiginfo->show();
                ui->pushButton_13->setStyleSheet("border-image: url(:/re/99.png)");
                ui->pushButton_password->setStyleSheet("border-image : url(:)");
                ui->pushButton_14->setStyleSheet("border-image : url(:/re/100.png)");
                ui->pushButton_error->setStyleSheet("border-image : url(:)");
                //ui->stackedWidget->setCurrentIndex(0);
                //usleep(10000);
            }
            //            else if(temp == "0852")
            //            {
            //                e3 = new QGraphicsOpacityEffect(this);
            //                e3->setOpacity(0.5);
            //                ui->label_black->setGraphicsEffect(e3);
            //                ui->label_black->show();
            //                ui->label_black->setGeometry(0,0,1366,768);
            //                SaveWhat = "config_init";
            //                save = new Save;
            //                connect(save,SIGNAL(configinit(bool)),this,SLOT(config_init(bool)));
            //                save->show();
            //            }
            else
            {
                ui->pushButton_error->setStyleSheet("border-image : url(:/re/124.bmp)");
                ui->pushButton_password->setStyleSheet("border-image : url(:/re/94.bmp)");
                isFull = 0;
                temp = "";
            }
        }
        else if (person ==1)
        {
            if(temp == config->value(QString("baseinfo/JSpassword")).toString())
            {
                // qDebug() << "SSSSSSSSSSSSSSSS";
                isJS = true;
                ui->stackedWidget->setCurrentIndex(0);
                newconfiginfo->initui();
                newconfiginfo->show();
                ui->pushButton_14->setStyleSheet("border-image: url(:/re/100.png)");
                ui->pushButton_13->setStyleSheet("border-image : url(:/re/99.png)");
                ui->pushButton_error->setStyleSheet("border-image : url(:)");
                ui->pushButton_password->setStyleSheet("border-image : url(:)");
                // ui->stackedWidget->setCurrentIndex(0);
                //usleep(10000);

            }
            else
            {
                ui->pushButton_error->setStyleSheet("border-image : url(:/re/124.bmp)");
                ui->pushButton_password->setStyleSheet("border-image : url(:/re/94.bmp)");
                isFull = 0;
                temp = "";
            }
        }
        delete config;
    }
}


void MainWindow::on_pushButton_13_clicked()
{
    if(person != 0)
    {
        ui->pushButton_13->setStyleSheet("border-image : url(:/re/93.bmp)");
        ui->pushButton_14->setStyleSheet("border-image: url(:/re/100.png)");

        ui->pushButton_error->setStyleSheet("border-image : url(:)");
        ui->pushButton_password->setStyleSheet("border-image : url(:/re/94.bmp)");
        isFull = 0;
        temp = "";
        person = 0;
    }
}

void MainWindow::on_pushButton_14_clicked()
{
    if(person != 1)
    {
        ui->pushButton_14->setStyleSheet("border-image : url(:/re/92.bmp)");
        ui->pushButton_13->setStyleSheet("border-image: url(:/re/99.png)");

        ui->pushButton_error->setStyleSheet("border-image : url(:)");
        ui->pushButton_password->setStyleSheet("border-image : url(:/re/94.bmp)");
        isFull = 0;
        temp = "";
        person = 1;
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    //workmode = true;
    ISmaintenance = false;
    ui->pushButton_13->setStyleSheet("border-image : url(:/re/93.png)");
    ui->pushButton_14->setStyleSheet("border-image : url(:/re/100.png)");
    ui->pushButton_error->setStyleSheet("border-image : url(:)");
    ui->pushButton_password->setStyleSheet("border-image : url(:/re/94.bmp)");
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_6->setCurrentIndex(0);
    //QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    //config->setValue("baseinfo/workmode","0");
    //delete config;
    workmode = false;
}

void MainWindow::ShowTime()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    ui->label_12->setText(str);
    ui->label_14->setText(str);
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget_6->setCurrentIndex(0);
}

void MainWindow::UpdateSlot()
{
    m_CurrentValue++;
    TimeLeft = Tacktime-m_CurrentValue/10;
    info[2] = QString::number(TimeLeft);
    if( m_CurrentValue == m_MaxValue )
    {
        m_CurrentValue = 0;
        Stop();
    }

    ui->progressBar->setValue(m_CurrentValue);

}

void MainWindow::Start(int interval/* =100 */, int maxValue/* =600 */)
{
    info[2] = QString::number(TimeLeft);
    m_UpdateInterval = interval;
    m_MaxValue = maxValue;
    m_Timer.start(m_UpdateInterval);
    ui->progressBar->setRange(0, m_MaxValue);
    ui->progressBar->setValue(0);
}

void MainWindow::Stop()
{
    ui->progressBar->setValue(0);
    m_Timer.stop();
    info[2]="0";
}


void MainWindow::on_pushButton_reset_clicked()
{
    //no ok 确认全部
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);

    if(SYSS == "ING")
    {
        if(SerialGunMode)
        {
            system("echo 0 > /sys/class/leds/control_uart2/brightness");
        }
        info[0] = "3";
        SYSS = "NOK";
        m_Timer.stop();
        Stop();
        ui->progressBar->setValue(0);
        workmode = false;
        ISmaintenance = false;
        white_led(0);
        nok_led(0);
        m_CurrentValue  = 0;
        // Curve_Is_Null = true;
        //界面 没打的螺栓全部置-1
        m_Timer.stop();
        ISRESET  = true;
        emit sendoperate();
        timerpdm.stop();
        if(!whichpdmnumnow)
        {
            for(int j = 0;j<tempnumdpm;j++)
            {
                butt[j]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/r01.png);");
                if(label1[j]->text() == "")
                {
                    label1[j]->setText(QString(tr("   T:").append("-1").append("Nm")));
                    label2[j]->setText(QString(tr("   A:").append("-1").append("°")));
                    label1[j]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);");
                    label2[j]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);");
                    status[j][0]="2";
                    status[j][1]="-1";
                    status[j][2]="-1";
                }
            }
        }
        else
        {
            //if(whichpdmnumnow != tempnumdpm-1)
            //{
            for(int j = whichpdmnumnow;j<tempnumdpm;j++)
            {
                butt[j]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/r01.png);");
                if(label1[j]->text() == "")
                {
                    label1[j]->setText(QString(tr("   T:").append("-1").append("Nm")));
                    label2[j]->setText(QString(tr("   A:").append("-1").append("°")));
                    label1[j]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);");
                    label2[j]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);");
                    status[j][0]="2";
                    status[j][1]="-1";
                    status[j][2]="-1";
                }
            }
        }
        emit sendConfigureAll(howmuchProNnum,whichar,whichpronumis,whichoption);

        ui->pushButton_16->setStyleSheet("font: 40pt ; background-color: rgb(255, 0, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
        ui->pushButton_16->setText("NOK");
        // timerDelay();
        // ui->label_17->setText(tr("等待车辆进站..."));
        //  ui->label_pdmarea->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/DWIN_SET/home.bmp);");
        red_led(1);
        TaoTongState = false; //确认全部关闭套筒

        // white_led(0);
        //数据库插入 扭矩角度全部-1

    }

    delete config;
}

void MainWindow::on_pushButton_17_clicked()
{
    //nok确认1个
    if(enableLsnumber)
    {
        //        QString screwid = SCREWID_SQL;
        //        QString protmp = proNum;
        //        QString vin_pin_sql = VIN_PIN_SQL;

        if(SYSS == "ING")
        {
            // Curve_Is_Null = true;
            emit  sendfromsecondthread(SCREWID_SQL,VIN_PIN_SQL,proNum);
            pdmnowromisOk = false;
            if(TaoTongState)
            {
                if(enableLsnumber == 1)
                {
                    ISRESET = true;
                    emit sendoperate();
                }
            }

            fromsecondthreaddata("-1","-1","ok");

        }
    }


}
//重启系统
void MainWindow::signal_mysqlerror_do()
{
    ISRESET = true;
    sendoperate();
    e3 = new QGraphicsOpacityEffect(this);
    e3->setOpacity(0.5);
    ui->label_black->setGraphicsEffect(e3);
    ui->label_black->show();
    ui->label_black->setGeometry(0,0,1366,768);
    SaveWhat = "sqlerror";
    save = new Save;
    connect(save,SIGNAL(sendShutDown(int)),this,SLOT(shutdown(int)));
    save->show();
}

void MainWindow::init()
{
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    ui->label_gongwei->setText(config->value(QString("baseinfo/StationName")).toString());
    ui->label_gonghao->setText(config->value(QString("baseinfo/StationId")).toString());
    //ui->label_pdmarea->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/DWIN_SET/mainlogo.png);");
    workmode = false;
    //config->setValue("baseinfo/workmode","0");
    //ui->stackedWidget->setCurrentIndex(0);
    ui->label_17->setText(tr("等待车辆进站..."));
    if(isRFID)
    {
        ui->label_tiaoma->setText("RFID");
        ui->label_11->show();
        ui->label_ss4->show();
    }
    else
    {
        ui->label_tiaoma->setText(tr("条码枪"));
        ui->label_11->hide();
        ui->label_ss4->hide();
    }
    ui->label_ss3->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/68.bmp);");
    Tacktime = config->value("baseinfo/TackTime").toInt();

    info[5] = QString::number(Tacktime);
    info[6] = config->value(QString("baseinfo/StationId")).toString();

    delete config;

    QDateTime dateTime = QDateTime::currentDateTime();
    int year=dateTime.date().year();
    if(year<2015)
        ui->label_time->setText(tr("系统时间错误"));
    else
    {
        ui->label_time->clear();
    }
}

void MainWindow::configwarning(bool isconfigone)
{
    //qDebug() << "come hererer!";
    ConfigOneOrAll = isconfigone;
    if(!isconfigone)
    {
        ISWARNING = true;
        e3 = new QGraphicsOpacityEffect(this);
        e3->setOpacity(0.5);
        ui->label_black->setGraphicsEffect(e3);
        ui->label_black->show();
        ui->label_black->setGeometry(0,0,1366,768);
        SaveWhat = "input";
        save = new Save;
        connect(save,SIGNAL(sendCloseInput(bool)),this,SLOT(receiveCloseInput(bool)));
        save->show();
    }
    else
    {
        on_pushButton_17_clicked();
    }

}

/*****************套筒选择信号对应使能发送********************************/
void MainWindow::taotong_main(int  which_t)
{
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    int tao_tong = config->value(QString("carinfo").append(QString::number(whichar)).append("/Taotong").append(QString::number(whichpronumis))).toInt();
//    qDebug() << "taotongis " << tao_tong << which_t;

    if(tao_tong == which_t)
    {
//         qDebug() << "send operate!!!4";
 //       qDebug() << "enable" << enableLsnumber;
        if(!enableLsnumber)
        {
//             qDebug() << "send operate!!!";
            ui->label_tiaomastate->setText("");
            proNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/ProNum").append(QString::number(whichpronumis))).toString();
            lsNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/LSNumber").append(QString::number(whichpronumis))).toString();
            ui->label_pronum->setText(proNum);
            ui->label_lsnum->setText(lsNum);
 //           qDebug() << proNum << lsNum;
            SCREWID_SQL = config->value(QString("carinfo").append(QString::number(whichar)).append("/LuoSuanNum").append(QString::number(whichpronumis))).toString();
            QString carname = "";
            carname =  config->value(QString("carinfo").append(QString::number(whichar).append("/carcx"))).toString();
            VIN_PIN_SQL = serialNums;
            enableLsnumber = lsNum.toInt();
            if(enableLsnumber)
            {
                //sendnexo(serialNums);
 //               qDebug() << "send operate";
                emit sendoperate();
            }
        }
    }
    else
    {
        ui->label_tiaomastate->setText(tr("请正确选择套筒"));
        TaoTongState = true;
        if(enableLsnumber)
        {
            enableLsnumber=0;
            ISRESET  = true;
            emit sendoperate();
        }
    }

    delete config;
}

void MainWindow::receiveCloseInput(bool tmp)
{
    if(tmp)
    {
        if(!ConfigOneOrAll)
        {
            on_pushButton_reset_clicked();
            ui->label_black->hide();
            delete e3;
            delete save;
        }
        else
        {
            ui->label_black->hide();
            delete e3;
            delete save;
        }

        ISWARNING = false;
    }
    else
    {
        ui->label_black->hide();
        delete e3;
        delete save;
        ISWARNING = false;
    }
    SaveWhat ="";
}

void MainWindow::red_led(int leds)
{
    if(leds)
        system("echo 1 > /sys/class/leds/control_led2/brightness");
    else
        system("echo 0 > /sys/class/leds/control_led2/brightness");
}
void MainWindow::green_led(int leds)
{
    if(leds)
        system("echo 1 > /sys/class/leds/control_led3/brightness");
    else
        system("echo 0 > /sys/class/leds/control_led3/brightness");
}
void MainWindow::yellow_led(int leds)
{
    if(leds)
        system("echo 1 > /sys/class/leds/control_led4/brightness");
    else
        system("echo 0 > /sys/class/leds/control_led4/brightness");
}
void MainWindow::white_led(int leds)
{
    if(leds)
        system("echo 1 > /sys/class/leds/control_led9/brightness");
    else
        system("echo 0 > /sys/class/leds/control_led9/brightness");
}
void MainWindow::nok_led(int leds)
{
    if(leds)
        system("echo 1 > /sys/class/leds/control_led8/brightness");
    else
        system("echo 0 > /sys/class/leds/control_led8/brightness");
}

void MainWindow::wifishow(bool wificonnect)
{
    if(wificonnect)
        ui->label_wifi->show();
    else
        ui->label_wifi->hide();
}
void MainWindow::datashow(bool dataconnect)
{
    if(dataconnect)
        ui->label_ss2->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/68.bmp);");
    else
        ui->label_ss2->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/69.bmp);");
}

void MainWindow::batteryshow1(QString power)
{
    if(power == "17")
    {
        if(timer_showdown.isActive())
        {
            qDebug()<<"timer_showdown stop";
            timer_showdown.stop();
        }
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery2.png);background:transparent;");
    }
    else if(power == "16")
    {
        if(timer_showdown.isActive())
        {
            qDebug()<<"timer_showdown stop";
            timer_showdown.stop();
        }
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery1.png);background:transparent;");
    }
    else if(power == "05")
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery.png);background:transparent;");
    else if(power == "04")
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery_2.png);background:transparent;");
    else if(power == "03")
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery_red.png);background:transparent;");
    else if(power == "02"||power == "01")
    {
        //15 分钟后关机
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery_red.png);background:transparent;");
        timer_showdown.start(900000);
    }
}

void MainWindow::battery15()
{
    system("echo 0 > /sys/class/leds/control_lvds/brightness");  //关背光
    qDebug("power down 1");
    system("halt");
}

void MainWindow::batteryshow2(bool balive)
{
    if(balive)
    {
        shutdown_timer.start(300000);
        ui->label_battery->show();
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery.png);background:transparent;");
    }
    else
    {
        shutdown_timer.stop();
        battry_num = 0;
        ui->label_battery->hide();
    }
}

void MainWindow::clocked()
{
    battry_num++;
    if(battry_num == 1)
    {
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery_2.png);background:transparent;");
    }
    else if(battry_num == 2)
    {
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery_red.png);background:transparent;");
    }
    else if(battry_num == 3)
    {
        system("echo 0 > /sys/class/leds/control_lvds/brightness");
        qDebug("power down 2");
        system("halt");
    }
}

void MainWindow::time_warning(bool time_warn)
{
    if(time_warn)
        ui->label_time->setText(tr("系统时间错误"));
    else
        ui->label_time->clear();
}

void MainWindow::ReceGunNotReady()
{
    yellow_led(1);
    ui->label_tiaomastate->setText(tr("拧紧枪没有准备"));
    ui->label_ss1->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/69.bmp);");
    ui->pushButton_16->setText("Not Ready");
    ui->pushButton_16->setStyleSheet("font: 19pt ; background-color: rgb(250, 0, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
}

void MainWindow::on_pushButton_shutdown_clicked()
{
    if(!ISmaintenance)
    {
        ISmaintenance = true;
        workmode = true;
        e3 = new QGraphicsOpacityEffect(this);
        e3->setOpacity(0.5);
        ui->label_black->setGraphicsEffect(e3);
        ui->label_black->show();
        ui->label_black->setGeometry(0,0,1366,768);
        SaveWhat = "shutdown";
        save = new Save;
        connect(save,SIGNAL(sendShutDown(int)),this,SLOT(shutdown(int)));
        save->show();
    }
}

void MainWindow::shutdown(int tmp)
{
    //qDebug() << "tmp " << tmp;
    if(tmp == 1)
    {
        qDebug() << "halt here";
        system("echo 0 > /sys/class/leds/control_lvds/brightness");
        system("halt");
    }
    else if(tmp == 2)
    {
        qDebug() << "reboot here";
        system("reboot");
    }
    else if(tmp == 3)
    {
        ui->label_black->hide();
        delete e3;
        delete save;
    }
    SaveWhat = "";
    ISmaintenance = false;
    workmode = false;
}
