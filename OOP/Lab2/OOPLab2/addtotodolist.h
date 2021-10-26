#ifndef ADDTOTODOLIST_H
#define ADDTOTODOLIST_H

#include <QDialog>
#include "todolistdata.h"
#include <QListWidget>
namespace ToDoList {
    enum mode {
        Add,
        Edit
    };
}
namespace Ui {
class AddToToDoList;
}

class AddToToDoList : public QDialog
{
    Q_OBJECT

public:
    explicit AddToToDoList(QWidget *parent = nullptr);
    ~AddToToDoList();
    explicit AddToToDoList(QWidget *parent, QSharedPointer<std::vector<ToDoListData>> parent_data_list, QListWidget* parent_list_widget,
                           ToDoList::mode mode);
private slots:
    void on_pushButtonCreate_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::AddToToDoList *ui;
    QSharedPointer<std::vector<ToDoListData>> m_parent_data_list;
    QListWidget* m_parent_list_widget;
    ToDoList::mode m_mode;
};

#endif // ADDTOTODOLIST_H
