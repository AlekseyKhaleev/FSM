/****************************************************************************
** Meta object code from reading C++ file 'gameWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../gameWidget.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_gameWidget_t {
    uint offsetsAndSizes[18];
    char stringdata0[11];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[6];
    char stringdata5[14];
    char stringdata6[11];
    char stringdata7[11];
    char stringdata8[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_gameWidget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_gameWidget_t qt_meta_stringdata_gameWidget = {
    {
        QT_MOC_LITERAL(0, 10),  // "gameWidget"
        QT_MOC_LITERAL(11, 10),  // "timerEvent"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 12),  // "QTimerEvent*"
        QT_MOC_LITERAL(36, 5),  // "event"
        QT_MOC_LITERAL(42, 13),  // "keyPressEvent"
        QT_MOC_LITERAL(56, 10),  // "QKeyEvent*"
        QT_MOC_LITERAL(67, 10),  // "paintEvent"
        QT_MOC_LITERAL(78, 12)   // "QPaintEvent*"
    },
    "gameWidget",
    "timerEvent",
    "",
    "QTimerEvent*",
    "event",
    "keyPressEvent",
    "QKeyEvent*",
    "paintEvent",
    "QPaintEvent*"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_gameWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x0a,    1 /* Public */,
       5,    1,   35,    2, 0x0a,    3 /* Public */,
       7,    1,   38,    2, 0x0a,    5 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 8,    4,

       0        // eod
};

Q_CONSTINIT const QMetaObject gameWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_gameWidget.offsetsAndSizes,
    qt_meta_data_gameWidget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_gameWidget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<gameWidget, std::true_type>,
        // method 'timerEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTimerEvent *, std::false_type>,
        // method 'keyPressEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QKeyEvent *, std::false_type>,
        // method 'paintEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPaintEvent *, std::false_type>
    >,
    nullptr
} };

void gameWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<gameWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->timerEvent((*reinterpret_cast< std::add_pointer_t<QTimerEvent*>>(_a[1]))); break;
        case 1: _t->keyPressEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        case 2: _t->paintEvent((*reinterpret_cast< std::add_pointer_t<QPaintEvent*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *gameWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gameWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gameWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Robot"))
        return static_cast< Robot*>(this);
    return QWidget::qt_metacast(_clname);
}

int gameWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
