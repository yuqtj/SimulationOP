/****************************************************************************
** Meta object code from reading C++ file 'RecordOp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RecordOp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RecordOp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RecordOp_t {
    QByteArrayData data[21];
    char stringdata0[259];
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
QT_MOC_LITERAL(4, 38, 20), // "onExcuteOpCompeleted"
QT_MOC_LITERAL(5, 59, 9), // "onNewFile"
QT_MOC_LITERAL(6, 69, 10), // "onOpenFile"
QT_MOC_LITERAL(7, 80, 10), // "onSaveFile"
QT_MOC_LITERAL(8, 91, 10), // "mouseEvent"
QT_MOC_LITERAL(9, 102, 5), // "nCode"
QT_MOC_LITERAL(10, 108, 6), // "WPARAM"
QT_MOC_LITERAL(11, 115, 6), // "wParam"
QT_MOC_LITERAL(12, 122, 6), // "LPARAM"
QT_MOC_LITERAL(13, 129, 6), // "lParam"
QT_MOC_LITERAL(14, 136, 8), // "keyEvent"
QT_MOC_LITERAL(15, 145, 22), // "onActivatedSysTrayIcon"
QT_MOC_LITERAL(16, 168, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(17, 202, 6), // "reason"
QT_MOC_LITERAL(18, 209, 9), // "onExitApp"
QT_MOC_LITERAL(19, 219, 18), // "copyTreeItemAction"
QT_MOC_LITERAL(20, 238, 20) // "deleteTreeItemAction"

    },
    "RecordOp\0onStartRecord\0\0onDoOperation\0"
    "onExcuteOpCompeleted\0onNewFile\0"
    "onOpenFile\0onSaveFile\0mouseEvent\0nCode\0"
    "WPARAM\0wParam\0LPARAM\0lParam\0keyEvent\0"
    "onActivatedSysTrayIcon\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0onExitApp\0copyTreeItemAction\0"
    "deleteTreeItemAction"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecordOp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    3,   80,    2, 0x0a /* Public */,
      14,    3,   87,    2, 0x0a /* Public */,
      15,    1,   94,    2, 0x0a /* Public */,
      18,    0,   97,    2, 0x0a /* Public */,
      19,    0,   98,    2, 0x0a /* Public */,
      20,    0,   99,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 12,    9,   11,   13,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 12,    9,   11,   13,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RecordOp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RecordOp *_t = static_cast<RecordOp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onStartRecord(); break;
        case 1: _t->onDoOperation(); break;
        case 2: _t->onExcuteOpCompeleted(); break;
        case 3: _t->onNewFile(); break;
        case 4: _t->onOpenFile(); break;
        case 5: _t->onSaveFile(); break;
        case 6: _t->mouseEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< WPARAM(*)>(_a[2])),(*reinterpret_cast< LPARAM(*)>(_a[3]))); break;
        case 7: _t->keyEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< WPARAM(*)>(_a[2])),(*reinterpret_cast< LPARAM(*)>(_a[3]))); break;
        case 8: _t->onActivatedSysTrayIcon((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 9: _t->onExitApp(); break;
        case 10: _t->copyTreeItemAction(); break;
        case 11: _t->deleteTreeItemAction(); break;
        default: ;
        }
    }
}

const QMetaObject RecordOp::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RecordOp.data,
      qt_meta_data_RecordOp,  qt_static_metacall, nullptr, nullptr}
};


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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
