/****************************************************************************
** Meta object code from reading C++ file 'addnewprojectdialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../OOPLab2/addnewprojectdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addnewprojectdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AddNewProjectDialog_t {
    const uint offsetsAndSize[16];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_AddNewProjectDialog_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_AddNewProjectDialog_t qt_meta_stringdata_AddNewProjectDialog = {
    {
QT_MOC_LITERAL(0, 19), // "AddNewProjectDialog"
QT_MOC_LITERAL(20, 14), // "create_project"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 9), // "file_path"
QT_MOC_LITERAL(46, 12), // "edit_project"
QT_MOC_LITERAL(59, 8), // "new_name"
QT_MOC_LITERAL(68, 28), // "on_pushButton_Cancel_clicked"
QT_MOC_LITERAL(97, 28) // "on_pushButton_Create_clicked"

    },
    "AddNewProjectDialog\0create_project\0\0"
    "file_path\0edit_project\0new_name\0"
    "on_pushButton_Cancel_clicked\0"
    "on_pushButton_Create_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddNewProjectDialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,
       4,    1,   41,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   44,    2, 0x08,    5 /* Private */,
       7,    0,   45,    2, 0x08,    6 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AddNewProjectDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AddNewProjectDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->create_project((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->edit_project((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_Cancel_clicked(); break;
        case 3: _t->on_pushButton_Create_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AddNewProjectDialog::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddNewProjectDialog::create_project)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AddNewProjectDialog::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddNewProjectDialog::edit_project)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject AddNewProjectDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_AddNewProjectDialog.offsetsAndSize,
    qt_meta_data_AddNewProjectDialog,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_AddNewProjectDialog_t
, QtPrivate::TypeAndForceComplete<AddNewProjectDialog, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *AddNewProjectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddNewProjectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AddNewProjectDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int AddNewProjectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void AddNewProjectDialog::create_project(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AddNewProjectDialog::edit_project(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
