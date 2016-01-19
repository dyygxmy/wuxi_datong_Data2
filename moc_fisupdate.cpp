/****************************************************************************
** Meta object code from reading C++ file 'fisupdate.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fisupdate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fisupdate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FisUpdate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      28,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   10,   10,   10, 0x0a,
      59,   10,   10,   10, 0x0a,
      75,   10,   10,   10, 0x0a,
      98,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FisUpdate[] = {
    "FisUpdate\0\0time_error(bool)\0"
    "sendTime(QString)\0myfistimer()\0"
    "fisupdateFunc()\0update_column(QString)\0"
    "QueryTime()\0"
};

void FisUpdate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FisUpdate *_t = static_cast<FisUpdate *>(_o);
        switch (_id) {
        case 0: _t->time_error((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sendTime((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->myfistimer(); break;
        case 3: _t->fisupdateFunc(); break;
        case 4: _t->update_column((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->QueryTime(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FisUpdate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FisUpdate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FisUpdate,
      qt_meta_data_FisUpdate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FisUpdate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FisUpdate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FisUpdate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FisUpdate))
        return static_cast<void*>(const_cast< FisUpdate*>(this));
    return QObject::qt_metacast(_clname);
}

int FisUpdate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void FisUpdate::time_error(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FisUpdate::sendTime(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
