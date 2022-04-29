#ifndef ADDTOTODOLIST_H
#define ADDTOTODOLIST_H

#include <QDialog>
#include "todolistmodel.h"

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
    friend class UnitTests;
public:
    explicit AddToToDoList(QWidget *parent = nullptr);
    ~AddToToDoList();
    /// current_index (index of selected element) is required for edit mode, to show current data of edited item
    explicit AddToToDoList(QWidget *parent, QSharedPointer<ToDoListModel> parent_model,
                           ToDoList::mode mode, int current_index = 0);
    Ui::AddToToDoList** get_ui();
private slots:
    void on_pushButtonCreate_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::AddToToDoList *ui;
    QSharedPointer<ToDoListModel> m_parent_model;
    ToDoList::mode m_mode;
    int m_current_index;
};

#endif // ADDTOTODOLIST_H
