/****************************************************************************
** Meta object code from reading C++ file 'qartnetdriver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/qdmxlib/private/qartnetdriver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qartnetdriver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QArtnetDriver_t {
    QByteArrayData data[9];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QArtnetDriver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QArtnetDriver_t qt_meta_stringdata_QArtnetDriver = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QArtnetDriver"
QT_MOC_LITERAL(1, 14, 9), // "StyleCode"
QT_MOC_LITERAL(2, 24, 4), // "Node"
QT_MOC_LITERAL(3, 29, 10), // "Controller"
QT_MOC_LITERAL(4, 40, 5), // "Media"
QT_MOC_LITERAL(5, 46, 5), // "Route"
QT_MOC_LITERAL(6, 52, 6), // "Backup"
QT_MOC_LITERAL(7, 59, 6), // "Config"
QT_MOC_LITERAL(8, 66, 6) // "Visual"

    },
    "QArtnetDriver\0StyleCode\0Node\0Controller\0"
    "Media\0Route\0Backup\0Config\0Visual"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QArtnetDriver[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    7,   19,

 // enum data: key, value
       2, uint(QArtnetDriver::Node),
       3, uint(QArtnetDriver::Controller),
       4, uint(QArtnetDriver::Media),
       5, uint(QArtnetDriver::Route),
       6, uint(QArtnetDriver::Backup),
       7, uint(QArtnetDriver::Config),
       8, uint(QArtnetDriver::Visual),

       0        // eod
};

void QArtnetDriver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QArtnetDriver::staticMetaObject = { {
    QMetaObject::SuperData::link<QDmxGenericNetworkDriver::staticMetaObject>(),
    qt_meta_stringdata_QArtnetDriver.data,
    qt_meta_data_QArtnetDriver,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QArtnetDriver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QArtnetDriver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QArtnetDriver.stringdata0))
        return static_cast<void*>(this);
    return QDmxGenericNetworkDriver::qt_metacast(_clname);
}

int QArtnetDriver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDmxGenericNetworkDriver::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
