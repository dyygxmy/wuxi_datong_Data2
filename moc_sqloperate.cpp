/****************************************************************************
** Meta object code from reading C++ file 'sqloperate.h'
**
** Created: Thu Oct 29 17:29:54 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sqloperate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sqloperate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SqlOperate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,   11,   11,   11, 0x0a,
      44,   11,   11,   11, 0x0a,
      56,   11,   11,   11, 0x0a,
      67,   11,   11,   11, 0x0a,
      77,   11,   11,   11, 0x0a,
      92,   11,   11,   11, 0x0a,
     159,  117,   11,   11, 0x0a,
     196,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SqlOperate[] = {
    "SqlOperate\0\0sendTime(QString)\0"
    "datasqlopen()\0mysqlopen()\0sqlclose()\0"
    "sqlInit()\0curvesqlopen()\0"
    "fromworkdatas(DataModel)\0"
    "isoption,whicharis,whichpro,whichoptionis\0"
    "receiveConfigureAll(int,int,int,int)\0"
    "QueryTime()\0"
};

void SqlOperate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SqlOperate *_t = static_cast<SqlOperate *>(_o);
        switch (_id) {
        case 0: _t->sendTime((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->datasqlopen(); break;
        case 2: _t->mysqlopen(); break;
        case 3: _t->sqlclose(); break;
        case 4: _t->sqlInit(); break;
        case 5: _t->curvesqlopen(); break;
        case 6: _t->fromworkdatas((*reinterpret_cast< DataModel(*)>(_a[1]))); break;
        case 7: _t->receiveConfigureAll((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 8: _t->QueryTime(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SqlOperate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SqlOperate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SqlOperate,
      qt_meta_data_SqlOperate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SqlOperate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SqlOperate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SqlOperate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SqlOperate))
        return static_cast<void*>(const_cast< SqlOperate*>(this));
    return QObject::qt_metacast(_clname);
}

int SqlOperate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void SqlOperate::sendTime(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
