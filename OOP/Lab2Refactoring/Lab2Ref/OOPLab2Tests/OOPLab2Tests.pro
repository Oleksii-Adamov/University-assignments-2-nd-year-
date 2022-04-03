QT += testlib
QT += gui
QT += widgets
QT += multimedia

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    unittests.cpp \
    ../OOPLab2/addnewprojectdialog.cpp \
    ../OOPLab2/addtotodolist.cpp \
    ../OOPLab2/filepath.cpp \
    ../OOPLab2/mainwindow.cpp \
    ../OOPLab2/settingsdialog.cpp \
    ../OOPLab2/timer.cpp \
    ../OOPLab2/todolistdata.cpp \
    ../OOPLab2/todolistwindow.cpp

HEADERS += \
    ../OOPLab2/addnewprojectdialog.h \
    ../OOPLab2/addtotodolist.h \
    ../OOPLab2/filepath.h \
    ../OOPLab2/mainwindow.h \
    ../OOPLab2/settingsdialog.h \
    ../OOPLab2/timer.h \
    ../OOPLab2/todolistdata.h \
    ../OOPLab2/todolistwindow.h

FORMS += \
    ../OOPLab2/addnewprojectdialog.ui \
    ../OOPLab2/addtotodolist.ui \
    ../OOPLab2/mainwindow.ui \
    ../OOPLab2/settingsdialog.ui \
    ../OOPLab2/timer.ui \
    ../OOPLab2/todolistwindow.ui
