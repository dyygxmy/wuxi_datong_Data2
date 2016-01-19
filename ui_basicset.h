/********************************************************************************
** Form generated from reading UI file 'basicset.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASICSET_H
#define UI_BASICSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BasicSet
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_cs351Ip;
    QLineEdit *lineEdit_PortA;
    QLineEdit *lineEdit_PortB;
    QWidget *page_3;
    QLabel *label_9;
    QLabel *label_24;
    QLabel *label_25;
    QLineEdit *lineEdit_RfidPort;
    QLineEdit *lineEdit_RfidIp;
    QLabel *label_26;
    QWidget *page_4;
    QLabel *label_10;
    QLabel *label_21;
    QLineEdit *lineEdit_DataServerIp;
    QLabel *label_22;
    QLabel *label_23;
    QLineEdit *lineEdit_CurveServerIp;
    QLineEdit *lineEdit_AndonServerIp;
    QLabel *label_29;
    QWidget *page_2;
    QLabel *label_6;
    QLineEdit *lineEdit_BarcodeGun;
    QLabel *label_27;
    QLabel *label_28;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *pushButton_37;
    QPushButton *pushButton_38;

    void setupUi(QDialog *BasicSet)
    {
        if (BasicSet->objectName().isEmpty())
            BasicSet->setObjectName(QString::fromUtf8("BasicSet"));
        BasicSet->resize(538, 341);
        stackedWidget = new QStackedWidget(BasicSet);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 538, 341));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 248, 255);"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 149, 341));
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/logo/cs351set.png);"));
        label_2 = new QLabel(page);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(220, 51, 251, 41));
        label_2->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        label_3 = new QLabel(page);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(221, 111, 31, 41));
        label_3->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        label_4 = new QLabel(page);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(181, 169, 71, 41));
        label_4->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        label_5 = new QLabel(page);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(181, 227, 71, 41));
        label_5->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        lineEdit_cs351Ip = new QLineEdit(page);
        lineEdit_cs351Ip->setObjectName(QString::fromUtf8("lineEdit_cs351Ip"));
        lineEdit_cs351Ip->setGeometry(QRect(260, 114, 181, 35));
        lineEdit_cs351Ip->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";\n"
"border-width:1px; \n"
"border-style:solid; \n"
"border-color:rgb(51, 153, 255); "));
        lineEdit_cs351Ip->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_PortA = new QLineEdit(page);
        lineEdit_PortA->setObjectName(QString::fromUtf8("lineEdit_PortA"));
        lineEdit_PortA->setGeometry(QRect(260, 173, 111, 34));
        lineEdit_PortA->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";\n"
"border-width:1px; \n"
"border-style:solid; \n"
"border-color:rgb(51, 153, 255); "));
        lineEdit_PortA->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_PortB = new QLineEdit(page);
        lineEdit_PortB->setObjectName(QString::fromUtf8("lineEdit_PortB"));
        lineEdit_PortB->setGeometry(QRect(260, 231, 111, 34));
        lineEdit_PortB->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";\n"
"border-width:1px; \n"
"border-style:solid; \n"
"border-color:rgb(51, 153, 255); "));
        lineEdit_PortB->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        stackedWidget->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        label_9 = new QLabel(page_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(0, 0, 149, 341));
        label_9->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/logo/RFID set.png);"));
        label_24 = new QLabel(page_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(190, 174, 81, 41));
        label_24->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        label_25 = new QLabel(page_3);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(292, 56, 81, 41));
        label_25->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        lineEdit_RfidPort = new QLineEdit(page_3);
        lineEdit_RfidPort->setObjectName(QString::fromUtf8("lineEdit_RfidPort"));
        lineEdit_RfidPort->setGeometry(QRect(279, 178, 111, 34));
        lineEdit_RfidPort->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";\n"
"border-width:1px; \n"
"border-style:solid; \n"
"border-color:rgb(51, 153, 255); "));
        lineEdit_RfidPort->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_RfidIp = new QLineEdit(page_3);
        lineEdit_RfidIp->setObjectName(QString::fromUtf8("lineEdit_RfidIp"));
        lineEdit_RfidIp->setGeometry(QRect(279, 119, 181, 35));
        lineEdit_RfidIp->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";\n"
"border-width:1px; \n"
"border-style:solid; \n"
"border-color:rgb(51, 153, 255); "));
        lineEdit_RfidIp->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_26 = new QLabel(page_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(240, 116, 31, 41));
        label_26->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        label_10 = new QLabel(page_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(0, 0, 149, 341));
        label_10->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/logo/serve set.png);"));
        label_21 = new QLabel(page_4);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(191, 166, 111, 41));
        label_21->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        lineEdit_DataServerIp = new QLineEdit(page_4);
        lineEdit_DataServerIp->setObjectName(QString::fromUtf8("lineEdit_DataServerIp"));
        lineEdit_DataServerIp->setGeometry(QRect(301, 111, 161, 35));
        lineEdit_DataServerIp->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";\n"
"border-width:1px; \n"
"border-style:solid; \n"
"border-color:rgb(51, 153, 255); "));
        lineEdit_DataServerIp->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_22 = new QLabel(page_4);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(191, 108, 106, 41));
        label_22->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        label_23 = new QLabel(page_4);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(283, 48, 101, 41));
        label_23->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        lineEdit_CurveServerIp = new QLineEdit(page_4);
        lineEdit_CurveServerIp->setObjectName(QString::fromUtf8("lineEdit_CurveServerIp"));
        lineEdit_CurveServerIp->setGeometry(QRect(301, 170, 161, 34));
        lineEdit_CurveServerIp->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";\n"
"border-width:1px; \n"
"border-style:solid; \n"
"border-color:rgb(51, 153, 255); "));
        lineEdit_CurveServerIp->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_AndonServerIp = new QLineEdit(page_4);
        lineEdit_AndonServerIp->setObjectName(QString::fromUtf8("lineEdit_AndonServerIp"));
        lineEdit_AndonServerIp->setGeometry(QRect(301, 230, 161, 34));
        lineEdit_AndonServerIp->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";\n"
"border-width:1px; \n"
"border-style:solid; \n"
"border-color:rgb(51, 153, 255); "));
        lineEdit_AndonServerIp->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_29 = new QLabel(page_4);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(171, 226, 123, 41));
        label_29->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        stackedWidget->addWidget(page_4);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label_6 = new QLabel(page_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 0, 149, 341));
        label_6->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/logo/barcode_set.png);"));
        lineEdit_BarcodeGun = new QLineEdit(page_2);
        lineEdit_BarcodeGun->setObjectName(QString::fromUtf8("lineEdit_BarcodeGun"));
        lineEdit_BarcodeGun->setGeometry(QRect(271, 127, 161, 35));
        lineEdit_BarcodeGun->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";\n"
"border-width:1px; \n"
"border-style:solid; \n"
"border-color:rgb(51, 153, 255); "));
        lineEdit_BarcodeGun->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_27 = new QLabel(page_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(260, 60, 141, 41));
        label_27->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        label_28 = new QLabel(page_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(192, 124, 71, 41));
        label_28->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        layoutWidget = new QWidget(page_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(200, 200, 241, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(layoutWidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setFocusPolicy(Qt::NoFocus);
        radioButton->setStyleSheet(QString::fromUtf8("QRadioButton{\n"
"   font: 14pt \"\351\273\221\344\275\223\";\n"
"   spacing: 10 \n"
"}  \n"
"\n"
"QRadioButton::indicator { \n"
"   width: 25px;\n"
"   height: 25px;\n"
"   image: url(:/LCD_CS351/LCD_CS351/logo/Radio.png);\n"
"}\n"
"\n"
"QRadioButton::indicator:checked { \n"
"image: url(:/LCD_CS351/LCD_CS351/logo/Radio_check.png);\n"
"}"));

        horizontalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(layoutWidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setFocusPolicy(Qt::NoFocus);
        radioButton_2->setStyleSheet(QString::fromUtf8("QRadioButton{\n"
"   font: 14pt \"\351\273\221\344\275\223\";\n"
"   spacing: 10 \n"
"}  \n"
"\n"
"QRadioButton::indicator { \n"
"   width: 25px;\n"
"   height: 25px;\n"
"   image: url(:/LCD_CS351/LCD_CS351/logo/Radio.png);\n"
"}\n"
"\n"
"QRadioButton::indicator:checked { \n"
"image: url(:/LCD_CS351/LCD_CS351/logo/Radio_check.png);\n"
"}"));

        horizontalLayout->addWidget(radioButton_2);

        stackedWidget->addWidget(page_2);
        pushButton_37 = new QPushButton(BasicSet);
        pushButton_37->setObjectName(QString::fromUtf8("pushButton_37"));
        pushButton_37->setGeometry(QRect(500, 0, 38, 38));
        pushButton_37->setFocusPolicy(Qt::NoFocus);
        pushButton_37->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/35_all/cha.bmp);"));
        pushButton_37->setFlat(true);
        pushButton_38 = new QPushButton(BasicSet);
        pushButton_38->setObjectName(QString::fromUtf8("pushButton_38"));
        pushButton_38->setGeometry(QRect(482, 295, 51, 41));
        pushButton_38->setFocusPolicy(Qt::NoFocus);
        pushButton_38->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/35_all/67.bmp);\n"
"font: 14pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));
        pushButton_38->setFlat(true);
        stackedWidget->raise();
        pushButton_38->raise();
        pushButton_37->raise();

        retranslateUi(BasicSet);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(BasicSet);
    } // setupUi

    void retranslateUi(QDialog *BasicSet)
    {
        BasicSet->setWindowTitle(QApplication::translate("BasicSet", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_2->setText(QApplication::translate("BasicSet", "BOSCH Rexroth CS351\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("BasicSet", "IP\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("BasicSet", "\347\253\257\345\217\243 A\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("BasicSet", "\347\253\257\345\217\243 B\357\274\232", 0, QApplication::UnicodeUTF8));
        label_9->setText(QString());
        label_24->setText(QApplication::translate("BasicSet", "\347\253\257\345\217\243\345\217\267 \357\274\232", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("BasicSet", "RFID\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("BasicSet", "IP\357\274\232", 0, QApplication::UnicodeUTF8));
        label_10->setText(QString());
        label_21->setText(QApplication::translate("BasicSet", "\346\233\262\347\272\277\346\234\215\345\212\241\345\231\250\357\274\232", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("BasicSet", "\346\225\260\346\215\256\346\234\215\345\212\241\345\231\250\357\274\232", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("BasicSet", "\346\234\215\345\212\241\345\231\250\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("BasicSet", "Andon\346\234\215\345\212\241\345\231\250\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QString());
        label_27->setText(QApplication::translate("BasicSet", "   \346\235\241\347\240\201\346\236\252\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("BasicSet", "\346\263\242\347\211\271\347\216\207\357\274\232", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("BasicSet", "\346\234\211\347\272\277", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("BasicSet", "\346\227\240\347\272\277", 0, QApplication::UnicodeUTF8));
        pushButton_37->setText(QString());
        pushButton_38->setText(QApplication::translate("BasicSet", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BasicSet: public Ui_BasicSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASICSET_H
