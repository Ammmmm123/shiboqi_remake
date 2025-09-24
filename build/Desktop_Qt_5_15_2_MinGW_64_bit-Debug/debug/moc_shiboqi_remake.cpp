/****************************************************************************
** Meta object code from reading C++ file 'shiboqi_remake.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../shiboqi_remake.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shiboqi_remake.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_shiboqi_remake_t {
    QByteArrayData data[18];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_shiboqi_remake_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_shiboqi_remake_t qt_meta_stringdata_shiboqi_remake = {
    {
QT_MOC_LITERAL(0, 0, 14), // "shiboqi_remake"
QT_MOC_LITERAL(1, 15, 20), // "on_setButton_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 23), // "on_listenButton_toggled"
QT_MOC_LITERAL(4, 61, 7), // "checked"
QT_MOC_LITERAL(5, 69, 25), // "on_loopSendButton_toggled"
QT_MOC_LITERAL(6, 95, 24), // "on_restartButton_clicked"
QT_MOC_LITERAL(7, 120, 14), // "onDataReceived"
QT_MOC_LITERAL(8, 135, 15), // "QVector<double>"
QT_MOC_LITERAL(9, 151, 8), // "voltages"
QT_MOC_LITERAL(10, 160, 5), // "times"
QT_MOC_LITERAL(11, 166, 10), // "updatePlot"
QT_MOC_LITERAL(12, 177, 11), // "eventFilter"
QT_MOC_LITERAL(13, 189, 3), // "obj"
QT_MOC_LITERAL(14, 193, 7), // "QEvent*"
QT_MOC_LITERAL(15, 201, 5), // "event"
QT_MOC_LITERAL(16, 207, 15), // "onUdpBindFailed"
QT_MOC_LITERAL(17, 223, 11) // "errorString"

    },
    "shiboqi_remake\0on_setButton_clicked\0"
    "\0on_listenButton_toggled\0checked\0"
    "on_loopSendButton_toggled\0"
    "on_restartButton_clicked\0onDataReceived\0"
    "QVector<double>\0voltages\0times\0"
    "updatePlot\0eventFilter\0obj\0QEvent*\0"
    "event\0onUdpBindFailed\0errorString"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_shiboqi_remake[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    1,   55,    2, 0x08 /* Private */,
       5,    1,   58,    2, 0x08 /* Private */,
       6,    0,   61,    2, 0x08 /* Private */,
       7,    2,   62,    2, 0x08 /* Private */,
      11,    0,   67,    2, 0x08 /* Private */,
      12,    2,   68,    2, 0x08 /* Private */,
      16,    1,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8,    9,   10,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 14,   13,   15,
    QMetaType::Void, QMetaType::QString,   17,

       0        // eod
};

void shiboqi_remake::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<shiboqi_remake *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_setButton_clicked(); break;
        case 1: _t->on_listenButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_loopSendButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_restartButton_clicked(); break;
        case 4: _t->onDataReceived((*reinterpret_cast< const QVector<double>(*)>(_a[1])),(*reinterpret_cast< const QVector<double>(*)>(_a[2]))); break;
        case 5: _t->updatePlot(); break;
        case 6: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->onUdpBindFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject shiboqi_remake::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_shiboqi_remake.data,
    qt_meta_data_shiboqi_remake,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *shiboqi_remake::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *shiboqi_remake::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_shiboqi_remake.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int shiboqi_remake::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
