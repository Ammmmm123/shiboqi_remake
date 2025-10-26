/****************************************************************************
** Meta object code from reading C++ file 'udp_receive.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../udp_receive.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udp_receive.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UdpReceiver_t {
    QByteArrayData data[13];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UdpReceiver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UdpReceiver_t qt_meta_stringdata_UdpReceiver = {
    {
QT_MOC_LITERAL(0, 0, 11), // "UdpReceiver"
QT_MOC_LITERAL(1, 12, 12), // "dataReceived"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 15), // "QVector<double>"
QT_MOC_LITERAL(4, 42, 8), // "voltages"
QT_MOC_LITERAL(5, 51, 5), // "times"
QT_MOC_LITERAL(6, 57, 17), // "overRangeDetected"
QT_MOC_LITERAL(7, 75, 11), // "channel1OTR"
QT_MOC_LITERAL(8, 87, 11), // "channel2OTR"
QT_MOC_LITERAL(9, 99, 11), // "sampleIndex"
QT_MOC_LITERAL(10, 111, 10), // "bindFailed"
QT_MOC_LITERAL(11, 122, 11), // "errorString"
QT_MOC_LITERAL(12, 134, 23) // "processPendingDatagrams"

    },
    "UdpReceiver\0dataReceived\0\0QVector<double>\0"
    "voltages\0times\0overRangeDetected\0"
    "channel1OTR\0channel2OTR\0sampleIndex\0"
    "bindFailed\0errorString\0processPendingDatagrams"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UdpReceiver[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       6,    3,   39,    2, 0x06 /* Public */,
      10,    1,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Int,    7,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void UdpReceiver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UdpReceiver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataReceived((*reinterpret_cast< const QVector<double>(*)>(_a[1])),(*reinterpret_cast< const QVector<double>(*)>(_a[2]))); break;
        case 1: _t->overRangeDetected((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->bindFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->processPendingDatagrams(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UdpReceiver::*)(const QVector<double> & , const QVector<double> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UdpReceiver::dataReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UdpReceiver::*)(bool , bool , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UdpReceiver::overRangeDetected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UdpReceiver::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UdpReceiver::bindFailed)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UdpReceiver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_UdpReceiver.data,
    qt_meta_data_UdpReceiver,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UdpReceiver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UdpReceiver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UdpReceiver.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UdpReceiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void UdpReceiver::dataReceived(const QVector<double> & _t1, const QVector<double> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UdpReceiver::overRangeDetected(bool _t1, bool _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UdpReceiver::bindFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
