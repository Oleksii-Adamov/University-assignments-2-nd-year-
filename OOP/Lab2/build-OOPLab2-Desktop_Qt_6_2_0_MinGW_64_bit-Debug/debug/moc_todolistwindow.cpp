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
    const uint offsetsAndSize[30];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ToDoListWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ToDoListWindow_t qt_meta_stringdata_ToDoListWindow = {
    {
QT_MOC_LITERAL(0, 14), // "ToDoListWindow"
QT_MOC_LITERAL(15, 21), // "delete_project_button"
QT_MOC_LITERAL(37, 0), // ""
QT_MOC_LITERAL(38, 4), // "name"
QT_MOC_LITERAL(43, 19), // "edit_project_button"
QT_MOC_LITERAL(63, 7), // "oldname"
QT_MOC_LITERAL(71, 8), // "new_name"
QT_MOC_LITERAL(80, 12), // "edit_project"
QT_MOC_LITERAL(93, 23), // "on_actionBack_triggered"
QT_MOC_LITERAL(117, 24), // "on_pushButtonAdd_clicked"
QT_MOC_LITERAL(142, 31), // "on_pushButtonStartTimer_clicked"
QT_MOC_LITERAL(174, 25), // "on_pushButtonEdit_clicked"
QT_MOC_LITERAL(200, 27), // "on_pushButtonDelete_clicked"
QT_MOC_LITERAL(228, 38), // "on_actionDelete_this_project_..."
QT_MOC_LITERAL(267, 30) // "on_actionEditProject_triggered"

    },
    "ToDoListWindow\0delete_project_button\0"
    "\0name\0edit_project_button\0oldname\0"
    "new_name\0edit_project\0on_actionBack_triggered\0"
    "on_pushButtonAdd_clicked\0"
    "on_pushButtonStartTimer_clicked\0"
    "on_pushButtonEdit_clicked\0"
    "on_pushButtonDelete_clicked\0"
    "on_actionDelete_this_project_triggered\0"
    "on_actionEditProject_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ToDoListWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x06,    1 /* Public */,
       4,    2,   77,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,   82,    2, 0x0a,    6 /* Public */,
       8,    0,   85,    2, 0x08,    8 /* Private */,
       9,    0,   86,    2, 0x08,    9 /* Private */,
      10,    0,   87,    2, 0x08,   10 /* Private */,
      11,    0,   88,    2, 0x08,   11 /* Private */,
      12,    0,   89,    2, 0x08,   12 /* Private */,
      13,    0,   90,    2, 0x08,   13 /* Private */,
      14,    0,   91,    2, 0x08,   14 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
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
        case 0: _t->delete_project_button((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->edit_project_button((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->edit_project((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_actionBack_triggered(); break;
        case 4: _t->on_pushButtonAdd_clicked(); break;
        case 5: _t->on_pushButtonStartTimer_clicked(); break;
        case 6: _t->on_pushButtonEdit_clicked(); break;
        case 7: _t->on_pushButtonDelete_clicked(); break;
        case 8: _t->on_actionDelete_this_project_triggered(); break;
        case 9: _t->on_actionEditProject_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ToDoListWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ToDoListWindow::delete_project_button)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ToDoListWindow::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ToDoListWindow::edit_project_button)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ToDoListWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ToDoListWindow.offsetsAndSize,
    qt_meta_data_ToDoListWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ToDoListWindow_t
, QtPrivate::TypeAndForceComplete<ToDoListWindow, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ToDoListWindow::delete_project_button(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ToDoListWindow::edit_project_button(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
