/****************************************************************************
** Meta object code from reading C++ file 'shiboqi_remake.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/ui/shiboqi_remake.h"
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
    QByteArrayData data[47];
    char stringdata0[801];
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
QT_MOC_LITERAL(7, 120, 10), // "updatePlot"
QT_MOC_LITERAL(8, 131, 11), // "eventFilter"
QT_MOC_LITERAL(9, 143, 3), // "obj"
QT_MOC_LITERAL(10, 147, 7), // "QEvent*"
QT_MOC_LITERAL(11, 155, 5), // "event"
QT_MOC_LITERAL(12, 161, 15), // "onUdpBindFailed"
QT_MOC_LITERAL(13, 177, 11), // "errorString"
QT_MOC_LITERAL(14, 189, 15), // "onAnalysisReady"
QT_MOC_LITERAL(15, 205, 22), // "WaveformAnalysisResult"
QT_MOC_LITERAL(16, 228, 6), // "result"
QT_MOC_LITERAL(17, 235, 22), // "onDownsampledDataReady"
QT_MOC_LITERAL(18, 258, 15), // "QVector<double>"
QT_MOC_LITERAL(19, 274, 8), // "voltages"
QT_MOC_LITERAL(20, 283, 5), // "times"
QT_MOC_LITERAL(21, 289, 31), // "on_waveformSwitchButton_clicked"
QT_MOC_LITERAL(22, 321, 28), // "on_frequencyUpButton_clicked"
QT_MOC_LITERAL(23, 350, 30), // "on_frequencyDownButton_clicked"
QT_MOC_LITERAL(24, 381, 28), // "on_amplitudeUpButton_clicked"
QT_MOC_LITERAL(25, 410, 30), // "on_amplitudeDownButton_clicked"
QT_MOC_LITERAL(26, 441, 25), // "on_handDrawButton_toggled"
QT_MOC_LITERAL(27, 467, 26), // "on_clearDrawButton_clicked"
QT_MOC_LITERAL(28, 494, 28), // "on_saveAndSendButton_clicked"
QT_MOC_LITERAL(29, 523, 23), // "on_pushButton_2_toggled"
QT_MOC_LITERAL(30, 547, 18), // "refreshSerialPorts"
QT_MOC_LITERAL(31, 566, 18), // "onParsedSerialData"
QT_MOC_LITERAL(32, 585, 4), // "duty"
QT_MOC_LITERAL(33, 590, 8), // "highTime"
QT_MOC_LITERAL(34, 599, 7), // "lowTime"
QT_MOC_LITERAL(35, 607, 9), // "frequency"
QT_MOC_LITERAL(36, 617, 22), // "onWaveformSendProgress"
QT_MOC_LITERAL(37, 640, 7), // "current"
QT_MOC_LITERAL(38, 648, 5), // "total"
QT_MOC_LITERAL(39, 654, 23), // "onWaveformSendCompleted"
QT_MOC_LITERAL(40, 678, 12), // "successCount"
QT_MOC_LITERAL(41, 691, 10), // "totalCount"
QT_MOC_LITERAL(42, 702, 20), // "onWaveformSendFailed"
QT_MOC_LITERAL(43, 723, 12), // "errorMessage"
QT_MOC_LITERAL(44, 736, 15), // "onSpectrumReady"
QT_MOC_LITERAL(45, 752, 22), // "SpectrumAnalysisResult"
QT_MOC_LITERAL(46, 775, 25) // "on_viewModeButton_toggled"

    },
    "shiboqi_remake\0on_setButton_clicked\0"
    "\0on_listenButton_toggled\0checked\0"
    "on_loopSendButton_toggled\0"
    "on_restartButton_clicked\0updatePlot\0"
    "eventFilter\0obj\0QEvent*\0event\0"
    "onUdpBindFailed\0errorString\0onAnalysisReady\0"
    "WaveformAnalysisResult\0result\0"
    "onDownsampledDataReady\0QVector<double>\0"
    "voltages\0times\0on_waveformSwitchButton_clicked\0"
    "on_frequencyUpButton_clicked\0"
    "on_frequencyDownButton_clicked\0"
    "on_amplitudeUpButton_clicked\0"
    "on_amplitudeDownButton_clicked\0"
    "on_handDrawButton_toggled\0"
    "on_clearDrawButton_clicked\0"
    "on_saveAndSendButton_clicked\0"
    "on_pushButton_2_toggled\0refreshSerialPorts\0"
    "onParsedSerialData\0duty\0highTime\0"
    "lowTime\0frequency\0onWaveformSendProgress\0"
    "current\0total\0onWaveformSendCompleted\0"
    "successCount\0totalCount\0onWaveformSendFailed\0"
    "errorMessage\0onSpectrumReady\0"
    "SpectrumAnalysisResult\0on_viewModeButton_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_shiboqi_remake[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  139,    2, 0x08 /* Private */,
       3,    1,  140,    2, 0x08 /* Private */,
       5,    1,  143,    2, 0x08 /* Private */,
       6,    0,  146,    2, 0x08 /* Private */,
       7,    0,  147,    2, 0x08 /* Private */,
       8,    2,  148,    2, 0x08 /* Private */,
      12,    1,  153,    2, 0x08 /* Private */,
      14,    1,  156,    2, 0x08 /* Private */,
      17,    2,  159,    2, 0x08 /* Private */,
      21,    0,  164,    2, 0x08 /* Private */,
      22,    0,  165,    2, 0x08 /* Private */,
      23,    0,  166,    2, 0x08 /* Private */,
      24,    0,  167,    2, 0x08 /* Private */,
      25,    0,  168,    2, 0x08 /* Private */,
      26,    1,  169,    2, 0x08 /* Private */,
      27,    0,  172,    2, 0x08 /* Private */,
      28,    0,  173,    2, 0x08 /* Private */,
      29,    1,  174,    2, 0x08 /* Private */,
      30,    0,  177,    2, 0x08 /* Private */,
      31,    4,  178,    2, 0x08 /* Private */,
      36,    2,  187,    2, 0x08 /* Private */,
      39,    2,  192,    2, 0x08 /* Private */,
      42,    1,  197,    2, 0x08 /* Private */,
      44,    1,  200,    2, 0x08 /* Private */,
      46,    1,  203,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 10,    9,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 18,   19,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Double,   32,   33,   34,   35,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   37,   38,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   40,   41,
    QMetaType::Void, QMetaType::QString,   43,
    QMetaType::Void, 0x80000000 | 45,   16,
    QMetaType::Void, QMetaType::Bool,    4,

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
        case 4: _t->updatePlot(); break;
        case 5: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->onUdpBindFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->onAnalysisReady((*reinterpret_cast< const WaveformAnalysisResult(*)>(_a[1]))); break;
        case 8: _t->onDownsampledDataReady((*reinterpret_cast< const QVector<double>(*)>(_a[1])),(*reinterpret_cast< const QVector<double>(*)>(_a[2]))); break;
        case 9: _t->on_waveformSwitchButton_clicked(); break;
        case 10: _t->on_frequencyUpButton_clicked(); break;
        case 11: _t->on_frequencyDownButton_clicked(); break;
        case 12: _t->on_amplitudeUpButton_clicked(); break;
        case 13: _t->on_amplitudeDownButton_clicked(); break;
        case 14: _t->on_handDrawButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->on_clearDrawButton_clicked(); break;
        case 16: _t->on_saveAndSendButton_clicked(); break;
        case 17: _t->on_pushButton_2_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->refreshSerialPorts(); break;
        case 19: _t->onParsedSerialData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 20: _t->onWaveformSendProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 21: _t->onWaveformSendCompleted((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: _t->onWaveformSendFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: _t->onSpectrumReady((*reinterpret_cast< const SpectrumAnalysisResult(*)>(_a[1]))); break;
        case 24: _t->on_viewModeButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
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
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
