/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButton_16;
    QWidget *widget_2;
    QLabel *label_17;
    QLabel *label_tiaomastate;
    QLabel *label_time;
    QProgressBar *progressBar;
    QStackedWidget *stackedWidget_6;
    QWidget *stackedWidget_6Page1;
    QWidget *widget;
    QPushButton *pushButton_10;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line;
    QPushButton *pushButton_12;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLabel *label_gongwei;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLabel *label_gonghao;
    QWidget *layoutWidget_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_pronum;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *label_lsnum;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *label_hege;
    QLabel *label_7;
    QLabel *label_tiaoma;
    QLabel *label_8;
    QLabel *label_ss1;
    QLabel *label_9;
    QLabel *label_ss2;
    QLabel *label_10;
    QLabel *label_ss3;
    QLabel *label_11;
    QLabel *label_ss4;
    QLabel *label_16;
    QLabel *label_tighten;
    QPushButton *pushButton_shutdown;
    QLabel *label_18;
    QLabel *label_15;
    QLabel *label_ceshipronum;
    QLabel *label_pdmarea;
    QLabel *label_ceshiniuju;
    QLabel *label_ceshijiaodu;
    QPushButton *pushButton_17;
    QPushButton *pushButton_reset;
    QLabel *label_battery;
    QLabel *label_wifi;
    QLabel *label_12;
    QWidget *page_4;
    QPushButton *pushButton_18;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_wifi_2;
    QLabel *label_black;
    QWidget *page_3;
    QWidget *widget_3;
    QWidget *page_2;
    QGroupBox *groupBox_4;
    QWidget *widget_4;
    QPushButton *pushButton_15;
    QWidget *widget_5;
    QPushButton *pushButton_14;
    QPushButton *pushButton_13;
    QPushButton *pushButton_error;
    QPushButton *pushButton_password;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_0;
    QPushButton *pushButton_delete;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1366, 768);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1366, 768));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 248, 255);"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        pushButton_16 = new QPushButton(page);
        pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));
        pushButton_16->setEnabled(true);
        pushButton_16->setGeometry(QRect(1204, 10, 151, 151));
        QPalette palette;
        QBrush brush(QColor(248, 248, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        pushButton_16->setPalette(palette);
        pushButton_16->setFocusPolicy(Qt::NoFocus);
        pushButton_16->setStyleSheet(QString::fromUtf8("font: 19pt ;\n"
"background-color: rgb(255, 0, 0);\n"
"color: rgb(248, 248, 255);\n"
"border-width:0px;  \n"
"border-style:solid;\n"
"border-color: rgb(51, 153, 255);  \n"
""));
        pushButton_16->setFlat(true);
        widget_2 = new QWidget(page);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 1204, 170));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 248, 255);"));
        label_17 = new QLabel(widget_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 10, 1184, 151));
        label_17->setStyleSheet(QString::fromUtf8("font: 60pt \"\351\273\221\344\275\223\";\n"
"background:transparent;\n"
"\n"
""));
        label_17->setAlignment(Qt::AlignCenter);
        label_tiaomastate = new QLabel(widget_2);
        label_tiaomastate->setObjectName(QString::fromUtf8("label_tiaomastate"));
        label_tiaomastate->setGeometry(QRect(20, 130, 171, 21));
        label_tiaomastate->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"color: rgb(255, 0, 0);\n"
"font: 12pt \"\351\273\221\344\275\223\";"));
        label_time = new QLabel(widget_2);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(180, 130, 171, 21));
        label_time->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"color: rgb(255, 0, 0);\n"
