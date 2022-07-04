/****************************************************************************
** Meta object code from reading C++ file 'qdmxusbdevice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/qdmxlib/private/qdmxusbdevice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdmxusbdevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QDmxUsbDevice_t {
    QByteArrayData data[18];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QDmxUsbDevice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QDmxUsbDevice_t qt_meta_stringdata_QDmxUsbDevice = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QDmxUsbDevice"
QT_MOC_LITERAL(1, 14, 7), // "setData"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 4), // "port"
QT_MOC_LITERAL(4, 28, 7), // "channel"
QT_MOC_LITERAL(5, 36, 4), // "data"
QT_MOC_LITERAL(6, 41, 4), // "Type"
QT_MOC_LITERAL(7, 46, 7), // "ProRXTX"
QT_MOC_LITERAL(8, 54, 6), // "OpenTX"
QT_MOC_LITERAL(9, 61, 6), // "ProMk2"
QT_MOC_LITERAL(10, 68, 8), // "UltraPro"
QT_MOC_LITERAL(11, 77, 7), // "DMX4ALL"
QT_MOC_LITERAL(12, 85, 7), // "VinceTX"
QT_MOC_LITERAL(13, 93, 8), // "Eurolite"
QT_MOC_LITERAL(14, 102, 7), // "Backend"
QT_MOC_LITERAL(15, 110, 7), // "LibFTDI"
QT_MOC_LITERAL(16, 118, 6), // "FTD2XX"
QT_MOC_LITERAL(17, 125, 6) // "Serial"

    },
    "QDmxUsbDevice\0setData\0\0port\0channel\0"
    "data\0Type\0ProRXTX\0OpenTX\0ProMk2\0"
    "UltraPro\0DMX4ALL\0VinceTX\0Eurolite\0"
    "Backend\0LibFTDI\0FTD2XX\0Serial"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QDmxUsbDevice[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       2,   48, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   29,    2, 0x09 /* Protected */,
       1,    3,   36,    2, 0x09 /* Protected */,
       1,    2,   43,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar, QMetaType::UShort, QMetaType::UChar,    3,    4,    5,
    QMetaType::Void, QMetaType::UChar, QMetaType::UShort, QMetaType::QByteArray,    3,    4,    5,
    QMetaType::Void, QMetaType::UChar, QMetaType::QByteArray,    3,    5,

 // enums: name, alias, flags, count, data
       6,    6, 0x0,    7,   58,
      14,   14, 0x0,    3,   72,

 // enum data: key, value
       7, uint(QDmxUsbDevice::ProRXTX),
       8, uint(QDmxUsbDevice::OpenTX),
       9, uint(QDmxUsbDevice::ProMk2),
      10, uint(QDmxUsbDevice::UltraPro),
      11, uint(QDmxUsbDevice::DMX4ALL),
      12, uint(QDmxUsbDevice::VinceTX),
      13, uint(QDmxUsbDevice::Eurolite),
      15, uint(QDmxUsbDevice::LibFTDI),
      16, uint(QDmxUsbDevice::FTD2XX),
      17, uint(QDmxUsbDevice::Serial),

       0        // eod
};

void QDmxUsbDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QDmxUsbDevice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setData((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 1: _t->setData((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 2: _t->setData((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QDmxUsbDevice::staticMetaObject = { {
    QMetaObject::SuperData::link<QDmxDevice::staticMetaObject>(),
    qt_meta_stringdata_QDmxUsbDevice.data,
    qt_meta_data_QDmxUsbDevice,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QDmxUsbDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QDmxUsbDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QDmxUsbDevice.stringdata0))
        return static_cast<void*>(this);
    return QDmxDevice::qt_metacast(_clname);
}

int QDmxUsbDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDmxDevice::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
