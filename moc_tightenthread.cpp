/****************************************************************************
** Meta object code from reading C++ file 'tightenthread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tightenthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tightenthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TightenThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      36,   14,   14,   14, 0x05,
      62,   59,   14,   14, 0x05,
     103,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     132,   14,   14,   14, 0x0a,
     147,   14,   14,   14, 0x0a,
     163,   14,   14,   14, 0x0a,
     185,  181,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TightenThread[] = {
    "TightenThread\0\0IsTigntenReady(bool)\0"
    "ReconnectSendOperate()\0,,\0"
    "send_mainwindow(QString,QString,QString)\0"
    "sendfromworkthread(QString*)\0"
    "tightenStart()\0slot_read_com()\0"
    "sendReadOperate()\0buf\0readGWKResult(QString)\0"
};

void TightenThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TightenThread *_t = static_cast<TightenThread *>(_o);
        switch (_id) {
        case 0: _t->IsTigntenReady((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->ReconnectSendOperate(); break;
        case 2: _t->send_mainwindow((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: _t->sendfromworkthread((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 4: _t->tightenStart(); break;
        case 5: _t->slot_read_com(); break;
        case 6: _t->sendReadOperate(); break;
        case 7: _t->readGWKResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TightenThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TightenThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TightenThread,
      qt_meta_data_TightenThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TightenThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TightenThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TightenThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TightenThread))
        return static_cast<void*>(const_cast< TightenThread*>(this));
    return QObject::qt_metacast(_clname);
}

int TightenThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void TightenThread::IsTigntenReady(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TightenThread::ReconnectSendOperate()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void TightenThread::send_mainwindow(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TightenThread::sendfromworkthread(QString * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