"font: 12pt \"\351\273\221\344\275\223\";"));
        progressBar = new QProgressBar(widget_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 10, 1184, 151));
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar:horizontal {\n"
"border: 1px solid  rgb(51, 153, 255);\n"
"background: rgb(248, 248, 255);\n"
"padding: 1px;\n"
"}\n"
"QProgressBar::chunk:horizontal {\n"
"background-color: rgb(51, 155, 255);\n"
"}"));
        progressBar->setValue(24);
        progressBar->setTextVisible(false);
        progressBar->raise();
        label_17->raise();
        label_time->raise();
        label_tiaomastate->raise();
        stackedWidget_6 = new QStackedWidget(page);
        stackedWidget_6->setObjectName(QString::fromUtf8("stackedWidget_6"));
        stackedWidget_6->setGeometry(QRect(0, 170, 1366, 598));
        stackedWidget_6->setStyleSheet(QString::fromUtf8(""));
        stackedWidget_6Page1 = new QWidget();
        stackedWidget_6Page1->setObjectName(QString::fromUtf8("stackedWidget_6Page1"));
        widget = new QWidget(stackedWidget_6Page1);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 200, 598));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(51, 153, 255);"));
        pushButton_10 = new QPushButton(widget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setEnabled(false);
        pushButton_10->setGeometry(QRect(28, 20, 143, 61));
        pushButton_10->setFocusPolicy(Qt::NoFocus);
        pushButton_10->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"border-image: url(:/LCD_CS351/LCD_CS351/35_all/logo.png);\n"
"\n"
""));
        pushButton_10->setFlat(true);
        line_2 = new QFrame(widget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(21, 204, 160, 5));
        line_2->setAutoFillBackground(false);
        line_2->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/logo/line.bmp);\n"
"background:transparent;"));
        line_2->setMidLineWidth(0);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(widget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(20, 311, 160, 5));
        line_3->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/logo/line.bmp);\n"
"background:transparent;"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line = new QFrame(widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(20, 417, 160, 5));
        line->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/logo/line.bmp);\n"
"background:transparent;"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        pushButton_12 = new QPushButton(widget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setEnabled(true);
        pushButton_12->setGeometry(QRect(114, 522, 51, 51));
        pushButton_12->setFocusPolicy(Qt::NoFocus);
        pushButton_12->setStyleSheet(QString::fromUtf8("border-image: url(:/re/settings.png);\n"
"color: rgb(248, 248, 255);\n"
"font: 14pt \"\351\273\221\344\275\223\";\n"
"\n"
""));
        pushButton_12->setFlat(true);
        layoutWidget_3 = new QWidget(widget);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(20, 224, 161, 71));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(layoutWidget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));

        horizontalLayout_4->addWidget(label_4);

        label_gongwei = new QLabel(layoutWidget_3);
        label_gongwei->setObjectName(QString::fromUtf8("label_gongwei"));
        label_gongwei->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));

        horizontalLayout_4->addWidget(label_gongwei);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(layoutWidget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));

        horizontalLayout_5->addWidget(label_5);

        label_gonghao = new QLabel(layoutWidget_3);
        label_gonghao->setObjectName(QString::fromUtf8("label_gonghao"));
        label_gonghao->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));

        horizontalLayout_5->addWidget(label_gonghao);


        verticalLayout_2->addLayout(horizontalLayout_5);

        layoutWidget_4 = new QWidget(widget);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(20, 90, 161, 101));
        verticalLayout = new QVBoxLayout(layoutWidget_4);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));

        horizontalLayout->addWidget(label);

        label_pronum = new QLabel(layoutWidget_4);
        label_pronum->setObjectName(QString::fromUtf8("label_pronum"));
        label_pronum->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));

        horizontalLayout->addWidget(label_pronum);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));

        horizontalLayout_2->addWidget(label_2);

        label_lsnum = new QLabel(layoutWidget_4);
        label_lsnum->setObjectName(QString::fromUtf8("label_lsnum"));
        label_lsnum->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));

        horizontalLayout_2->addWidget(label_lsnum);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));

        horizontalLayout_3->addWidget(label_3);

        label_hege = new QLabel(layoutWidget_4);
        label_hege->setObjectName(QString::fromUtf8("label_hege"));
        label_hege->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));

        horizontalLayout_3->addWidget(label_hege);


        verticalLayout->addLayout(horizontalLayout_3);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(23, 377, 80, 19));
        label_7->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));
        label_tiaoma = new QLabel(widget);
        label_tiaoma->setObjectName(QString::fromUtf8("label_tiaoma"));
        label_tiaoma->setGeometry(QRect(109, 376, 51, 19));
        label_tiaoma->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));
        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(22, 442, 48, 16));
        label_8->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));
        label_ss1 = new QLabel(widget);
        label_ss1->setObjectName(QString::fromUtf8("label_ss1"));
        label_ss1->setGeometry(QRect(78, 442, 16, 16));
        label_ss1->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/35_all/69.bmp);"));
        label_9 = new QLabel(widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(105, 442, 48, 16));
        label_9->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));
        label_ss2 = new QLabel(widget);
        label_ss2->setObjectName(QString::fromUtf8("label_ss2"));
        label_ss2->setGeometry(QRect(159, 442, 16, 16));
        label_ss2->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/35_all/69.bmp);"));
        label_10 = new QLabel(widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(22, 482, 51, 16));
        label_10->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));
        label_ss3 = new QLabel(widget);
        label_ss3->setObjectName(QString::fromUtf8("label_ss3"));
        label_ss3->setGeometry(QRect(78, 482, 16, 16));
        label_ss3->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/35_all/69.bmp);"));
        label_11 = new QLabel(widget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(108, 482, 40, 16));
        label_11->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));
        label_ss4 = new QLabel(widget);
        label_ss4->setObjectName(QString::fromUtf8("label_ss4"));
        label_ss4->setGeometry(QRect(159, 482, 16, 16));
        label_ss4->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/35_all/69.bmp);"));
        label_16 = new QLabel(widget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(23, 335, 80, 19));
        label_16->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));
        label_tighten = new QLabel(widget);
        label_tighten->setObjectName(QString::fromUtf8("label_tighten"));
        label_tighten->setGeometry(QRect(109, 335, 51, 19));
        label_tighten->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));
        pushButton_shutdown = new QPushButton(widget);
        pushButton_shutdown->setObjectName(QString::fromUtf8("pushButton_shutdown"));
        pushButton_shutdown->setEnabled(true);
        pushButton_shutdown->setGeometry(QRect(30, 529, 41, 41));
        pushButton_shutdown->setFocusPolicy(Qt::NoFocus);
        pushButton_shutdown->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/logo/on_0ff.png);\n"
