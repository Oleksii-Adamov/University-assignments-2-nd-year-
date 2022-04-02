#include "mainwindow.h"
#include "todolistdata.h"
#include <QApplication>
#include <QTest>
#include "test_addtotodolist.h"

int main(int argc, char *argv[])
{
    //std::freopen("D:/University/Programming-labs-2nd-year/OOP/Lab2/OOPLab2/testing.log", "w", stdout);
    QApplication a(argc, argv);
    qRegisterMetaType<ToDoListData>();
    //QTest::qExec(new Test_AddToToDoList, argc, argv);
    //std::fclose(stdout);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
