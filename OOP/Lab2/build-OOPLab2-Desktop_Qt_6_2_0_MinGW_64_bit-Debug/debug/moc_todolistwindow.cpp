/****************************************************************************
** Meta object code from reading C++ file 'todolistwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../OOPLab2/todolistwindow.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'todolistwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ToDoListWindow_t {
    const uint offsetsAndSize[14];
    char stringdata0[151];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ToDoListWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ToDoListWindow_t qt_meta_stringdata_ToDoListWindow = {
    {
QT_MOC_LITERAL(0, 14), // "ToDoListWindow"
QT_MOC_LITERAL(15, 23), // "on_actionBack_triggered"
QT_MOC_LITERAL(39, 0), // ""
QT_MOC_LITERAL(40, 24), // "on_pushButtonAdd_clicked"
QT_MOC_LITERAL(65, 31), // "on_pushButtonStartTimer_clicked"
QT_MOC_LITERAL(97, 25), // "on_pushButtonEdit_clicked"
QT_MOC_LITERAL(123, 27) // "on_pushButtonDelete_clicked"

    },
    "ToDoListWindow\0on_actionBack_triggered\0"
    "\0on_pushButtonAdd_clicked\0"
    "on_pushButtonStartTimer_clicked\0"
    "on_pushButtonEdit_clicked\0"
    "on_pushButtonDelete_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ToDoListWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x08,    1 /* Private */,
       3,    0,   45,    2, 0x08,    2 /* Private */,
       4,    0,   46,    2, 0x08,    3 /* Private */,
       5,    0,   47,    2, 0x08,    4 /* Private */,
       6,    0,   48,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ToDoListWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ToDoListWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_actionBack_triggered(); break;
        case 1: _t->on_pushButtonAdd_clicked(); break;
        case 2: _t->on_pushButtonStartTimer_clicked(); break;
        case 3: _t->on_pushButtonEdit_clicked(); break;
        case 4: _t->on_pushButtonDelete_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject ToDoListWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ToDoListWindow.offsetsAndSize,
    qt_meta_data_ToDoListWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ToDoListWindow_t
, QtPrivate::TypeAndForceComplete<ToDoListWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *ToDoListWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ToDoListWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ToDoListWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ToDoListWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE