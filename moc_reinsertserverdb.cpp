/****************************************************************************
** Meta object code from reading C++ file 'reinsertserverdb.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "reinsertserverdb.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reinsertserverdb.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ReInsertServerDb[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      35,   17,   17,   17, 0x0a,
      50,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ReInsertServerDb[] = {
    "ReInsertServerDb\0\0reinsert_start()\0"
    "timer_insert()\0printDead()\0"
};

void ReInsertServerDb::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReInsertServerDb *_t = static_cast<ReInsertServerDb *>(_o);
        switch (_id) {
        case 0: _t->reinsert_start(); break;
        case 1: _t->timer_insert(); break;
        case 2: _t->printDead(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ReInsertServerDb::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ReInsertServerDb::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ReInsertServerDb,
      qt_meta_data_ReInsertServerDb, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReInsertServerDb::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReInsertServerDb::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReInsertServerDb::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReInsertServerDb))
        return static_cast<void*>(const_cast< ReInsertServerDb*>(this));
    return QObject::qt_metacast(_clname);
}

int ReInsertServerDb::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
