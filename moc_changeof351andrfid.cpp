/****************************************************************************
** Meta object code from reading C++ file 'changeof351andrfid.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "changeof351andrfid.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'changeof351andrfid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Changeof351AndRfid[] = {

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
      23,   20,   19,   19, 0x05,
      55,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      75,   19,   19,   19, 0x0a,
      85,   19,   19,   19, 0x0a,
      98,   19,   19,   19, 0x0a,
     111,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Changeof351AndRfid[] = {
    "Changeof351AndRfid\0\0,,\0"
    "serialCom(QString,bool,QString)\0"
    "sendSerial(QString)\0comInit()\0"
    "receivemss()\0newConnect()\0slot_read_com()\0"
};

void Changeof351AndRfid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Changeof351AndRfid *_t = static_cast<Changeof351AndRfid *>(_o);
        switch (_id) {
        case 0: _t->serialCom((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->sendSerial((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->comInit(); break;
        case 3: _t->receivemss(); break;
        case 4: _t->newConnect(); break;
        case 5: _t->slot_read_com(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Changeof351AndRfid::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Changeof351AndRfid::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Changeof351AndRfid,
      qt_meta_data_Changeof351AndRfid, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Changeof351AndRfid::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Changeof351AndRfid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Changeof351AndRfid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Changeof351AndRfid))
        return static_cast<void*>(const_cast< Changeof351AndRfid*>(this));
    return QObject::qt_metacast(_clname);
}

int Changeof351AndRfid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Changeof351AndRfid::serialCom(QString _t1, bool _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Changeof351AndRfid::sendSerial(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
