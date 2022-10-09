#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mysqlConnect();
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setGeometry(QRect(0, 0, 1366, 768));

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    //this->setCursor(Qt::BlankCursor); //去掉光标

    channelNum = 1;//通道号 通过哪个控件进入到密码验证 1设置 2手自动切换
    init();
    this->setFixedSize(1366,768);
    this->setWindowTitle("B.I.W @Data2.1.0");
    //    connectMysql();
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
#if DYTEST1^1
    ui->pushButton_reset->hide();//确认全部按钮
//    ui->but_car61->hide();
//    ui->but_car62->hide();
//    ui->but_car68->hide();
//    ui->but_car69->hide();
#endif
    ui->pushButton_17->hide();
#if 1
        ui->btnLeft->setVisible(false);
    ui->btnRight->setVisible(false);
    ui->jump->setVisible(false);
#endif
    ui->labelTyre1->setVisible(false);
    ui->labelTyre2->setVisible(false);
    ui->labelTyre3->setVisible(false);
    ui->labelTyre4->setVisible(false);

    ui->btnIgnoreLeft->setVisible(false);
    ui->btnIgnoreRight->setVisible(false);

    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    controlType = config->value("/baseinfo/controlType").toString();
    delete config;

    numType = 0 ;


    QTimer *timer=new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(ShowTime()));
    if(SerialGunMode)
    {
        //        system("echo 0 > /sys/class/leds/control_uart2/brightness");
        system("echo 0 > /sys/class/leds/control_uart1/brightness");
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
    qDebug()<<"TightenIsReady:"<<isready<<SYSS;
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
                    DTdebug() << "pronum ==" << proNum;
                    DTdebug() << "lsnum ==" << lsNum;
                }
            }
        }
    }
    delete config;
}
void MainWindow::mysqlConnect()
{
    db = QSqlDatabase::addDatabase("QMYSQL","mysqlconnectionmatch");
    db.setHostName("localhost");
    db.setDatabaseName("Tighten");
    db.setUserName("root");
    db.setPassword("123456");
    query = QSqlQuery(db);
}



