/****************************************************************************
** Meta object code from reading C++ file 'save.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "save.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'save.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Save[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,
      34,    5,    5,    5, 0x05,
      57,    5,    5,    5, 0x05,
      76,    5,    5,    5, 0x05,
     107,    5,    5,    5, 0x05,
     128,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
     146,    5,    5,    5, 0x08,
     170,    5,    5,    5, 0x08,
     196,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Save[] = {
    "Save\0\0sendSaveAdvancedState(bool)\0"
    "sendSaveBaseinfo(bool)\0sendDeSingle(bool)\0"
    "sendSaveMasterSlaveState(bool)\0"
    "sendCloseInput(bool)\0sendShutDown(int)\0"
    "on_pushButton_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_cancel_clicked()\0"
};

void Save::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Save *_t = static_cast<Save *>(_o);
        switch (_id) {
        case 0: _t->sendSaveAdvancedState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sendSaveBaseinfo((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->sendDeSingle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->sendSaveMasterSlaveState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->sendCloseInput((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->sendShutDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_pushButton_clicked(); break;
        case 7: _t->on_pushButton_2_clicked(); break;
        case 8: _t->on_pushButton_cancel_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Save::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Save::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Save,
      qt_meta_data_Save, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Save::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Save::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Save::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Save))
        return static_cast<void*>(const_cast< Save*>(this));
    return QDialog::qt_metacast(_clname);
}

int Save::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void Save::sendSaveAdvancedState(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Save::sendSaveBaseinfo(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Save::sendDeSingle(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Save::sendSaveMasterSlaveState(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Save::sendCloseInput(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Save::sendShutDown(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
