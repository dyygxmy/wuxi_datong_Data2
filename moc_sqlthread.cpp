/****************************************************************************
** Meta object code from reading C++ file 'sqlthread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sqlthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sqlthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SqlThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   10,   10,   10, 0x0a,
      39,   10,   10,   10, 0x0a,
      51,   10,   10,   10, 0x0a,
      62,   10,   10,   10, 0x0a,
      86,   82,   10,   10, 0x0a,
     126,  123,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SqlThread[] = {
    "SqlThread\0\0send_mysqlerror()\0sqlinit()\0"
    "mysqlopen()\0sqlclose()\0sqlinsert(QString*)\0"
    ",,,\0receiveConfigureAll(int,int,int,int)\0"
    ",,\0configOne(QString,QString,QString)\0"
};

void SqlThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SqlThread *_t = static_cast<SqlThread *>(_o);
        switch (_id) {
        case 0: _t->send_mysqlerror(); break;
        case 1: _t->sqlinit(); break;
        case 2: _t->mysqlopen(); break;
        case 3: _t->sqlclose(); break;
        case 4: _t->sqlinsert((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 5: _t->receiveConfigureAll((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 6: _t->configOne((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SqlThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SqlThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SqlThread,
      qt_meta_data_SqlThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SqlThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SqlThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SqlThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SqlThread))
        return static_cast<void*>(const_cast< SqlThread*>(this));
    return QObject::qt_metacast(_clname);
}

int SqlThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void SqlThread::send_mysqlerror()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
