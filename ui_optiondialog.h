/********************************************************************************
** Form generated from reading UI file 'optiondialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONDIALOG_H
#define UI_OPTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_OptionDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_bx1name;
    QLineEdit *lineEdit_bx1code;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *OptionDialog)
    {
        if (OptionDialog->objectName().isEmpty())
            OptionDialog->setObjectName(QString::fromUtf8("OptionDialog"));
        OptionDialog->resize(332, 212);
        OptionDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 248, 255);"));
        label = new QLabel(OptionDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 40, 101, 31));
        label->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        label_2 = new QLabel(OptionDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(186, 40, 101, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        label_3 = new QLabel(OptionDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(155, 100, 21, 31));
        label_3->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        lineEdit_bx1name = new QLineEdit(OptionDialog);
        lineEdit_bx1name->setObjectName(QString::fromUtf8("lineEdit_bx1name"));
        lineEdit_bx1name->setGeometry(QRect(30, 100, 111, 35));
        lineEdit_bx1name->setFocusPolicy(Qt::ClickFocus);
        lineEdit_bx1name->setStyleSheet(QString::fromUtf8("border-width:1px; \n"
"border-style:solid; \n"
"border-color:rgb(51, 153, 255); \n"
"margin-top: 0ex;\n"
"font: 14pt \"\351\273\221\344\275\223\";"));
        lineEdit_bx1code = new QLineEdit(OptionDialog);
        lineEdit_bx1code->setObjectName(QString::fromUtf8("lineEdit_bx1code"));
        lineEdit_bx1code->setGeometry(QRect(180, 100, 111, 35));
        lineEdit_bx1code->setFocusPolicy(Qt::ClickFocus);
        lineEdit_bx1code->setStyleSheet(QString::fromUtf8("border-width:1px; \n"
"border-style:solid; \n"
"border-color:rgb(51, 153, 255); \n"
"margin-top: 0ex;\n"
"font: 14pt \"Arial\";"));
        pushButton = new QPushButton(OptionDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(270, 150, 53, 53));
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/35_all/67.bmp);\n"
"font: 14pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));
        pushButton->setFlat(true);
        pushButton_2 = new QPushButton(OptionDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(302, 0, 31, 31));
        pushButton_2->setFocusPolicy(Qt::NoFocus);
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/35_all/cha.bmp);"));
        pushButton_2->setFlat(true);

        retranslateUi(OptionDialog);

        QMetaObject::connectSlotsByName(OptionDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionDialog)
    {
        OptionDialog->setWindowTitle(QApplication::translate("OptionDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("OptionDialog", "\351\200\211\350\243\205\344\273\266\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("OptionDialog", "\351\200\211\350\243\205\344\273\266\344\273\243\347\240\201", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("OptionDialog", "\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("OptionDialog", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class OptionDialog: public Ui_OptionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONDIALOG_H
