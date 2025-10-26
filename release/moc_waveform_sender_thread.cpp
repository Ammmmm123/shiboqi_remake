/****************************************************************************
** Meta object code from reading C++ file 'waveform_sender_thread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../waveform_sender_thread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'waveform_sender_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WaveformSenderThread_t {
    QByteArrayData data[10];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WaveformSenderThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WaveformSenderThread_t qt_meta_stringdata_WaveformSenderThread = {
    {
QT_MOC_LITERAL(0, 0, 20), // "WaveformSenderThread"
QT_MOC_LITERAL(1, 21, 15), // "progressUpdated"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 7), // "current"
QT_MOC_LITERAL(4, 46, 5), // "total"
QT_MOC_LITERAL(5, 52, 16), // "sendingCompleted"
QT_MOC_LITERAL(6, 69, 12), // "successCount"
QT_MOC_LITERAL(7, 82, 10), // "totalCount"
QT_MOC_LITERAL(8, 93, 13), // "sendingFailed"
QT_MOC_LITERAL(9, 107, 12) // "errorMessage"

    },
    "WaveformSenderThread\0progressUpdated\0"
    "\0current\0total\0sendingCompleted\0"
    "successCount\0totalCount\0sendingFailed\0"
    "errorMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WaveformSenderThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       5,    2,   34,    2, 0x06 /* Public */,
       8,    1,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void WaveformSenderThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WaveformSenderThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->progressUpdated((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->sendingCompleted((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->sendingFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WaveformSenderThread::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WaveformSenderThread::progressUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WaveformSenderThread::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WaveformSenderThread::sendingCompleted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WaveformSenderThread::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WaveformSenderThread::sendingFailed)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WaveformSenderThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_WaveformSenderThread.data,
    qt_meta_data_WaveformSenderThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WaveformSenderThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WaveformSenderThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WaveformSenderThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int WaveformSenderThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void WaveformSenderThread::progressUpdated(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WaveformSenderThread::sendingCompleted(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WaveformSenderThread::sendingFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
