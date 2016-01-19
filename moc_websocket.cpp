/****************************************************************************
** Meta object code from reading C++ file 'websocket.h'
**
** Created: Thu Oct 29 17:29:36 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "source/websocket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'websocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WebSocket[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      26,   10,   10,   10, 0x05,
      38,   10,   10,   10, 0x05,
      59,   53,   10,   10, 0x05,
     123,  102,   10,   10, 0x05,
     182,   10,   10,   10, 0x05,
     222,  204,   10,   10, 0x05,
     254,  204,   10,   10, 0x05,
     299,  291,   10,   10, 0x05,
     328,  291,   10,   10, 0x05,
     368,  362,   10,   10, 0x05,
     416,  404,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     447,  430,   10,   10, 0x0a,
     501,  491,   10,   10, 0x2a,
     537,   10,   10,   10, 0x2a,
     554,  545,   10,   10, 0x0a,
     574,  570,   10,   10, 0x2a,
     585,   10,   10,   10, 0x0a,
     592,   10,   10,   10, 0x08,
     619,  606,   10,   10, 0x08,
     685,  677,   10,   10, 0x08,
     727,  715,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WebSocket[] = {
    "WebSocket\0\0aboutToClose()\0connected()\0"
    "disconnected()\0state\0"
    "stateChanged(QAbstractSocket::SocketState)\0"
    "proxy,pAuthenticator\0"
    "proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)\0"
    "readChannelFinished()\0frame,isLastFrame\0"
    "textFrameReceived(QString,bool)\0"
    "binaryFrameReceived(QByteArray,bool)\0"
    "message\0textMessageReceived(QString)\0"
    "binaryMessageReceived(QByteArray)\0"
    "error\0error(QAbstractSocket::SocketError)\0"
    "elapsedTime\0pong(quint64)\0closeCode,reason\0"
    "close(WebSocketProtocol::CloseCode,QString)\0"
    "closeCode\0close(WebSocketProtocol::CloseCode)\0"
    "close()\0url,mask\0open(QUrl,bool)\0url\0"
    "open(QUrl)\0ping()\0processData()\0"
    "opCode,frame\0"
    "processControlFrame(WebSocketProtocol::OpCode,QByteArray)\0"
    "pSocket\0processHandshake(QTcpSocket*)\0"
    "socketState\0"
    "processStateChanged(QAbstractSocket::SocketState)\0"
};

void WebSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WebSocket *_t = static_cast<WebSocket *>(_o);
        switch (_id) {
        case 0: _t->aboutToClose(); break;
        case 1: _t->connected(); break;
        case 2: _t->disconnected(); break;
        case 3: _t->stateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 4: _t->proxyAuthenticationRequired((*reinterpret_cast< const QNetworkProxy(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 5: _t->readChannelFinished(); break;
        case 6: _t->textFrameReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->binaryFrameReceived((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->textMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->binaryMessageReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 10: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 11: _t->pong((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        case 12: _t->close((*reinterpret_cast< WebSocketProtocol::CloseCode(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: _t->close((*reinterpret_cast< WebSocketProtocol::CloseCode(*)>(_a[1]))); break;
        case 14: _t->close(); break;
        case 15: _t->open((*reinterpret_cast< const QUrl(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 16: _t->open((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 17: _t->ping(); break;
        case 18: _t->processData(); break;
        case 19: _t->processControlFrame((*reinterpret_cast< WebSocketProtocol::OpCode(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 20: _t->processHandshake((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 21: _t->processStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WebSocket::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WebSocket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WebSocket,
      qt_meta_data_WebSocket, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WebSocket::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WebSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WebSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WebSocket))
        return static_cast<void*>(const_cast< WebSocket*>(this));
    return QObject::qt_metacast(_clname);
}

int WebSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void WebSocket::aboutToClose()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void WebSocket::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void WebSocket::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void WebSocket::stateChanged(QAbstractSocket::SocketState _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WebSocket::proxyAuthenticationRequired(const QNetworkProxy & _t1, QAuthenticator * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void WebSocket::readChannelFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void WebSocket::textFrameReceived(QString _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void WebSocket::binaryFrameReceived(QByteArray _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void WebSocket::textMessageReceived(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void WebSocket::binaryMessageReceived(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void WebSocket::error(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void WebSocket::pong(quint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_END_MOC_NAMESPACE
