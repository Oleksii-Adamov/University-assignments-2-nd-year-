QT       += core gui
QT       += multimedia
QT       += core testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addnewprojectdialog.cpp \
    addtotodolist.cpp \
    filepath.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    timer.cpp \
    todolistdata.cpp \
    todolistmodel.cpp \
    todolistwindow.cpp

HEADERS += \
    addnewprojectdialog.h \
    addtotodolist.h \
    filepath.h \
    mainwindow.h \
    settingsdialog.h \
    timer.h \
    todolistdata.h \
    todolistmodel.h \
    todolistwindow.h

FORMS += \
    addnewprojectdialog.ui \
    addtotodolist.ui \
    mainwindow.ui \
    settingsdialog.ui \
    timer.ui \
    todolistwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