"color: rgb(248, 248, 255);\n"
"font: 14pt \"\351\273\221\344\275\223\";\n"
"\n"
""));
        pushButton_shutdown->setFlat(true);
        label_8->raise();
        label_ss1->raise();
        label_9->raise();
        label_ss2->raise();
        label_10->raise();
        label_ss3->raise();
        label_11->raise();
        label_ss4->raise();
        label_7->raise();
        label_tiaoma->raise();
        pushButton_10->raise();
        line_2->raise();
        line_3->raise();
        line->raise();
        pushButton_12->raise();
        layoutWidget_3->raise();
        layoutWidget_4->raise();
        label_16->raise();
        label_tighten->raise();
        pushButton_shutdown->raise();
        label_18 = new QLabel(stackedWidget_6Page1);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(460, 81, 25, 16));
        label_18->setStyleSheet(QString::fromUtf8("background:transparent;"));
        label_15 = new QLabel(stackedWidget_6Page1);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(350, 81, 25, 16));
        label_15->setStyleSheet(QString::fromUtf8("background:transparent;"));
        label_ceshipronum = new QLabel(stackedWidget_6Page1);
        label_ceshipronum->setObjectName(QString::fromUtf8("label_ceshipronum"));
        label_ceshipronum->setGeometry(QRect(250, 80, 51, 21));
        label_ceshipronum->setStyleSheet(QString::fromUtf8("background:transparent;"));
        label_pdmarea = new QLabel(stackedWidget_6Page1);
        label_pdmarea->setObjectName(QString::fromUtf8("label_pdmarea"));
        label_pdmarea->setEnabled(false);
        label_pdmarea->setGeometry(QRect(200, 0, 1166, 598));
        label_pdmarea->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/DWIN_SET/home.bmp);"));
        label_ceshiniuju = new QLabel(stackedWidget_6Page1);
        label_ceshiniuju->setObjectName(QString::fromUtf8("label_ceshiniuju"));
        label_ceshiniuju->setGeometry(QRect(400, 81, 51, 16));
        label_ceshiniuju->setStyleSheet(QString::fromUtf8("background:transparent;"));
        label_ceshijiaodu = new QLabel(stackedWidget_6Page1);
        label_ceshijiaodu->setObjectName(QString::fromUtf8("label_ceshijiaodu"));
        label_ceshijiaodu->setGeometry(QRect(505, 81, 81, 16));
        label_ceshijiaodu->setStyleSheet(QString::fromUtf8("background:transparent;"));
        pushButton_17 = new QPushButton(stackedWidget_6Page1);
        pushButton_17->setObjectName(QString::fromUtf8("pushButton_17"));
        pushButton_17->setGeometry(QRect(210, 500, 80, 30));
        pushButton_17->setFocusPolicy(Qt::NoFocus);
        pushButton_17->setStyleSheet(QString::fromUtf8("background:transparent;"));
        pushButton_17->setFlat(true);
        pushButton_reset = new QPushButton(stackedWidget_6Page1);
        pushButton_reset->setObjectName(QString::fromUtf8("pushButton_reset"));
        pushButton_reset->setGeometry(QRect(209, 550, 80, 30));
        pushButton_reset->setFocusPolicy(Qt::NoFocus);
        pushButton_reset->setStyleSheet(QString::fromUtf8(""));
        pushButton_reset->setFlat(true);
        label_battery = new QLabel(stackedWidget_6Page1);
        label_battery->setObjectName(QString::fromUtf8("label_battery"));
        label_battery->setGeometry(QRect(1147, 574, 28, 14));
        label_battery->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"border-image: url(:/LCD_CS351/LCD_CS351/logo/battery.png);"));
        label_wifi = new QLabel(stackedWidget_6Page1);
        label_wifi->setObjectName(QString::fromUtf8("label_wifi"));
        label_wifi->setGeometry(QRect(1111, 573, 23, 18));
        label_wifi->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"border-image: url(:/LCD_CS351/LCD_CS351/logo/wifi.png);"));
        label_12 = new QLabel(stackedWidget_6Page1);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(1189, 570, 171, 21));
        label_12->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"color: rgb(51, 153, 255);"));
        stackedWidget_6->addWidget(stackedWidget_6Page1);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        pushButton_18 = new QPushButton(page_4);
        pushButton_18->setObjectName(QString::fromUtf8("pushButton_18"));
        pushButton_18->setGeometry(QRect(0, 520, 74, 80));
        pushButton_18->setFocusPolicy(Qt::NoFocus);
        pushButton_18->setStyleSheet(QString::fromUtf8("background : transparent;\n"
"border-image: url(:/re/go.png);"));
        pushButton_18->setFlat(true);
        label_13 = new QLabel(page_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(0, 0, 1366, 600));
        label_13->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/DWIN_SET/mainlogo.png);"));
        label_14 = new QLabel(page_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(1180, 570, 171, 21));
        label_14->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"color: rgb(248, 248, 255);"));
        label_wifi_2 = new QLabel(page_4);
        label_wifi_2->setObjectName(QString::fromUtf8("label_wifi_2"));
        label_wifi_2->setGeometry(QRect(1103, 560, 41, 31));
        label_wifi_2->setStyleSheet(QString::fromUtf8("background:transparent;"));
        stackedWidget_6->addWidget(page_4);
        label_13->raise();
        pushButton_18->raise();
        label_14->raise();
        label_wifi_2->raise();
        label_black = new QLabel(page);
        label_black->setObjectName(QString::fromUtf8("label_black"));
        label_black->setGeometry(QRect(1310, 620, 58, 15));
        label_black->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        stackedWidget->addWidget(page);
        stackedWidget_6->raise();
        pushButton_16->raise();
        widget_2->raise();
        label_black->raise();
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        widget_3 = new QWidget(page_3);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(0, 0, 1366, 768));
        widget_3->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/DWIN_SET/startt.png);"));
        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        groupBox_4 = new QGroupBox(page_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 0, 1366, 768));
        groupBox_4->setStyleSheet(QString::fromUtf8(""));
        widget_4 = new QWidget(groupBox_4);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(0, 0, 200, 768));
        widget_4->setStyleSheet(QString::fromUtf8("background-color: rgb(51, 153, 255);"));
        pushButton_15 = new QPushButton(widget_4);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));
        pushButton_15->setGeometry(QRect(60, 40, 57, 57));
        pushButton_15->setFocusPolicy(Qt::NoFocus);
        pushButton_15->setStyleSheet(QString::fromUtf8("border-image: url(:/re/back.png);\n"
"background : transparent;"));
        pushButton_15->setFlat(true);
        widget_5 = new QWidget(groupBox_4);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(200, 0, 1166, 768));
        widget_5->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 248, 255);"));
        pushButton_14 = new QPushButton(widget_5);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setGeometry(QRect(670, 120, 129, 145));
        pushButton_14->setFocusPolicy(Qt::NoFocus);
        pushButton_14->setStyleSheet(QString::fromUtf8("border-image: url(:/re/100.png);\n"
"background : transparent;"));
        pushButton_14->setFlat(true);
        pushButton_13 = new QPushButton(widget_5);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(400, 120, 129, 145));
        pushButton_13->setFocusPolicy(Qt::NoFocus);
        pushButton_13->setStyleSheet(QString::fromUtf8("border-image: url(:/re/93.bmp);\n"
"background : transparent;"));
        pushButton_13->setFlat(true);
        pushButton_error = new QPushButton(widget_5);
        pushButton_error->setObjectName(QString::fromUtf8("pushButton_error"));
        pushButton_error->setEnabled(false);
        pushButton_error->setGeometry(QRect(540, 390, 127, 24));
        pushButton_error->setFlat(true);
        pushButton_password = new QPushButton(widget_5);
        pushButton_password->setObjectName(QString::fromUtf8("pushButton_password"));
        pushButton_password->setEnabled(false);
        pushButton_password->setGeometry(QRect(550, 330, 109, 19));
        pushButton_password->setFlat(true);
        pushButton = new QPushButton(widget_5);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(false);
        pushButton->setGeometry(QRect(470, 448, 268, 234));
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/re/num.png);"));
        pushButton->setFlat(true);
        pushButton_3 = new QPushButton(widget_5);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(647, 466, 75, 46));
        pushButton_3->setStyleSheet(QString::fromUtf8("background : transparent;"));
        pushButton_3->setFlat(true);
        pushButton_1 = new QPushButton(widget_5);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setEnabled(true);
        pushButton_1->setGeometry(QRect(487, 466, 75, 46));
        pushButton_1->setStyleSheet(QString::fromUtf8("background : transparent;"));
        pushButton_1->setFlat(true);
        pushButton_2 = new QPushButton(widget_5);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(567, 466, 75, 46));
        pushButton_2->setStyleSheet(QString::fromUtf8("background : transparent;"));
        pushButton_2->setFlat(true);
        pushButton_4 = new QPushButton(widget_5);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setEnabled(true);
        pushButton_4->setGeometry(QRect(487, 517, 75, 46));
        pushButton_4->setStyleSheet(QString::fromUtf8("background : transparent;"));
        pushButton_4->setFlat(true);
        pushButton_5 = new QPushButton(widget_5);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setEnabled(true);
        pushButton_5->setGeometry(QRect(567, 517, 75, 46));
        pushButton_5->setStyleSheet(QString::fromUtf8("background : transparent;"));
        pushButton_5->setFlat(true);
        pushButton_6 = new QPushButton(widget_5);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setEnabled(true);
        pushButton_6->setGeometry(QRect(647, 517, 75, 46));
        pushButton_6->setStyleSheet(QString::fromUtf8("background : transparent;"));
        pushButton_6->setFlat(true);
        pushButton_7 = new QPushButton(widget_5);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setEnabled(true);
        pushButton_7->setGeometry(QRect(487, 568, 75, 46));
        pushButton_7->setStyleSheet(QString::fromUtf8("background : transparent;"));
        pushButton_7->setFlat(true);
        pushButton_8 = new QPushButton(widget_5);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setEnabled(true);
        pushButton_8->setGeometry(QRect(567, 568, 75, 46));
        pushButton_8->setStyleSheet(QString::fromUtf8("background : transparent;"));
        pushButton_8->setFlat(true);
        pushButton_9 = new QPushButton(widget_5);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setEnabled(true);
        pushButton_9->setGeometry(QRect(647, 568, 75, 46));
        pushButton_9->setStyleSheet(QString::fromUtf8("background : transparent;"));
        pushButton_9->setFlat(true);
        pushButton_0 = new QPushButton(widget_5);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        pushButton_0->setEnabled(true);
        pushButton_0->setGeometry(QRect(567, 619, 75, 46));
        pushButton_0->setStyleSheet(QString::fromUtf8("background : transparent;"));
        pushButton_0->setFlat(true);
        pushButton_delete = new QPushButton(widget_5);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));
        pushButton_delete->setEnabled(true);
        pushButton_delete->setGeometry(QRect(647, 619, 75, 46));
        pushButton_delete->setStyleSheet(QString::fromUtf8("background : transparent;"));
        pushButton_delete->setFlat(true);
        stackedWidget->addWidget(page_2);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        stackedWidget_6->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        pushButton_16->setText(QApplication::translate("MainWindow", "Not Ready", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "ABCDEFGHIJKLMN", 0, QApplication::UnicodeUTF8));
        label_tiaomastate->setText(QApplication::translate("MainWindow", "\346\213\247\347\264\247\346\216\247\345\210\266\345\231\250\346\262\241\346\234\211\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
        label_time->setText(QString());
        pushButton_10->setText(QString());
        pushButton_12->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "\345\267\245    \346\256\265\357\274\232", 0, QApplication::UnicodeUTF8));
        label_gongwei->setText(QApplication::translate("MainWindow", "ba0", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "\345\267\245    \344\275\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_gonghao->setText(QApplication::translate("MainWindow", "gonghao", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\347\250\213 \345\272\217 \345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label_pronum->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "\351\242\235    \345\256\232\357\274\232", 0, QApplication::UnicodeUTF8));
        label_lsnum->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "\345\220\210    \346\240\274\357\274\232", 0, QApplication::UnicodeUTF8));
        label_hege->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "\346\235\241\347\240\201\346\250\241\345\274\217\357\274\232", 0, QApplication::UnicodeUTF8));
        label_tiaoma->setText(QApplication::translate("MainWindow", "weihu", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "\346\213\247\347\264\247\346\234\272", 0, QApplication::UnicodeUTF8));
        label_ss1->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        label_ss2->setText(QString());
        label_10->setText(QApplication::translate("MainWindow", "\347\263\273  \347\273\237", 0, QApplication::UnicodeUTF8));
        label_ss3->setText(QString());
        label_11->setText(QApplication::translate("MainWindow", "RFID ", 0, QApplication::UnicodeUTF8));
        label_ss4->setText(QString());
        label_16->setText(QApplication::translate("MainWindow", "\346\213\247\347\264\247\346\250\241\345\274\217\357\274\232", 0, QApplication::UnicodeUTF8));
        label_tighten->setText(QApplication::translate("MainWindow", "Cleco", 0, QApplication::UnicodeUTF8));
        pushButton_shutdown->setText(QString());
        label_18->setText(QApplication::translate("MainWindow", "\350\247\222\345\272\246", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "\346\211\255\347\237\251", 0, QApplication::UnicodeUTF8));
        label_ceshipronum->setText(QString());
        label_pdmarea->setText(QString());
        label_ceshiniuju->setText(QString());
        label_ceshijiaodu->setText(QString());
        pushButton_17->setText(QApplication::translate("MainWindow", "\347\241\256\350\256\244\344\270\200\344\270\252", 0, QApplication::UnicodeUTF8));
        pushButton_reset->setText(QApplication::translate("MainWindow", "\347\241\256\350\256\244\345\205\250\351\203\250", 0, QApplication::UnicodeUTF8));
        label_battery->setText(QString());
        label_wifi->setText(QString());
        label_12->setText(QString());
        pushButton_18->setText(QString());
        label_13->setText(QString());
        label_14->setText(QString());
        label_wifi_2->setText(QString());
        label_black->setText(QString());
        groupBox_4->setTitle(QString());
        pushButton_15->setText(QString());
        pushButton_14->setText(QString());
        pushButton_13->setText(QString());
        pushButton_error->setText(QString());
        pushButton_password->setText(QString());
        pushButton->setText(QString());
        pushButton_3->setText(QString());
        pushButton_1->setText(QString());
        pushButton_2->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
        pushButton_9->setText(QString());
        pushButton_0->setText(QString());
        pushButton_delete->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
