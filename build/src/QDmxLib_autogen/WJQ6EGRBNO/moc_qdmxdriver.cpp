/****************************************************************************
** Meta object code from reading C++ file 'qdmxdriver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/qdmxlib/private/qdmxdriver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdmxdriver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QDmxDriver_t {
    QByteArrayData data[10];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QDmxDriver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QDmxDriver_t qt_meta_stringdata_QDmxDriver = {
    {
QT_MOC_LITERAL(0, 0, 10), // "QDmxDriver"
QT_MOC_LITERAL(1, 11, 23), // "availableDevicesChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 13), // "enableChanged"
QT_MOC_LITERAL(4, 50, 2), // "en"
QT_MOC_LITERAL(5, 53, 13), // "loadedChanged"
QT_MOC_LITERAL(6, 67, 2), // "st"
QT_MOC_LITERAL(7, 70, 10), // "setEnabled"
QT_MOC_LITERAL(8, 81, 4), // "load"
QT_MOC_LITERAL(9, 86, 6) // "unload"

    },
    "QDmxDriver\0availableDevicesChanged\0\0"
    "enableChanged\0en\0loadedChanged\0st\0"
    "setEnabled\0load\0unload"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QDmxDriver[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   51,    2, 0x0a /* Public */,
       8,    0,   54,    2, 0x0a /* Public */,
       9,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Bool,
    QMetaType::Bool,

       0        // eod
};

void QDmxDriver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QDmxDriver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->availableDevicesChanged(); break;
        case 1: _t->enableChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->loadedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: { bool _r = _t->load();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->unload();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QDmxDriver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QDmxDriver::availableDevicesChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QDmxDriver::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QDmxDriver::enableChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QDmxDriver::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QDmxDriver::loadedChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QDmxDriver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QDmxDriver.data,
    qt_meta_data_QDmxDriver,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QDmxDriver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QDmxDriver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QDmxDriver.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QDmxDriver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QDmxDriver::availableDevicesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QDmxDriver::enableChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QDmxDriver::loadedChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_QDmxDummyDriver_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QDmxDummyDriver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QDmxDummyDriver_t qt_meta_stringdata_QDmxDummyDriver = {
    {
QT_MOC_LITERAL(0, 0, 15) // "QDmxDummyDriver"

    },
    "QDmxDummyDriver"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QDmxDummyDriver[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void QDmxDummyDriver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QDmxDummyDriver::staticMetaObject = { {
    QMetaObject::SuperData::link<QDmxDriver::staticMetaObject>(),
    qt_meta_stringdata_QDmxDummyDriver.data,
    qt_meta_data_QDmxDummyDriver,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QDmxDummyDriver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QDmxDummyDriver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QDmxDummyDriver.stringdata0))
        return static_cast<void*>(this);
    return QDmxDriver::qt_metacast(_clname);
}

int QDmxDummyDriver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDmxDriver::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
