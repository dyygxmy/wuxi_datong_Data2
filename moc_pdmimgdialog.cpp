/****************************************************************************
** Meta object code from reading C++ file 'pdmimgdialog.h'
**
** Created: Fri Jul 3 08:50:32 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "pdmimgdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pdmimgdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PdmImgDialog[] = {

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
      14,   13,   13,   13, 0x05,
      35,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   13,   13,   13, 0x08,
      75,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PdmImgDialog[] = {
    "PdmImgDialog\0\0sendmessage(QString)\0"
    "cancelpdm()\0on_pdmenterbutton_clicked()\0"
    "on_pdmenterbutton_2_clicked()\0"
};

void PdmImgDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PdmImgDialog *_t = static_cast<PdmImgDialog *>(_o);
        switch (_id) {
        case 0: _t->sendmessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->cancelpdm(); break;
        case 2: _t->on_pdmenterbutton_clicked(); break;
        case 3: _t->on_pdmenterbutton_2_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PdmImgDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PdmImgDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PdmImgDialog,
      qt_meta_data_PdmImgDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PdmImgDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PdmImgDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PdmImgDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PdmImgDialog))
        return static_cast<void*>(const_cast< PdmImgDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int PdmImgDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void PdmImgDialog::sendmessage(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PdmImgDialog::cancelpdm()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
