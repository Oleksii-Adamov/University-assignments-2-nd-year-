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
    void setList(QSharedPointer<std::vector<ToDoListData>> list);
private slots:
    void on_actionBack_triggered();

    void on_pushButtonAdd_clicked();

    void on_pushButtonStartTimer_clicked();

private:
    Ui::ToDoListWindow *ui;
    //QStringListModel *m_list_model;
    //QStringList m_string_list;
    //QSharedPointer<QList<ToDoListData>> m_data_list;
    QSharedPointer<std::vector<ToDoListData>> m_data_list;
    //QWidget* m_parent;
};

#endif // TODOLISTWINDOW_H
