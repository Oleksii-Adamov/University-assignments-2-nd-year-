#include "mainwindow.h"
#include "todolistdata.h"
#include <QApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<ToDoListData>();
    ToDoListData variant_data(0, "as", 0, 0);
    QVariant variant = QVariant::fromValue(variant_data);
    qDebug() << variant.typeName();
    ToDoListData data_from_variant = variant.value<ToDoListData>();
    qDebug() << data_from_variant.ToQString();
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