/**********************************连接mysql数据库*/
bool MainWindow::mysqlIsOpen()
{
    if(!db.isOpen() || !db.contains("mysqlconnectionmatch")){
        if(db.open()){
            qDebug()<<"open mysqlconnectionmatch success";
        }else{
            qDebug()<<"open mysqlconnectionmatch faile:"<<db.lastError().text();
        }
    }

    if(db.isOpen() && db.contains("mysqlconnectionmatch")){
        return true;
    }else{
        return false;
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
    //    extern QString info[7];
    //    extern QString status[100][5];
//        qDebug()<<"point[104]:"<<tempnumdpm<<states;
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
//        qDebug()<<"point[105]:";
    //##############################################
}

//根据配置信息匹配
void MainWindow::matchFuc(int i)
{
    whichar = i;
    howmuchProNnum = QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(i)).append("/IsOptionalStation")).toInt();

    //匹配成功,再判断是否选配
    if(howmuchProNnum)
    {
        //选配
        //匹配 数据库中的vin码
        bxuannumtmp= 0;
        int k =1;
        for(k = 1;k<6;k++)//5 遍历选配
        {
            int tt = 0;
            bool bixuanSuccess = false;
            for(int n = 1;n < 21;n++)//遍历20螺栓编号找到一个有值就出来
            {
                QVariant tt_var = QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/OPLSNumber").append(QString::number(k)).append(QString::number(n)));
                //OPLSNumber[1-5][1-20] OPLSNumber11~OPLSNumber520
                tt = tt_var.toInt();
                qDebug()<<"tt_var:"<<tt_var<<tt;
                if(tt)
                    break;
            }
            whichoption = k;
            if(tt)
            {
                DTdebug() << " whichoption" << whichoption;
                //取出选配，查询FIS 数据库，比对 必选fis信息
                selectVin = QString("select FisMatch from fisData where VIN ='%1'").arg(serialNums);
                DTdebug() << " selectVIN " << selectVin;
                if(mysqlIsOpen()){
                    query.exec(selectVin);
                    if(query.next())
                    {
                        //查到了匹配
                        QString strFis = query.value(0).toString().replace("\"","");
                        QStringList strList ;
                        strList  = strFis.split(",") ;

                        record = query.record();

                        for(int j = 1;j < 6;j++)//5 bixuan 遍历必选
                        {
                            QString bxname = QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/bxuanname").append(QString::number(whichoption)).append(QString::number(j))).toString();
                            QString bxcode = QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/bxuancode").append(QString::number(whichoption)).append(QString::number(j))).toString();

                            if(bxname == "" || bxcode == "")
                            {
                                DTdebug() << "name is null" ;
                                //continue;
                                break;
                            }
                            else
                            {
                                bxuannumtmp++;
                                QString bx = bxname + "=" + bxcode ;
                                qDebug()<<"bx=:"<<bx;
                                if(strList.contains(bx)){
                                    DTdebug() << "bixuanmatchsuccess"<<bx;
                                    equeloptionbnum++ ;
                                }else{
                                    //必选有一个失败直接不用匹配了，直接匹配下一个选配
                                    DTdebug() << "bixuanmatchfail"<<bx;
                                    break;
                                }
                            }
                        }
                        qDebug()<<"successCount:"<<equeloptionbnum<<bxuannumtmp;
                        if(equeloptionbnum == bxuannumtmp)
                        {
                            //必选全部匹配成功，直接使用，不需要匹配下一个选配和车型
                            bixuanSuccess = true;
                            matchSuccess = true;
//                            break;
                        }
                    }
                    else
                    {
                        //查不着 快速请求
                        DTdebug() << query.lastError();
                        continue;
                    }
                    mysqlclose();
                }
            }
            else
            {
                continue;
            }
            //  qDebug() << "NMNMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNequeloptionbnum " << equeloptionbnum;

            if(bixuanSuccess)
            {
                qDebug()<<"bixuanSuccess:"<<whichar<<whichoption;
                whichpronumis = 1;
                int statusop = 0;
                for(int j = 1;j< 21;j++)//一个螺栓编号最高可设置20个螺栓
                {
                    //                    qDebug()<<"point[101]:"<<j;
                    //
                    proNum = QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/OPProNum").append(QString::number(whichoption)).append(QString::number(j))).toString();
                    lsNum = QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/OPLSNumber").append(QString::number(whichoption)).append(QString::number(j))).toString();
                    SCREWID_SQL = QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/OPLuoSuanNum").append(QString::number(whichoption)).append(QString::number(j))).toString();
                    VIN_PIN_SQL = serialNums;
                    enableLsnumber = lsNum.toInt();
                    if(enableLsnumber)
                    {
                        //                        qDebug()<<"point[102]:";
                        ui->label_pronum->setText(proNum);
                        int count_num = 0;
                        for(int m =1;m < 21;m++)
                        {
                            if(QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/OPLSNumber").append(QString::number(whichoption)).append(QString::number(m))).toInt() > 0)
                                count_num++;
                        }
                        ui->label_lsnum->setText(QString::number(count_num));
                        ui->label_hege->setText("0");
                        QString namepdm =  QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/pdmyinyong").append(QString::number(whichoption))).toString();
                        tempnumdpm = 0;
                        QString pathpdm;
                        int j = 1;
                        for( j = 1;j<250;j++)
                        {
                            if(namepdm == QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/pdmname")))
                            {
                                tempnumdpm = QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/num")).toInt();
                                pathpdm = QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/pdmpath")).toString();
                                break;
                            }
                        }
                        //                        qDebug()<<"point[103]:";
                        sendWebValue(1,pathpdm);
                        //显示PDM图
                        ui->label_pdmarea->setStyleSheet(QString("QLabel#label_pdmarea{border-image: url(/PDM/").append(pathpdm).append(")}"));

                        numpdm = 0;
                        info[4] =QString::number(tempnumdpm);
                        for(int i = 0;i<butt.size();i++){
                            butt.at(i)->deleteLater();
                            label1.at(i)->deleteLater();
                            label2.at(i)->deleteLater();
                        }
                        butt.clear();
                        label1.clear();
                        label2.clear();
                        for(int i = 0;i < tempnumdpm;i++)
                        {
                            QPushButton *bunTemp = new QPushButton(ui->label_pdmarea);//显示螺栓状态 白，黄，绿，红
                            QLabel *labelTemp1 = new QLabel(ui->label_pdmarea);//上面一个显示扭矩
                            QLabel *labelTemp2 = new QLabel(ui->label_pdmarea);//下面一个显示角度
                            butt<<bunTemp;
                            label1<<labelTemp1;
                            label2<<labelTemp2;

                            butt.at(i)->raise();
                            butt.at(i)->setFlat(true);
                            label1.at(i)->setAlignment(Qt::AlignLeft);
                            label2.at(i)->setAlignment(Qt::AlignLeft);
                            butt.at(i)->setFocusPolicy(Qt::NoFocus);
                            label1.at(i)->setFocusPolicy(Qt::NoFocus);
                            label2.at(i)->setFocusPolicy(Qt::NoFocus);
                            butt.at(i)->setAttribute(Qt::WA_TransparentForMouseEvents);
                            label1.at(i)->setAttribute(Qt::WA_TransparentForMouseEvents);
                            label2.at(i)->setAttribute(Qt::WA_TransparentForMouseEvents);
                            numpdm++;
                            // temppdm = numpdm -1;


                            int tempx = QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/tempx").append(QString::number((i+1)))).toInt();
                            int tempy =  QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/tempy").append(QString::number((i+1)))).toInt();
                            status[i][3] =QString::number(tempx);
                            status[i][4] =QString::number(tempy);
                            double x = (double)tempx/1000 * 1166;// +  200;
                            double y = (double)tempy/1000 * 598;//+ 170;
                            butt.at(i)->setGeometry(x,y,46,46);
                            label1.at(i)->setGeometry(x+23,y,130,23);
                            label2.at(i)->setGeometry(x+23,y+23,130,23);
                            label1.at(i)->setStyleSheet("background:transparent;color: rgb(0, 0, 0);");
                            label2.at(i)->setStyleSheet("background:transparent;color: rgb(0, 0, 0);");
                            butt.at(i)->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/w01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                            butt.at(i)->setText(QString::number((i+1)));
                            butt.at(i)->show();
                            label1.at(i)->show();
                            label2.at(i)->show();
                            //                            ui->label_pdmarea->show();
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
        if(k == 6)//5个选配匹配完都没匹配到
        {
            ui->label_tiaomastate->setText(tr("选配匹配失败"));
            ISmaintenance = false;
            workmode = false;
            //                system("echo 0 > /sys/class/leds/control_uart2/brightness");
            system("echo 0 > /sys/class/leds/control_uart1/brightness");
        }
    }else//不选配
    {
        matchSuccess = true;//不选配，该车型走一遍逻辑不再去匹配下一个车型
        //设置获取匹配成功后的 程序号
        //再判断是否有套筒
        DTdebug() << "fei xuan pei is  come in !!!!!!!";
        whichpronumis = 1;
        int j = 1;
        for(j = 1;j< 21;j++)
        {
            int tao_tong = QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/Taotong").append(QString::number(j))).toInt();
            if(tao_tong >0 && tao_tong < 9)
            {
                // DTdebug() << "tao tong fei xuan pei is  come in !!!!!!!";
                VIN_PIN_SQL = serialNums;
                TAOTONG = tao_tong;
                QString namepdm =  QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/pdmyinyong")).toString();
                tempnumdpm = 0;
                whichpronumis=1;
                QString pathpdm;
                int j = 1;
                for( j = 1;j<250;j++)
                {
                    if(namepdm == QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/pdmname")))
                    {
                        //tempnumdpm PDM显示的螺栓的个数绿点
                        tempnumdpm = QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/num")).toInt();
                        //pdm图片文件名称（带后缀）
                        pathpdm = QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/pdmpath")).toString();
                        break;
                    }
                }
                if(PDM_PATH != pathpdm)
                {
                    if(j!=250)
                    {
                        ui->label_pdmarea->setStyleSheet(QString("QLabel#label_pdmarea{border-image: url(/PDM/").append(pathpdm).append(")}"));
                    }
                    PDM_PATH = pathpdm;
                }
                numpdm = 0;
                //************套筒值为web****************
                sendWebValue(1,pathpdm);
                info[4] =QString::number(tempnumdpm);
                for(int i = 0;i<butt.size();i++){
                    butt.at(i)->deleteLater();
                    label1.at(i)->deleteLater();
                    label2.at(i)->deleteLater();
                }
                butt.clear();
                label1.clear();
                label2.clear();
                for(int i = 0;i < tempnumdpm;i++)
                {
                    QPushButton *bunTemp = new QPushButton(ui->label_pdmarea);//显示螺栓状态 白，黄，绿，红
                    QLabel *labelTemp1 = new QLabel(ui->label_pdmarea);//上面一个显示扭矩
                    QLabel *labelTemp2 = new QLabel(ui->label_pdmarea);//下面一个显示角度
                    butt<<bunTemp;
                    label1<<labelTemp1;
                    label2<<labelTemp2;
                    butt.at(i)->raise();
                    butt.at(i)->setFlat(true);
                    label1.at(i)->setAlignment(Qt::AlignLeft);
                    label2.at(i)->setAlignment(Qt::AlignLeft);
                    butt.at(i)->setFocusPolicy(Qt::NoFocus);
                    label1.at(i)->setFocusPolicy(Qt::NoFocus);
                    label2.at(i)->setFocusPolicy(Qt::NoFocus);
                    butt.at(i)->setAttribute(Qt::WA_TransparentForMouseEvents);
                    label1.at(i)->setAttribute(Qt::WA_TransparentForMouseEvents);
                    label2.at(i)->setAttribute(Qt::WA_TransparentForMouseEvents);

                    numpdm++;


                    butt.at(i)->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/w01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                    butt.at(i)->setText(QString::number((i+1)));

                    int tempx = QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/tempx").append(QString::number((i+1)))).toInt();
                    int tempy =  QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/tempy").append(QString::number((i+1)))).toInt();
                    status[i][3] =QString::number(tempx);
                    status[i][4] =QString::number(tempy);
                    double x = (double)tempx/1000 * 1166 ;//+ 200;
                    double y = (double)tempy/1000 * 598 ;//+ 170;
                    butt.at(i)->setGeometry(x,y,46,46);
                    label1.at(i)->setGeometry(x+23,y,130,23);
                    label2.at(i)->setGeometry(x+23,y+23,130,23);
                    label1.at(i)->setStyleSheet("background:transparent;color: rgb(0, 0, 0);");
                    label2.at(i)->setStyleSheet("background:transparent;color: rgb(0, 0, 0);");
                    butt.at(i)->show();
                    label1.at(i)->show();
                    label2.at(i)->show();
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
                // DTdebug() << "here";
                white_led(1);
                ui->pushButton_16->setStyleSheet("font: 50pt ; background-color: rgb(250, 225, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                SYSS = "ING";
                TaoTongState = true;

                break;
            }

            proNum = QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/ProNum").append(QString::number(j))).toString();
            lsNum = QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/LSNumber").append(QString::number(j))).toString();
            SCREWID_SQL = QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/LuoSuanNum").append(QString::number(j))).toString();
            DTdebug() <<"screwid" <<SCREWID_SQL;
            QString carname = "";
            carname =  QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar).append("/carcx"))).toString();
            VIN_PIN_SQL = serialNums;
            enableLsnumber = lsNum.toInt();
            if(enableLsnumber)
            {
                ui->label_pronum->setText(proNum);
                int count_num = 0;
                for(int m =1;m < 21;m++)
                {
                    if(QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/LSNumber").append(QString::number(m))).toInt() > 0)
                        count_num++;
                }
                ui->label_lsnum->setText(QString::number(count_num));
                ui->label_hege->setText("0");
                QString namepdm =  QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(whichar)).append("/pdmyinyong")).toString();
                tempnumdpm = 0;
                QString pathpdm;
                int j = 1;
                for( j = 1;j<250;j++)
                {
                    if(namepdm == QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/pdmname")))
                    {
                        tempnumdpm = QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/num")).toInt();
                        pathpdm = QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/pdmpath")).toString();
                        break;
                    }
                }
                if(PDM_PATH != pathpdm)
                {
                    if(j!=250)
                    {
                        ui->label_pdmarea->setStyleSheet(QString("QLabel#label_pdmarea{border-image: url(/PDM/").append(pathpdm).append(")}"));
                    }
                    PDM_PATH = pathpdm;
                }

                //  DTdebug() << pathpdm;
                numpdm = 0;
                /************发给web端空白螺栓****************/
                sendWebValue(1,pathpdm);
                info[4] =QString::number(tempnumdpm);
                for(int i = 0;i<butt.size();i++){
                    butt.at(i)->deleteLater();
                    label1.at(i)->deleteLater();
                    label2.at(i)->deleteLater();
                }
                butt.clear();
                label1.clear();
                label2.clear();
                for(int i = 0;i < tempnumdpm;i++)
                {
                    QPushButton *bunTemp = new QPushButton(ui->label_pdmarea);//显示螺栓状态 白，黄，绿，红
                    QLabel *labelTemp1 = new QLabel(ui->label_pdmarea);//上面一个显示扭矩
                    QLabel *labelTemp2 = new QLabel(ui->label_pdmarea);//下面一个显示角度
                    butt<<bunTemp;
                    label1<<labelTemp1;
                    label2<<labelTemp2;
                    butt.at(i)->raise();
                    butt.at(i)->setFlat(true);
                    label1.at(i)->setAlignment(Qt::AlignLeft);
                    label2.at(i)->setAlignment(Qt::AlignLeft);
                    butt.at(i)->setFocusPolicy(Qt::NoFocus);
                    label1.at(i)->setFocusPolicy(Qt::NoFocus);
                    label2.at(i)->setFocusPolicy(Qt::NoFocus);
                    butt.at(i)->setAttribute(Qt::WA_TransparentForMouseEvents);
                    label1.at(i)->setAttribute(Qt::WA_TransparentForMouseEvents);
                    label2.at(i)->setAttribute(Qt::WA_TransparentForMouseEvents);

                    numpdm++;
                    // temppdm = numpdm -1;

                    butt.at(i)->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/w01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                    butt.at(i)->setText(QString::number((i+1)));

                    int tempx = QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/tempx").append(QString::number((i+1)))).toInt();
                    int tempy =  QSettings("/config.ini", QSettings::IniFormat).value(QString("pdminfo").append(QString::number((j))).append("/tempy").append(QString::number((i+1)))).toInt();
                    status[i][3] =QString::number(tempx);
                    status[i][4] =QString::number(tempy);
                    double x = (double)tempx/1000 * 1166;// + 200;
                    double y = (double)tempy/1000 * 598 ;//+ 170;
                    butt.at(i)->setGeometry(x,y,46,46);
                    label1.at(i)->setGeometry(x+23,y,130,23);
                    label2.at(i)->setGeometry(x+23,y+23,130,23);
                    label1.at(i)->setStyleSheet("background:transparent;color: rgb(0, 0, 0);");
                    label2.at(i)->setStyleSheet("background:transparent;color: rgb(0, 0, 0);");
                    butt.at(i)->show();
                    label1.at(i)->show();
                    label2.at(i)->show();
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
                //                        system("echo 0 > /sys/class/leds/control_uart2/brightness");
                system("echo 0 > /sys/class/leds/control_uart1/brightness");
            }
            ISmaintenance = false;
            workmode = false;
        }
    }
}



/*******************匹配VIN码***************************/
void MainWindow::searchVinNum()
{
    FUNC() ;
    //匹配VIN码
    QString strCarType = "" ;
    QString strSqlSelect = QString("select CarID from %1 where VIN='%2'").arg(SQL_TABLE_FISDATA).arg(serialNums);
    if(mysqlIsOpen()){
        if(!query.exec(strSqlSelect))
        {
            DTdebug() << query.lastError() << strSqlSelect;
        }
        else
        {
            if(query.next())
            {
                //从fisData表中查到当前VIN码对应的CarID
                strCarType = query.value(0).toString();
            }
        }
        mysqlclose();
    }
    //车型匹配
    bool successCar = false;
    for(int i = 1;i < 21;i++)//20 car type 遍历20个车型
    {
        QString temp = QSettings("/config.ini", QSettings::IniFormat).value(QString("carinfo").append(QString::number(i)).append("/VIN")).toString();
        matchSuccess = false;//默认未成功匹配，所有配置要遍历匹配
        qDebug()<<"carCycle:"<<i;
        //CarID不为空且与配置的VIN特征码一致
        if((!strCarType.isEmpty()) && (strCarType == temp))
        {
            ui->label_tiaomastate->setText(tr(""));
            successCar = true ;
            matchFuc(i);
            DTdebug() << "config" << temp << "sql:" << strCarType ;
            //break;
        }
        else {
            successCar = false ;
            //matchFuc(i);
            DTdebug() << "config" << temp << "sql:" << strCarType ;
        }
        if(matchSuccess){
            break;
        }
    }
    if(!successCar)//未匹配到车型
    {
        ui->label_tiaomastate->setText(tr("特征码匹配失败"));
        if(SerialGunMode)
        {
            //            system("echo 0 > /sys/class/leds/control_uart2/brightness");
            system("echo 0 > /sys/class/leds/control_uart1/brightness");
        }
        ISmaintenance = false;
        workmode = false;
    }
}

/********************获取扫描枪的条码**************************/
void MainWindow::getSerialNum(QString serialNum,bool equeled,QString tempp)
{

    DTdebug() <<"getSerialNum():"<<serialNum << equeled<<tempp<<serialNums << statusType;
    //"LSKG5GC13KA076431" "" ""
    if(controlType == "PMM")
    {
        if(serialNum == serialNums)
        {
            if(tyreNum == 4 && statusType == "OK")
            {
                tyreNum = 0 ;

                statusType = " " ;
                startNum = 1 ;
                ui->labelTyre1->setVisible(false);
                ui->labelTyre2->setVisible(false);
                ui->labelTyre3->setVisible(false);
                ui->labelTyre4->setVisible(false);
            }
            else {
                return ;
            }

        }
        else {
            tyreNum = 0 ;
            statusType = " " ;
            if(startNum >4)
            {
                startNum = 1 ;
            }


            ui->labelTyre1->setVisible(false);
            ui->labelTyre2->setVisible(false);
            ui->labelTyre3->setVisible(false);
            ui->labelTyre4->setVisible(false);
            //        serialNums = serialNum ;
        }
    }
    ui->label_tiaomastate->setText("");
    ui->label_17->setText(serialNums);

    ui->labelTyre1->setVisible(false);
    ui->labelTyre2->setVisible(false);
    ui->labelTyre3->setVisible(false);
    ui->labelTyre4->setVisible(false);

    ui->labelTyre1->setAlignment(Qt::AlignCenter) ;
    ui->labelTyre2->setAlignment(Qt::AlignCenter) ;
    ui->labelTyre3->setAlignment(Qt::AlignCenter) ;
    ui->labelTyre4->setAlignment(Qt::AlignCenter) ;

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
                //                system("echo 0 > /sys/class/leds/control_uart2/brightness");
                system("echo 0 > /sys/class/leds/control_uart1/brightness");
            }
            ISmaintenance = false;
            workmode = false;
        }else
        {
            //关闭条码枪
            ui->label_17->setText(serialNums);
            qDebug()<<"CsIsConnect:"<<CsIsConnect;
            CsIsConnect = true;
            if(CsIsConnect && serialNums.size() == 17) //351没连接 不匹配
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






/********************500ms**PDM闪烁*****************************/

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
            if(controlType == "PMM")
            {
                if(whichpdmnumnow != 0 && whichpdmnumnow != 5 && whichpdmnumnow != 10 && whichpdmnumnow != 15 )
                {
                    DTdebug() << "whichpdmnumnow  twinkle" << whichpdmnumnow ;
                    return ;
                }
                int twinkle = whichpdmnumnow+5;
                for(int i = whichpdmnumnow;i<twinkle;i++)
                {
                    if(pdmflicker)
                    {
                        butt.at(i)->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/r01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                    }
                    else
                    {
                        butt.at(i)->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/y01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                    }
                }
            }
            else {
                if(pdmflicker)
                {
                    butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/r01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                }
                else
                {
                    butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/y01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                }
            }

        }
        else
        {
            if(controlType == "PMM")
            {
                if(whichpdmnumnow != 0 && whichpdmnumnow != 5 && whichpdmnumnow != 10 && whichpdmnumnow != 15 || whichpdmnumnow >14)
                {
                    DTdebug() << "whichpdmnumnow  twinkle" << whichpdmnumnow ;
                    return ;
                }
                DTdebug() << whichpdmnumnow ;
                int twinkle = whichpdmnumnow+5;
                for(int i = whichpdmnumnow;i<twinkle;i++)
                {
                    if(pdmflicker)
                    {
                        butt.at(i)->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/y01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                    }
                    else
                    {
                        butt.at(i)->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/w01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                    }
                }
            }
            else {
                if(pdmflicker)
                {
                    butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/y01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                }
                else
                {
                    butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/w01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                }
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

    tempnumdpm = 0;

//    int tempdata = tempnumdpm;
//    qDebug()<<"tempnumdpm:"<<tempnumdpm;
//    for(int i = 0;i<tempdata;i++)
//    {
//        delete butt.at(i);
//        delete label1.at(i);
//        delete label2.at(i);
//        tempnumdpm--;
//    }
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
    FUNC() ;

    DTdebug() << MI << WI <<IsOk <<whichpdmnumnow;
    //0 dat  1 time   2 state   3  扭矩 4 角度 5 螺栓编号   6 vin pin 码   7 循环号  8 曲线
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    if(IsOk== "Reconnect")  //重新连接
    {
        if(enableLsnumber)
        {
            //            sendnexo(serialNums);
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
        status[whichpdmnumnow][1] = MI; // 螺栓扭矩
        status[whichpdmnumnow][2] = WI; // 螺栓角度
        //status[whichpdmnumnow][4] = data_model.DATE_b+" "+data_model.TIME_b;//螺栓拧紧时间
        if(IsOk == "NOK") // 本次螺栓不合格nok
        {
            status[whichpdmnumnow][0] = "5";  //螺栓状态
            info[0] = "1"; //拧紧状态
            ui->label_ceshipronum->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/32.bmp);");//没用
            if(whichpdmnumnow < tempnumdpm)  //界面显示螺栓信息
            {
                label1[whichpdmnumnow]->setText(QString(tr("   T:").append(MI).append("Nm")));
                label2[whichpdmnumnow]->setText(QString(tr("   A:").append(WI).append("°")));
                label1[whichpdmnumnow]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);color: rgb(0, 0, 0);");
                label2[whichpdmnumnow]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);color: rgb(0, 0, 0);");
                butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/r01.png);color: rgb(0, 0, 0);border-radius: 23px;");
            }
            qDebug()<<"this is NOK led[0]";
            nok_led(1); //only one NOK
            PDMCurrentState = "NOK";
            if(controlType == "PMM")
            {
                qDebug() <<"thiswhichpdmnumnow:"<<whichpdmnumnow ;
                if(numType<6)
                {
                    numType ++ ;
                    whichpdmnumnow ++ ;
                }

                if(numType == 5)
                {
                    numType = 0 ;
                    whichpdmnumnow = whichpdmnumnow-5 ;
                }
            }
            //timerpdm.stop();
        }
        else  //本次螺栓合格ok
        {
            ui->label_ceshipronum->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/70.bmp);");//没用
            if(MI!= "-1" && WI != "-1")
                QualifiedNum++;//合格数加1
            ui->label_hege->setText(QString::number(QualifiedNum));
            enableLsnumber--;   //结果ok 数量减1
            //DTdebug() << "enableLsnumber1" << enableLsnumber;
            qDebug()<<"thisisOKNum:"<<whichpdmnumnow<<tempnumdpm;
            if(whichpdmnumnow < tempnumdpm)
            {
                if(MI == "-1" && WI == "-1")
                { //nok确认1 个
                    DTdebug() << whichpdmnumnow << PDMCurrentState;
                    status[whichpdmnumnow][0] = "2";  //螺栓状态
                    pdmnowromisOk = false;
                    butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/r01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                    if(PDMCurrentState != "NOK" || controlType == "PMM" )//当前白螺栓
                    {
                        // DTdebug() << "psmdfpsdmfsdfsdfsfsdf";

                        label1[whichpdmnumnow]->setText(QString(tr("   T:").append("-1").append("Nm")));
                        label2[whichpdmnumnow]->setText(QString(tr("   A:").append("-1").append("°")));
                        label1[whichpdmnumnow]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);");
                        label2[whichpdmnumnow]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);");
                        //存入数据库
                    }
                    qDebug()<<"this is OK led[10]";
                    nok_led(0);

                    if(whichpdmnumnow < 50)
                    {
                        whichpdmnumnow++;
                    }
                    else
                    {
                        DTdebug() << "whichpdmnumnow can not ++" << whichpdmnumnow ;
                    }
                    timerpdm.start();
                }
                else
                {
                    //正常
                    qDebug()<<"this is OK led[11]";
                    nok_led(0);
                    butt[whichpdmnumnow]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/g01.png);color: rgb(0, 0, 0);border-radius: 23px;");

                    label1[whichpdmnumnow]->setText(QString(tr("   T:").append(MI).append("Nm")));
                    label2[whichpdmnumnow]->setText(QString(tr("   A:").append(WI).append("°")));
                    label1[whichpdmnumnow]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);color: rgb(0, 0, 0);");
                    label2[whichpdmnumnow]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);color: rgb(0, 0, 0);");
                    status[whichpdmnumnow][0] = "1";  //螺栓状态
                    if(whichpdmnumnow < 50)
                    {
                        whichpdmnumnow++;
                    }
                    else
                    {
                        DTdebug() << "whichpdmnumnow can not ++" << whichpdmnumnow ;
                    }

                    if(whichpdmnumnow < 20)
                    {
                        status[whichpdmnumnow][0] = "3";
                    }
                    else
                    {
                        DTdebug() << "last data" <<  whichpdmnumnow ;
                    }


                }
            }
            enablenumberLeft = enableLsnumber;
            PDMCurrentState = "OK";
            qDebug()<<"enableLsnumber:"<<enableLsnumber<<whichpronumis;
            if(!enableLsnumber)
            {
                if(whichpronumis == 20)
                {
                    TaoTongState = false;
                    white_led(0);
                    ui->label_lsnum->setText("0");
                    //程序号 打完
                    if(SerialGunMode)
                    {
                        //                        system("echo 0 > /sys/class/leds/control_uart2/brightness");
                        system("echo 0 > /sys/class/leds/control_uart1/brightness");
                    }
                    ISmaintenance = false;
                    workmode = false;
                    if(MI!= "-1" && WI != "-1")
                    {
                        if(!pdmnowromisOk)
                        {
                            ui->pushButton_16->setStyleSheet("font: 40pt ; background-color: rgb(255, 0, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                            ui->pushButton_16->setText("NOK");
                            status[whichpdmnumnow][0] = "2";  //螺栓状态
                            info[0] = "3"; //拧紧状态
                            SYSS = "NOK";
                            red_led(1);
                        }
                        else
                        {
                            ui->pushButton_16->setStyleSheet("font: 60pt ; background-color: rgb(25, 125, 44); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                            ui->pushButton_16->setText("OK");
                            status[whichpdmnumnow][0] = "1";  //螺栓状态
                            info[0] = "2"; //拧紧状态
                            SYSS = "OK";
                            green_led(1);
                        }
                        ISRESET  = true;
                        emit sendoperate();
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
                    //                    m_Timer.stop();
                    Stop();
                    ui->progressBar->setValue(0);
                    m_CurrentValue  = 0;
                    //  timerdelay.start(25000);
                }
                else
                {

                    // QualifiedNum = 0;
                    whichpronumis++;
                    int k = 0;
                    for( k = whichpronumis;k <21;k++)
                    {
                        if(!howmuchProNnum)  //非选配
                        {
                            int tao_tong = config->value(QString("carinfo").append(QString::number(whichar)).append("/Taotong").append(QString::number(whichpronumis))).toInt();
                            if(tao_tong>0 && tao_tong < 9)
                            {
                                //DTdebug() << "TAO TONG taoTONg tao tong" << tao_tong;
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
                            //ui->label_hege->setText("0");
                            emit sendoperate();
                            ui->label_pronum->setText(proNum);
                            enableLsnumber = lsNum.toInt();
                            ui->label_lsnum->setText(QString::number(ui->label_lsnum->text().toInt()-1));
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
                        ui->label_lsnum->setText("0");
                        if(MI!= "-1" && WI != "-1")
                        {
                            if(!pdmnowromisOk)
                            {
                                ui->pushButton_16->setStyleSheet("font: 40pt ; background-color: rgb(255, 0, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                                ui->pushButton_16->setText("NOK");
                                status[whichpdmnumnow][0] = "2";  //螺栓状态
                                info[0] = "3"; //拧紧状态
                                SYSS = "NOK";
                                red_led(1);
                            }
                            else
                            {
                                ui->pushButton_16->setStyleSheet("font: 60pt ; background-color: rgb(25, 125, 44); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
                                ui->pushButton_16->setText("OK");
                                SYSS = "OK";
                                green_led(1);
                                status[whichpdmnumnow][0] = "1";  //螺栓状态
                                info[0] = "2"; //拧紧状态
                                green_led(1);
                            }
                            ISRESET  = true;
                            emit sendoperate();
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
                        //                        m_Timer.stop();
                        // timerdelay.start(25000);
                        ISmaintenance = false;
                        if(SerialGunMode)
                        {
                            //                            system("echo 0 > /sys/class/leds/control_uart2/brightness");
                            system("echo 0 > /sys/class/leds/control_uart1/brightness");
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

/**********************主界面维护模式 设置按钮，可以进入设置界面*****************************/
void MainWindow::on_pushButton_12_clicked()
{
    //GO login
    //QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    //    system("echo 0 > /sys/class/leds/control_uart2/brightness");
    system("echo 0 > /sys/class/leds/control_uart1/brightness");
    if(!ISmaintenance)
    {
        ISmaintenance = true;
        workmode = true;
        PDM_PATH="";
        channelNum = 1;
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
/******************************
 * 处理手自动切换后一系列逻辑
 *****************************/
void MainWindow::autoManualSwitch()
{
    if(ui->pushButton_tighten->text()!="Manual")
    {
        ui->pushButton_tighten->setText(tr("Manual"));

        if(controlType == "Cleco"){
            system("echo 1 > /sys/class/leds/OUTC1/brightness"); //Cleco enable tool
        }
        else {
            system("echo 0 > /sys/class/leds/OUTC1/brightness");
        }

    }
    else
    {
        ui->pushButton_tighten->setText(tr("auto"));
#if 0
        system("echo 0 > /sys/class/leds/OUTC1/brightness"); //Cleco disable tool
#else
        if(controlType == "Cleco"){
            system("echo 0 > /sys/class/leds/OUTC1/brightness");
        }
        else {
            system("echo 1 > /sys/class/leds/OUTC1/brightness");
        }
#endif
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
        if (person ==0)//工程师登录
        {
            if(temp == config->value(QString("baseinfo/GCpassword")).toString()||
                    temp == "5027")
            {
                isJS = false;
                //ui->stackedWidget->setCurrentIndex(0);
                //newconfiginfo->clearCache();
                if(channelNum == 1){
                    newconfiginfo->initui();
                    newconfiginfo->show();
                }else if(channelNum == 2){
                    autoManualSwitch();
                }
                ui->pushButton_13->setStyleSheet("border-image: url(:/re/99.png)");
                ui->pushButton_password->setStyleSheet("border-image : url(:)");
                ui->pushButton_14->setStyleSheet("border-image : url(:/re/100.png)");
                ui->pushButton_error->setStyleSheet("border-image : url(:)");
                //ui->stackedWidget->setCurrentIndex(0);
                //usleep(10000);
                ui->stackedWidget->setCurrentIndex(0);
            }
            else
            {
                ui->pushButton_error->setStyleSheet("border-image : url(:/re/124.bmp)");
                ui->pushButton_password->setStyleSheet("border-image : url(:/re/94.bmp)");
                isFull = 0;
                temp = "";
            }
        }
        else if (person ==1)//技术员登录
        {
            if(temp == config->value(QString("baseinfo/JSpassword")).toString())
            {
                // DTdebug() << "SSSSSSSSSSSSSSSS";
                isJS = true;
                //ui->stackedWidget->setCurrentIndex(0);
                if(channelNum == 1){
                    newconfiginfo->initui();
                    newconfiginfo->show();
                }else if(channelNum == 2){
                    autoManualSwitch();
                }
                ui->pushButton_14->setStyleSheet("border-image: url(:/re/100.png)");
                ui->pushButton_13->setStyleSheet("border-image : url(:/re/99.png)");
                ui->pushButton_error->setStyleSheet("border-image : url(:)");
                ui->pushButton_password->setStyleSheet("border-image : url(:)");
                // ui->stackedWidget->setCurrentIndex(0);
                //usleep(10000);
                ui->stackedWidget->setCurrentIndex(0);
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


//确认全部(这个按钮现在没用,直接当普通函数调用的)
void MainWindow::on_pushButton_reset_clicked()
{
    //no ok 确认全部
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);

    if(SYSS == "ING")
    {
        if(SerialGunMode)
        {
            //            system("echo 0 > /sys/class/leds/control_uart2/brightness");
            system("echo 0 > /sys/class/leds/control_uart1/brightness");
        }
        info[0] = "3";
        SYSS = "NOK";
        m_Timer.stop();
        Stop();
        ui->progressBar->setValue(0);
        workmode = false;
        ISmaintenance = false;
        white_led(0);
        qDebug()<<"this is OK led[12]";
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
                butt[j]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/r01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                if(label1[j]->text() == "")
                {
                    label1[j]->setText(QString(tr("   T:").append("-1").append("Nm")));
                    label2[j]->setText(QString(tr("   A:").append("-1").append("°")));
                    label1[j]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);color: rgb(0, 0, 0);");
                    label2[j]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);color: rgb(0, 0, 0);");
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
                butt[j]->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/r01.png);color: rgb(0, 0, 0);border-radius: 23px;");
                if(label1[j]->text() == "")
                {
                    label1[j]->setText(QString(tr("   T:").append("-1").append("Nm")));
                    label2[j]->setText(QString(tr("   A:").append("-1").append("°")));
                    label1[j]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);color: rgb(0, 0, 0);");
                    label2[j]->setStyleSheet("font: 14pt;background-color: rgb(248, 248, 248);color: rgb(0, 0, 0);");
                    status[j][0]="2";
                    status[j][1]="-1";
                    status[j][2]="-1";
                }
            }
        }
        emit sendConfigureAll(howmuchProNnum,whichar,whichpronumis,whichoption);

        ui->pushButton_16->setStyleSheet("font: 40pt ; background-color: rgb(255, 0, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
        ui->pushButton_16->setText("NOK");
        red_led(1);
        TaoTongState = false; //确认全部关闭套筒
        ui->label_lsnum->setText("0");

    }

    delete config;
}

//nok确认1个(这个按钮现在没用,直接当普通函数调用的)
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


            if(controlType == "PMM" && statusType == "NOK")
            {
                QString strScrewid ;
                for(int i =0 ;i<5;i++)
                {
                    strScrewid = searchScrewID(startNum) ;
                    startNum ++ ;
                    emit  sendfromsecondthread(strScrewid,VIN_PIN_SQL,proNum);
                    pdmnowromisOk = false;
                    if(TaoTongState)
                    {
                        if(enableLsnumber == 1)
                        {
                            ISRESET = true;
                            //                            emit sendoperate();
                        }
                    }
                    fromsecondthreaddata("-1","-1","ok");

                }
                showTyreNum(g_direction,"OK");
            }
            else if (controlType == "PMM" && statusType == "OK" && g_direction == "Left " && (tyreNum == 1 || tyreNum == 3) ) {
                on_btnIgnoreRight_clicked();
            }
            else if (controlType == "PMM" && statusType == "OK" && g_direction == "Right" && (tyreNum == 1 || tyreNum == 3) ) {
                on_btnIgnoreLeft_clicked();
            }
            else if (controlType == "PMM" && statusType == "OK") {
                ui->btnIgnoreLeft->setVisible(true);
                ui->btnIgnoreRight->setVisible(true);
            }
            else {
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

//拧钥匙跳过螺栓处理
void MainWindow::configwarning(bool isconfigone)
{
    qDebug() << "MainWindow::configwarning"<<isconfigone;
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
    else//确认一个用
    {
        on_pushButton_17_clicked();
    }

}

/*****************套筒选择信号对应使能发送********************************/
void MainWindow::taotong_main(int  which_t)
{
    QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
    int tao_tong = config->value(QString("carinfo").append(QString::number(whichar)).append("/Taotong").append(QString::number(whichpronumis))).toInt();
    //    DTdebug() << "taotongis " << tao_tong << which_t;

    if(tao_tong == which_t)
    {
        if(!enableLsnumber)
        {
            //             DTdebug() << "send operate!!!";
            ui->label_tiaomastate->setText("");
            proNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/ProNum").append(QString::number(whichpronumis))).toString();
            lsNum = config->value(QString("carinfo").append(QString::number(whichar)).append("/LSNumber").append(QString::number(whichpronumis))).toString();
            ui->label_pronum->setText(proNum);
            ui->label_lsnum->setText(lsNum);
            //           DTdebug() << proNum << lsNum;
            SCREWID_SQL = config->value(QString("carinfo").append(QString::number(whichar)).append("/LuoSuanNum").append(QString::number(whichpronumis))).toString();
            QString carname = "";
            carname =  config->value(QString("carinfo").append(QString::number(whichar).append("/carcx"))).toString();
            VIN_PIN_SQL = serialNums;
            enableLsnumber = lsNum.toInt();
            if(enableLsnumber)
            {
                //sendnexo(serialNums);
                //               DTdebug() << "send operate";
                emit sendoperate();
            }
        }
    }
    else
    {
        ui->label_tiaomastate->setText(tr("请正确选择套筒"));
        TaoTongState = true;
        //        DTdebug() << "******select taotong *********" << enableLsnumber;
        if(enableLsnumber)
        {
            enableLsnumber=0;
            ISRESET  = true;
            emit sendoperate();
        }
    }

    delete config;
}


//跳所有螺栓确认处理
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
    {
        //        system("echo 0 > /sys/class/leds/OUTC1/brightness"); //Cleco disalbe tool
        system("echo 1 > /sys/class/leds/control_led2/brightness");
    }
    else
        system("echo 0 > /sys/class/leds/control_led2/brightness");
}
void MainWindow::green_led(int leds)
{
    if(leds)
    {
        //        system("echo 0 > /sys/class/leds/OUTC1/brightness"); //Cleco disalbe tool
        system("echo 1 > /sys/class/leds/control_led3/brightness");
    }
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

//钥匙盒上显示
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
            DTdebug()<<"timer_showdown stop";
            timer_showdown.stop();
        }
        ui->label_battery->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/logo/battery2.png);background:transparent;");
    }
    else if(power == "16")
    {
        if(timer_showdown.isActive())
        {
            DTdebug()<<"timer_showdown stop";
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
    DTdebug() << "power down 1";
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
        DTdebug()<<"power down 2";
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

//void MainWindow::ReceGunNotReady()
//{
//    yellow_led(1);
//    ui->label_tiaomastate->setText(tr("拧紧枪没有准备"));
//    ui->label_ss1->setStyleSheet("border-image: url(:/LCD_CS351/LCD_CS351/35_all/69.bmp);");
//    ui->pushButton_16->setText("Not Ready");
//    ui->pushButton_16->setStyleSheet("font: 19pt ; background-color: rgb(250, 0, 0); color: rgb(248, 248, 255); border-width:0px;   border-style:solid; border-color: rgb(51, 153, 255);  ");
//}

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
    //DTdebug() << "tmp " << tmp;
    if(tmp == 1)
    {
        DTdebug() << "halt here";
        system("echo 0 > /sys/class/leds/control_lvds/brightness");
        system("halt");
    }
    else if(tmp == 2)
    {
        DTdebug() << "reboot here";
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

//手自动切换按钮信号槽
void MainWindow::on_pushButton_tighten_clicked()
{
    channelNum = 2;
    ui->stackedWidget->setCurrentIndex(2);
    isFull = 0;
    person = 0;
    temp = "";
    ui->pushButton_13->setStyleSheet("border-image : url(:/re/93.bmp)");
    ui->pushButton_password->setStyleSheet("border-image : url(:/re/94.bmp)");
}

void MainWindow::showTyreNum(QString dir, QString status)
{
    FUNC();
    DTdebug() << dir<<status <<tyreNum << statusType <<status ;

    if(status == "NOK" && tyreNum == 0)
    {
#if 0
        ui->labelTyre1->setVisible(true);
        if(dir.contains("Left"))
        {
            ui->labelTyre1->setText("左前");

        }
        else if(dir.contains("Right")){
            ui->labelTyre1->setText("右前");
        }
#else
        tyreNum ++ ;
#endif
    }

    if(statusType == "OK" && status == "NOK"  )
    {
        tyreNum ++;
    }
    //    else if (statusType == "NOK" && status == "OK") {
    //        DTdebug() << tyreNum ;
    //    }
    else if (status == "OK" && statusType == "OK" ) {
        tyreNum ++ ;
    }
    else if (status == "OK" && statusType == " " ) {
        tyreNum ++ ;
    }
    else {
        DTdebug() << statusType <<status ;
    }
    statusType = status ;
#if 0
    if(status == "NOK")
    {
        if(tyreNum == 0)
        {
            ui->labelTyre1->setVisible(true);
            if(dir.contains("Left"))
            {
                ui->labelTyre1->setText("左前");

            }
            else if(dir.contains("Right")){
                ui->labelTyre1->setText("右前");
            }
        }
    }
    else if (status == "OK" ) {
        tyreNum ++ ;
    }
#endif


    if(tyreNum == 1)
    {
        ui->labelTyre1->setVisible(true);
        if(dir.contains("Left"))
        {/*RF*/
            ui->labelTyre1->setText("左前");
        }
        else if(dir.contains("Right")){/*LF*/
            ui->labelTyre1->setText("右前");
        }
    }
    else if (tyreNum == 2) {
        ui->labelTyre2->setVisible(true);
        if(dir.contains("Left"))
        {/*LF*/
            ui->labelTyre2->setText("左前");
        }
        else if(dir.contains("Right")){/*RF*/
            ui->labelTyre2->setText("右前");
        }
    }
    else if (tyreNum == 3) {
        ui->labelTyre3->setVisible(true);
        if(dir.contains("Left"))
        {/*LR*/
            ui->labelTyre3->setText("左后");
        }
        else if(dir.contains("Right")){/*RR*/
            ui->labelTyre3->setText("右后");
        }
    }
    else if (tyreNum == 4) {
        ui->labelTyre4->setVisible(true);
        if(dir == "Left ")
        {/*LR*/
            ui->labelTyre4->setText("左后");
        }
        else if(dir == "Right"){/*RR*/
            ui->labelTyre4->setText("右后");
        }
    }
}


QString MainWindow::searchScrewID(int lsNum)
{
#if 1
    FUNC() ;
    DTdebug() << g_direction << lsNum;

    QString bufScrwid = "" ;
    if(whichar == 0)
    {
        DTdebug() << "catType is wrong";
    }
    else
    {
        if((startNum < 6 && g_direction=="Right") || (startNum >10 && startNum <16 && g_direction=="Right") )
        {
            lsNum = lsNum+5 ;
        }
        else if (startNum>5 && startNum<11 && g_direction=="Left " || (startNum >15 && startNum <21 && g_direction=="Left ")) {
            lsNum -= 5 ;
        }
        QSettings *config = new QSettings("/config.ini", QSettings::IniFormat);
        for(int i = lsNum ; i<21 ;i++)
        {
            bufScrwid = config->value(QString("carinfo").append(QString::number(whichar)).append("/LuoSuanNum").append(QString::number(i))).toString();
            int temp = bufScrwid.mid(6,1).toInt();
            if(g_direction == "Left ")
            {
                DTdebug() << "left" << bufScrwid << temp%2;
                if(temp%2 == 1)
                {
                    break ;
                }

            }
            else if (g_direction == "Right")
            {
                DTdebug() << "left" << bufScrwid  << temp;
                if(temp%2 == 0 && temp != 0)
                {
                    break ;
                }
            }

        }
        DTdebug() <<"screwid" <<bufScrwid;
        delete config;
    }
    return bufScrwid ;
#endif
}

void MainWindow::on_btnLeft_clicked()
{
    //    Q_EMIT signalSendLeft();
    //    GTestTightenData = ui->lineEdit_test1->text();
    emit sendTestTightenData();
}

void MainWindow::on_btnRight_clicked()
{
    Q_EMIT signalSendRight();
}

void MainWindow::on_jump_clicked()
{
    on_pushButton_17_clicked();
}

void MainWindow::on_btnIgnoreLeft_clicked()
{
    FUNC() ;
    if(ui->btnIgnoreLeft->isVisible())
    {
        ui->btnIgnoreLeft->setVisible(false);
    }
    if(ui->btnIgnoreRight->isVisible())
    {
        ui->btnIgnoreRight->setVisible(false);
    }
    QString strScrewid ;
    g_direction = "Left " ;
    for(int i =0 ;i<5;i++)
    {
        strScrewid = searchScrewID(startNum) ;
        startNum ++ ;
        emit  sendfromsecondthread(strScrewid,VIN_PIN_SQL,proNum);
        pdmnowromisOk = false;
        if(TaoTongState)
        {
            if(enableLsnumber == 1)
            {
                ISRESET = true;
                //                            emit sendoperate();
            }
        }
        fromsecondthreaddata("-1","-1","ok");

    }
    showTyreNum(g_direction,"OK");
}

void MainWindow::on_btnIgnoreRight_clicked()
{
    FUNC() ;
    if(ui->btnIgnoreLeft->isVisible())
    {
        ui->btnIgnoreLeft->setVisible(false);
    }
    if(ui->btnIgnoreRight->isVisible())
    {
        ui->btnIgnoreRight->setVisible(false);
    }
    QString strScrewid ;
    g_direction = "Right" ;
    for(int i =0 ;i<5;i++)
    {
        strScrewid = searchScrewID(startNum) ;
        startNum ++ ;
        emit  sendfromsecondthread(strScrewid,VIN_PIN_SQL,proNum);
        pdmnowromisOk = false;
        if(TaoTongState)
        {
            if(enableLsnumber == 1)
            {
                ISRESET = true;
            }
        }
        fromsecondthreaddata("-1","-1","ok");

    }
    showTyreNum(g_direction,"OK");
}

void MainWindow::on_pushButton_16_clicked()
{
    //    getSerialNum("LSFAL11A2LA056750",false,"");//22
//    getSerialNum("LSKG5GC14LA064886",false,"");//20
}
