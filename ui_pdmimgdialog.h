/********************************************************************************
** Form generated from reading UI file 'pdmimgdialog.ui'
**
** Created: Tue Jun 30 12:58:29 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDMIMGDIALOG_H
#define UI_PDMIMGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PdmImgDialog
{
public:
    QWidget *widget;
    QPushButton *pdmenterbutton;
    QPushButton *pdmenterbutton_2;
    QTableWidget *tableWidgetPicList;

    void setupUi(QDialog *PdmImgDialog)
    {
        if (PdmImgDialog->objectName().isEmpty())
            PdmImgDialog->setObjectName(QString::fromUtf8("PdmImgDialog"));
        PdmImgDialog->resize(1075, 687);
        PdmImgDialog->setStyleSheet(QString::fromUtf8(""));
        widget = new QWidget(PdmImgDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 1075, 687));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 248, 255);"));
        pdmenterbutton = new QPushButton(widget);
        pdmenterbutton->setObjectName(QString::fromUtf8("pdmenterbutton"));
        pdmenterbutton->setGeometry(QRect(987, 630, 54, 54));
        pdmenterbutton->setFocusPolicy(Qt::NoFocus);
        pdmenterbutton->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/35_all/67.bmp);\n"
"color: rgb(248, 248, 255);\n"
"font: 14pt \"\351\273\221\344\275\223\";"));
        pdmenterbutton->setAutoDefault(false);
        pdmenterbutton->setDefault(false);
        pdmenterbutton->setFlat(true);
        pdmenterbutton_2 = new QPushButton(widget);
        pdmenterbutton_2->setObjectName(QString::fromUtf8("pdmenterbutton_2"));
        pdmenterbutton_2->setGeometry(QRect(867, 630, 54, 54));
        pdmenterbutton_2->setFocusPolicy(Qt::NoFocus);
        pdmenterbutton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/LCD_CS351/LCD_CS351/logo/cancel.bmp);"));
        tableWidgetPicList = new QTableWidget(widget);
        tableWidgetPicList->setObjectName(QString::fromUtf8("tableWidgetPicList"));
        tableWidgetPicList->setGeometry(QRect(0, 0, 1075, 621));
        tableWidgetPicList->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 248, 255);"));
        tableWidgetPicList->setFrameShape(QFrame::StyledPanel);
        tableWidgetPicList->setFrameShadow(QFrame::Plain);
        tableWidgetPicList->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidgetPicList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetPicList->setSelectionMode(QAbstractItemView::SingleSelection);

        retranslateUi(PdmImgDialog);

        QMetaObject::connectSlotsByName(PdmImgDialog);
    } // setupUi

    void retranslateUi(QDialog *PdmImgDialog)
    {
        PdmImgDialog->setWindowTitle(QApplication::translate("PdmImgDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pdmenterbutton->setText(QApplication::translate("PdmImgDialog", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pdmenterbutton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PdmImgDialog: public Ui_PdmImgDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDMIMGDIALOG_H
