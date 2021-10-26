#ifndef TODOLISTWINDOW_H
#define TODOLISTWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "todolistdata.h"
#include <vector>

namespace Ui {
class ToDoListWindow;
}

class ToDoListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ToDoListWindow(QWidget *parent = nullptr);
    ~ToDoListWindow();
    //void setList(QSharedPointer<QStringList> list);
    //void setList(QSharedPointer<QList<ToDoListData>> list);
    //void setList(QSharedPointer<std::vector<ToDoListData>> list);
    ToDoListWindow(QString file_name, QSharedPointer<std::vector<ToDoListData>> list, QWidget *parent = nullptr);
private slots:
    void on_actionBack_triggered();

    void on_pushButtonAdd_clicked();

    void on_pushButtonStartTimer_clicked();

    void on_pushButtonEdit_clicked();

private:
    Ui::ToDoListWindow *ui;
    QString m_file_name;
    QSharedPointer<std::vector<ToDoListData>> m_data_list;
};

#endif // TODOLISTWINDOW_H
