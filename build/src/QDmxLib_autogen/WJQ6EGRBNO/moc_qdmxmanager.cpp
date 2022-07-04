/****************************************************************************
** Meta object code from reading C++ file 'qdmxmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/qdmxlib/private/qdmxmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdmxmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QDmxManager_t {
    QByteArrayData data[15];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QDmxManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QDmxManager_t qt_meta_stringdata_QDmxManager = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QDmxManager"
QT_MOC_LITERAL(1, 12, 23), // "availableDevicesChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 16), // "inputDataChanged"
QT_MOC_LITERAL(4, 54, 8), // "universe"
QT_MOC_LITERAL(5, 63, 4), // "data"
QT_MOC_LITERAL(6, 68, 22), // "deviceInputDataChanged"
QT_MOC_LITERAL(7, 91, 4), // "port"
QT_MOC_LITERAL(8, 96, 9), // "MergeType"
QT_MOC_LITERAL(9, 106, 3), // "HTP"
QT_MOC_LITERAL(10, 110, 3), // "LTP"
QT_MOC_LITERAL(11, 114, 4), // "LoTP"
QT_MOC_LITERAL(12, 119, 8), // "PortType"
QT_MOC_LITERAL(13, 128, 5), // "Input"
QT_MOC_LITERAL(14, 134, 6) // "Output"

    },
    "QDmxManager\0availableDevicesChanged\0"
    "\0inputDataChanged\0universe\0data\0"
    "deviceInputDataChanged\0port\0MergeType\0"
    "HTP\0LTP\0LoTP\0PortType\0Input\0Output"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QDmxManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       2,   40, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    2,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   35,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar, QMetaType::QByteArray,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar, QMetaType::QByteArray,    7,    5,

 // enums: name, alias, flags, count, data
       8,    8, 0x0,    3,   50,
      12,   12, 0x0,    2,   56,

 // enum data: key, value
       9, uint(QDmxManager::HTP),
      10, uint(QDmxManager::LTP),
      11, uint(QDmxManager::LoTP),
      13, uint(QDmxManager::Input),
      14, uint(QDmxManager::Output),

       0        // eod
};

void QDmxManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QDmxManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->availableDevicesChanged(); break;
        case 1: _t->inputDataChanged((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 2: _t->deviceInputDataChanged((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QDmxManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QDmxManager::availableDevicesChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QDmxManager::*)(quint8 , const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QDmxManager::inputDataChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QDmxManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QDmxManager.data,
    qt_meta_data_QDmxManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QDmxManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QDmxManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QDmxManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QDmxManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void QDmxManager::availableDevicesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QDmxManager::inputDataChanged(quint8 _t1, const QByteArray & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
