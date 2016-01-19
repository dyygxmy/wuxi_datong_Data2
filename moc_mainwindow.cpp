/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      48,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      18,   11,   11,   11, 0x05,
      25,   11,   11,   11, 0x05,
      42,   39,   11,   11, 0x05,
     130,   88,   11,   11, 0x05,
     164,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     182,   39,   11,   11, 0x0a,
     228,   39,   11,   11, 0x0a,
     263,   11,   11,   11, 0x0a,
     278,   11,   11,   11, 0x0a,
     285,   11,   11,   11, 0x0a,
     300,   11,   11,   11, 0x0a,
     315,   11,   11,   11, 0x0a,
     337,   11,   11,   11, 0x0a,
     356,   11,   11,   11, 0x0a,
     375,   11,   11,   11, 0x0a,
     393,   11,   11,   11, 0x0a,
     405,   11,   11,   11, 0x0a,
     426,   11,   11,   11, 0x0a,
     443,   11,   11,   11, 0x0a,
     456,   11,   11,   11, 0x0a,
     483,   11,   11,   11, 0x0a,
     509,   11,   11,   11, 0x0a,
     535,   11,   11,   11, 0x0a,
     561,   11,   11,   11, 0x0a,
     587,   11,   11,   11, 0x0a,
     613,   11,   11,   11, 0x0a,
     639,   11,   11,   11, 0x0a,
     665,   11,   11,   11, 0x0a,
     691,   11,   11,   11, 0x0a,
     717,   11,   11,   11, 0x0a,
     748,   11,   11,   11, 0x0a,
     775,   11,   11,   11, 0x0a,
     802,   11,   11,   11, 0x0a,
     829,   11,   11,   11, 0x0a,
     855,   11,   11,   11, 0x0a,
     866,   11,   11,   11, 0x0a,
     879,   11,   11,   11, 0x0a,
     892,   11,   11,   11, 0x0a,
     919,   11,   11,   11, 0x0a,
     949,   11,   11,   11, 0x0a,
     973,   11,   11,   11, 0x0a,
     993,   11,   11,   11, 0x0a,
    1011,   11,   11,   11, 0x0a,
    1025,   11,   11,   11, 0x0a,
    1035,   11,   11,   11, 0x08,
    1062,   11,   11,   11, 0x08,
    1085,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0clo()\0clo1()\0sendoperate()\0"
    ",,\0sendfromsecondthread(QString,QString,QString)\0"
    "isoption,whicharis,whichpro,whichoptionis\0"
    "sendConfigureAll(int,int,int,int)\0"
    "sendnexo(QString)\0"
    "fromsecondthreaddata(QString,QString,QString)\0"
    "getSerialNum(QString,bool,QString)\0"
    "connectMysql()\0init()\0wifishow(bool)\0"
    "datashow(bool)\0batteryshow1(QString)\0"
    "batteryshow2(bool)\0time_warning(bool)\0"
    "ReceGunNotReady()\0battery15()\0"
    "TightenIsReady(bool)\0receiveOperate()\0"
    "timerDelay()\0on_pushButton_12_clicked()\0"
    "on_pushButton_1_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_3_clicked()\0"
    "on_pushButton_4_clicked()\0"
    "on_pushButton_5_clicked()\0"
    "on_pushButton_6_clicked()\0"
    "on_pushButton_7_clicked()\0"
    "on_pushButton_8_clicked()\0"
    "on_pushButton_9_clicked()\0"
    "on_pushButton_delete_clicked()\0"
    "on_pushButton_13_clicked()\0"
    "on_pushButton_14_clicked()\0"
    "on_pushButton_15_clicked()\0"
    "on_pushButton_0_clicked()\0ShowTime()\0"
    "UpdateSlot()\0PdmFlicker()\0"
    "on_pushButton_18_clicked()\0"
    "on_pushButton_reset_clicked()\0"
    "receiveCloseInput(bool)\0configwarning(bool)\0"
    "taotong_main(int)\0shutdown(int)\0"
    "clocked()\0on_pushButton_17_clicked()\0"
    "signal_mysqlerror_do()\0"
    "on_pushButton_shutdown_clicked()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->clo(); break;
        case 1: _t->clo1(); break;
        case 2: _t->sendoperate(); break;
        case 3: _t->sendfromsecondthread((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 4: _t->sendConfigureAll((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 5: _t->sendnexo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->fromsecondthreaddata((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 7: _t->getSerialNum((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 8: _t->connectMysql(); break;
        case 9: _t->init(); break;
        case 10: _t->wifishow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->datashow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->batteryshow1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->batteryshow2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->time_warning((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->ReceGunNotReady(); break;
        case 16: _t->battery15(); break;
        case 17: _t->TightenIsReady((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->receiveOperate(); break;
        case 19: _t->timerDelay(); break;
        case 20: _t->on_pushButton_12_clicked(); break;
        case 21: _t->on_pushButton_1_clicked(); break;
        case 22: _t->on_pushButton_2_clicked(); break;
        case 23: _t->on_pushButton_3_clicked(); break;
        case 24: _t->on_pushButton_4_clicked(); break;
        case 25: _t->on_pushButton_5_clicked(); break;
        case 26: _t->on_pushButton_6_clicked(); break;
        case 27: _t->on_pushButton_7_clicked(); break;
        case 28: _t->on_pushButton_8_clicked(); break;
        case 29: _t->on_pushButton_9_clicked(); break;
        case 30: _t->on_pushButton_delete_clicked(); break;
        case 31: _t->on_pushButton_13_clicked(); break;
        case 32: _t->on_pushButton_14_clicked(); break;
        case 33: _t->on_pushButton_15_clicked(); break;
        case 34: _t->on_pushButton_0_clicked(); break;
        case 35: _t->ShowTime(); break;
        case 36: _t->UpdateSlot(); break;
        case 37: _t->PdmFlicker(); break;
        case 38: _t->on_pushButton_18_clicked(); break;
        case 39: _t->on_pushButton_reset_clicked(); break;
        case 40: _t->receiveCloseInput((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 41: _t->configwarning((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 42: _t->taotong_main((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: _t->shutdown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 44: _t->clocked(); break;
        case 45: _t->on_pushButton_17_clicked(); break;
        case 46: _t->signal_mysqlerror_do(); break;
        case 47: _t->on_pushButton_shutdown_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 48)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 48;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::clo()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::clo1()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainWindow::sendoperate()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MainWindow::sendfromsecondthread(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::sendConfigureAll(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::sendnexo(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
