/****************************************************************************
** Meta object code from reading C++ file 'web.h'
**
** Created: Thu Oct 29 17:29:52 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "web.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'web.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Web[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x0a,
      18,    4,    4,    4, 0x0a,
      44,   36,    4,    4, 0x0a,
      68,   36,    4,    4, 0x0a,
     101,    4,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Web[] = {
    "Web\0\0mywebtimer()\0onNewConnection()\0"
    "message\0processMessage(QString)\0"
    "processBinaryMessage(QByteArray)\0"
    "socketDisconnected()\0"
};

void Web::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Web *_t = static_cast<Web *>(_o);
        switch (_id) {
        case 0: _t->mywebtimer(); break;
        case 1: _t->onNewConnection(); break;
        case 2: _t->processMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->processBinaryMessage((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->socketDisconnected(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Web::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Web::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Web,
      qt_meta_data_Web, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Web::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Web::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Web::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Web))
        return static_cast<void*>(const_cast< Web*>(this));
    return QObject::qt_metacast(_clname);
}

int Web::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
