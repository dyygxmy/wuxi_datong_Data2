/********************************************************************************
** Form generated from reading UI file 'save.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVE_H
#define UI_SAVE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Save
{
public:
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *Save)
    {
        if (Save->objectName().isEmpty())
            Save->setObjectName(QString::fromUtf8("Save"));
        Save->resize(315, 176);
        groupBox = new QGroupBox(Save);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 20, 315, 156));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	background-color: rgb(248, 248, 255);\n"
"	color: rgb(248, 248, 255);\n"
"    font: 14pt \"\351\273\221\344\275\223\";\n"
"    margin-top: 0ex;\n"
"    border-width:3px;  \n"
"    border-style:solid;\n"
"    border-color: rgb(51, 153, 255);  \n"
"}"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 110, 80, 26));
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/35_all/67.bmp);\n"
"background:transparent;\n"
"font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(190, 110, 80, 26));
        pushButton_2->setFocusPolicy(Qt::NoFocus);
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/35_all/67.bmp);\n"
"background:transparent;\n"
"font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(21, 20, 65, 54));
        label_2->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/logo/warn.png);"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(100, 47, 191, 21));
        label_3->setStyleSheet(QString::fromUtf8("font: 14pt \"\351\273\221\344\275\223\";"));
        label = new QLabel(Save);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 315, 25));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(51, 153, 255); \n"
"font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(248, 248, 255);"));
        pushButton_cancel = new QPushButton(Save);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(285, 0, 31, 25));
        pushButton_cancel->setFocusPolicy(Qt::NoFocus);
        pushButton_cancel->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/35_all/cha.bmp);\n"
"background:transparent;"));
        pushButton_cancel->setAutoDefault(false);
        pushButton_cancel->setFlat(true);

        retranslateUi(Save);

        QMetaObject::connectSlotsByName(Save);
    } // setupUi

    void retranslateUi(QDialog *Save)
    {
        Save->setWindowTitle(QApplication::translate("Save", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        pushButton->setText(QApplication::translate("Save", "\346\230\257", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Save", "\345\220\246", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        label_3->setText(QApplication::translate("Save", "  \344\277\235\345\255\230\345\217\202\346\225\260\350\256\276\347\275\256\357\274\237", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Save", "  Dat@2", 0, QApplication::UnicodeUTF8));
        pushButton_cancel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Save: public Ui_Save {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVE_H
