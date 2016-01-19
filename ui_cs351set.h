/********************************************************************************
** Form generated from reading UI file 'cs351set.ui'
**
** Created: Tue Jun 23 09:01:22 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CS351SET_H
#define UI_CS351SET_H

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
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CS351set
{
public:
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *Cs351_edit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *PortA_edit;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *PortB_edit;

    void setupUi(QDialog *CS351set)
    {
        if (CS351set->objectName().isEmpty())
            CS351set->setObjectName(QString::fromUtf8("CS351set"));
        CS351set->resize(418, 367);
        CS351set->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);"));
        pushButton = new QPushButton(CS351set);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(240, 270, 75, 23));
        layoutWidget = new QWidget(CS351set);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 90, 225, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\346\245\267\344\275\223\";"));

        horizontalLayout->addWidget(label);

        Cs351_edit = new QLineEdit(layoutWidget);
        Cs351_edit->setObjectName(QString::fromUtf8("Cs351_edit"));
        Cs351_edit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(Cs351_edit);

        layoutWidget1 = new QWidget(CS351set);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(70, 150, 225, 26));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\346\245\267\344\275\223\";"));

        horizontalLayout_2->addWidget(label_2);

        PortA_edit = new QLineEdit(layoutWidget1);
        PortA_edit->setObjectName(QString::fromUtf8("PortA_edit"));
        PortA_edit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(PortA_edit);

        layoutWidget2 = new QWidget(CS351set);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(70, 200, 225, 26));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: 75 18pt \"\346\245\267\344\275\223\";"));

        horizontalLayout_3->addWidget(label_3);

        PortB_edit = new QLineEdit(layoutWidget2);
        PortB_edit->setObjectName(QString::fromUtf8("PortB_edit"));
        PortB_edit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(PortB_edit);


        retranslateUi(CS351set);

        QMetaObject::connectSlotsByName(CS351set);
    } // setupUi

    void retranslateUi(QDialog *CS351set)
    {
        CS351set->setWindowTitle(QApplication::translate("CS351set", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("CS351set", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CS351set", "CS351IP", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CS351set", "\347\253\257 \345\217\243 A", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CS351set", "\347\253\257 \345\217\243 B", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CS351set: public Ui_CS351set {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CS351SET_H
