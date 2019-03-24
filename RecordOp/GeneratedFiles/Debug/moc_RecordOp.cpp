/****************************************************************************
** Meta object code from reading C++ file 'RecordOp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RecordOp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RecordOp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RecordOp_t {
    QByteArrayData data[16];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecordOp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecordOp_t qt_meta_stringdata_RecordOp = {
    {
QT_MOC_LITERAL(0, 0, 8), // "RecordOp"
QT_MOC_LITERAL(1, 9, 13), // "onStartRecord"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 13), // "onDoOperation"
QT_MOC_LITERAL(4, 38, 9), // "onClearOp"
QT_MOC_LITERAL(5, 48, 10), // "mouseEvent"
QT_MOC_LITERAL(6, 59, 5), // "nCode"
QT_MOC_LITERAL(7, 65, 6), // "WPARAM"
QT_MOC_LITERAL(8, 72, 6), // "wParam"
QT_MOC_LITERAL(9, 79, 6), // "LPARAM"
QT_MOC_LITERAL(10, 86, 6), // "lParam"
QT_MOC_LITERAL(11, 93, 8), // "keyEvent"
QT_MOC_LITERAL(12, 102, 22), // "onActivatedSysTrayIcon"
QT_MOC_LITERAL(13, 125, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(14, 159, 6), // "reason"
QT_MOC_LITERAL(15, 166, 9) // "onExitApp"

    },
    "RecordOp\0onStartRecord\0\0onDoOperation\0"
    "onClearOp\0mouseEvent\0nCode\0WPARAM\0"
    "wParam\0LPARAM\0lParam\0keyEvent\0"
    "onActivatedSysTrayIcon\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0onExitApp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecordOp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    3,   52,    2, 0x0a /* Public */,
      11,    3,   59,    2, 0x0a /* Public */,
      12,    1,   66,    2, 0x0a /* Public */,
      15,    0,   69,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, 0x80000000 | 9,    6,    8,   10,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, 0x80000000 | 9,    6,    8,   10,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,

       0        // eod
};

void RecordOp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RecordOp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onStartRecord(); break;
        case 1: _t->onDoOperation(); break;
        case 2: _t->onClearOp(); break;
        case 3: _t->mouseEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< WPARAM(*)>(_a[2])),(*reinterpret_cast< LPARAM(*)>(_a[3]))); break;
        case 4: _t->keyEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< WPARAM(*)>(_a[2])),(*reinterpret_cast< LPARAM(*)>(_a[3]))); break;
        case 5: _t->onActivatedSysTrayIcon((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 6: _t->onExitApp(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RecordOp::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_RecordOp.data,
    qt_meta_data_RecordOp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RecordOp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecordOp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RecordOp.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int RecordOp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
