/****************************************************************************
** Meta object code from reading C++ file 'taotong.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "taotong.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'taotong.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TaoTong[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      26,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,    8,    8,    8, 0x0a,
      57,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TaoTong[] = {
    "TaoTong\0\0taotong_num(int)\0"
    "sendbattery(QString)\0T_start()\0"
    "taotong_timer()\0"
};

void TaoTong::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TaoTong *_t = static_cast<TaoTong *>(_o);
        switch (_id) {
        case 0: _t->taotong_num((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sendbattery((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->T_start(); break;
        case 3: _t->taotong_timer(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TaoTong::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TaoTong::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TaoTong,
      qt_meta_data_TaoTong, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TaoTong::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TaoTong::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TaoTong::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TaoTong))
        return static_cast<void*>(const_cast< TaoTong*>(this));
    return QObject::qt_metacast(_clname);
}

int TaoTong::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TaoTong::taotong_num(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TaoTong::sendbattery(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
