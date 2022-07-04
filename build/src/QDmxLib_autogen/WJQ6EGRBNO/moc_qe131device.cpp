/****************************************************************************
** Meta object code from reading C++ file 'qe131device.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/qdmxlib/private/qe131device.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qe131device.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QE131Device_t {
    QByteArrayData data[9];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QE131Device_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QE131Device_t qt_meta_stringdata_QE131Device = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QE131Device"
QT_MOC_LITERAL(1, 12, 7), // "setData"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 4), // "port"
QT_MOC_LITERAL(4, 26, 7), // "channel"
QT_MOC_LITERAL(5, 34, 4), // "data"
QT_MOC_LITERAL(6, 39, 12), // "readDatagram"
QT_MOC_LITERAL(7, 52, 11), // "socketError"
QT_MOC_LITERAL(8, 64, 28) // "QAbstractSocket::SocketError"

    },
    "QE131Device\0setData\0\0port\0channel\0"
    "data\0readDatagram\0socketError\0"
    "QAbstractSocket::SocketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QE131Device[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x09 /* Protected */,
       1,    3,   46,    2, 0x09 /* Protected */,
       1,    2,   53,    2, 0x09 /* Protected */,
       6,    0,   58,    2, 0x09 /* Protected */,
       7,    1,   59,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar, QMetaType::UShort, QMetaType::UChar,    3,    4,    5,
    QMetaType::Void, QMetaType::UChar, QMetaType::UShort, QMetaType::QByteArray,    3,    4,    5,
    QMetaType::Void, QMetaType::UChar, QMetaType::QByteArray,    3,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    7,

       0        // eod
};

void QE131Device::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QE131Device *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setData((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 1: _t->setData((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 2: _t->setData((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 3: _t->readDatagram(); break;
        case 4: _t->socketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QE131Device::staticMetaObject = { {
    QMetaObject::SuperData::link<QDmxGenericNetworkDevice::staticMetaObject>(),
    qt_meta_stringdata_QE131Device.data,
    qt_meta_data_QE131Device,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QE131Device::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QE131Device::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QE131Device.stringdata0))
        return static_cast<void*>(this);
    return QDmxGenericNetworkDevice::qt_metacast(_clname);
}

int QE131Device::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDmxGenericNetworkDevice::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
