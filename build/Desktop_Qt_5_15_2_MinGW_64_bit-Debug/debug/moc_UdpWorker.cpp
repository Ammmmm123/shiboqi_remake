/****************************************************************************
** Meta object code from reading C++ file 'UdpWorker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../UdpWorker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UdpWorker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UdpWorker_t {
    QByteArrayData data[19];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UdpWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UdpWorker_t qt_meta_stringdata_UdpWorker = {
    {
QT_MOC_LITERAL(0, 0, 9), // "UdpWorker"
QT_MOC_LITERAL(1, 10, 10), // "batchReady"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 15), // "QVector<double>"
QT_MOC_LITERAL(4, 38, 8), // "voltages"
QT_MOC_LITERAL(5, 47, 5), // "times"
QT_MOC_LITERAL(6, 53, 10), // "bindFailed"
QT_MOC_LITERAL(7, 64, 11), // "errorString"
QT_MOC_LITERAL(8, 76, 17), // "overRangeDetected"
QT_MOC_LITERAL(9, 94, 11), // "channel1OTR"
QT_MOC_LITERAL(10, 106, 11), // "channel2OTR"
QT_MOC_LITERAL(11, 118, 11), // "sampleIndex"
QT_MOC_LITERAL(12, 130, 15), // "setLocalAddress"
QT_MOC_LITERAL(13, 146, 7), // "address"
QT_MOC_LITERAL(14, 154, 4), // "port"
QT_MOC_LITERAL(15, 159, 5), // "start"
QT_MOC_LITERAL(16, 165, 4), // "stop"
QT_MOC_LITERAL(17, 170, 11), // "onReadyRead"
QT_MOC_LITERAL(18, 182, 13) // "flushIfNeeded"

    },
    "UdpWorker\0batchReady\0\0QVector<double>\0"
    "voltages\0times\0bindFailed\0errorString\0"
    "overRangeDetected\0channel1OTR\0channel2OTR\0"
    "sampleIndex\0setLocalAddress\0address\0"
    "port\0start\0stop\0onReadyRead\0flushIfNeeded"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UdpWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       6,    1,   59,    2, 0x06 /* Public */,
       8,    3,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    2,   69,    2, 0x0a /* Public */,
      15,    0,   74,    2, 0x0a /* Public */,
      16,    0,   75,    2, 0x0a /* Public */,
      17,    0,   76,    2, 0x08 /* Private */,
      18,    0,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Int,    9,   10,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,   13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UdpWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UdpWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->batchReady((*reinterpret_cast< const QVector<double>(*)>(_a[1])),(*reinterpret_cast< const QVector<double>(*)>(_a[2]))); break;
        case 1: _t->bindFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->overRangeDetected((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->setLocalAddress((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 4: _t->start(); break;
        case 5: _t->stop(); break;
        case 6: _t->onReadyRead(); break;
        case 7: _t->flushIfNeeded(); break;
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
            using _t = void (UdpWorker::*)(const QVector<double> & , const QVector<double> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UdpWorker::batchReady)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UdpWorker::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UdpWorker::bindFailed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UdpWorker::*)(bool , bool , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UdpWorker::overRangeDetected)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UdpWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_UdpWorker.data,
    qt_meta_data_UdpWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UdpWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UdpWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UdpWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UdpWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void UdpWorker::batchReady(const QVector<double> & _t1, const QVector<double> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UdpWorker::bindFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UdpWorker::overRangeDetected(bool _t1, bool _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
