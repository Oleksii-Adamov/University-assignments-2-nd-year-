#ifndef TODOLISTWINDOW_H
#define TODOLISTWINDOW_H

#include <QMainWindow>
#include<QtGui>

namespace Ui {
class ToDoListWindow;
}

class ToDoListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ToDoListWindow(QWidget *parent = nullptr);
    ~ToDoListWindow();
    void setList(QSharedPointer<QStringList> list);
private slots:
    void on_actionBack_triggered();

private:
    Ui::ToDoListWindow *ui;
    QStringListModel *m_list_model;
    QSharedPointer<QStringList> m_list;
    QWidget* m_parent;
};

#endif // TODOLISTWINDOW_H
