/****************************************************************************
** Meta object code from reading C++ file 'XGlobalHook.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../XGlobalHook.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XGlobalHook.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_XGlobalHook_t {
    QByteArrayData data[9];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_XGlobalHook_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_XGlobalHook_t qt_meta_stringdata_XGlobalHook = {
    {
QT_MOC_LITERAL(0, 0, 11), // "XGlobalHook"
QT_MOC_LITERAL(1, 12, 10), // "mouseEvent"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "nCode"
QT_MOC_LITERAL(4, 30, 6), // "WPARAM"
QT_MOC_LITERAL(5, 37, 6), // "wParam"
QT_MOC_LITERAL(6, 44, 6), // "LPARAM"
QT_MOC_LITERAL(7, 51, 6), // "lParam"
QT_MOC_LITERAL(8, 58, 8) // "keyEvent"

    },
    "XGlobalHook\0mouseEvent\0\0nCode\0WPARAM\0"
    "wParam\0LPARAM\0lParam\0keyEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_XGlobalHook[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,
       8,    3,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 6,    3,    5,    7,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 6,    3,    5,    7,

       0        // eod
};

void XGlobalHook::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<XGlobalHook *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< WPARAM(*)>(_a[2])),(*reinterpret_cast< LPARAM(*)>(_a[3]))); break;
        case 1: _t->keyEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< WPARAM(*)>(_a[2])),(*reinterpret_cast< LPARAM(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (XGlobalHook::*)(int , WPARAM , LPARAM );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XGlobalHook::mouseEvent)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (XGlobalHook::*)(int , WPARAM , LPARAM );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XGlobalHook::keyEvent)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject XGlobalHook::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_XGlobalHook.data,
    qt_meta_data_XGlobalHook,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *XGlobalHook::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *XGlobalHook::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_XGlobalHook.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int XGlobalHook::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void XGlobalHook::mouseEvent(int _t1, WPARAM _t2, LPARAM _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XGlobalHook::keyEvent(int _t1, WPARAM _t2, LPARAM _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
