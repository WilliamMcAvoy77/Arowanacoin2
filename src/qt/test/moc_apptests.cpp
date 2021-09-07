/****************************************************************************
** Meta object code from reading C++ file 'apptests.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qt/test/apptests.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apptests.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AppTests_t {
    QByteArrayData data[9];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AppTests_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AppTests_t qt_meta_stringdata_AppTests = {
    {
QT_MOC_LITERAL(0, 0, 8), // "AppTests"
QT_MOC_LITERAL(1, 9, 8), // "appTests"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 8), // "guiTests"
QT_MOC_LITERAL(4, 28, 11), // "BitcoinGUI*"
QT_MOC_LITERAL(5, 40, 6), // "window"
QT_MOC_LITERAL(6, 47, 12), // "consoleTests"
QT_MOC_LITERAL(7, 60, 11), // "RPCConsole*"
QT_MOC_LITERAL(8, 72, 7) // "console"

    },
    "AppTests\0appTests\0\0guiTests\0BitcoinGUI*\0"
    "window\0consoleTests\0RPCConsole*\0console"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AppTests[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    1,   30,    2, 0x08 /* Private */,
       6,    1,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void AppTests::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AppTests *_t = static_cast<AppTests *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->appTests(); break;
        case 1: _t->guiTests((*reinterpret_cast< BitcoinGUI*(*)>(_a[1]))); break;
        case 2: _t->consoleTests((*reinterpret_cast< RPCConsole*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject AppTests::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AppTests.data,
      qt_meta_data_AppTests,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AppTests::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppTests::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AppTests.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AppTests::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
