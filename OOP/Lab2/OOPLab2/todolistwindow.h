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

signals:
    void delete_project_button(const QString& name);
    void edit_project_button(const QString& oldname, const QString& new_name);

public slots:
    void edit_project(const QString& new_name);

private slots:
    void on_actionBack_triggered();

    void on_pushButtonAdd_clicked();

    void on_pushButtonStartTimer_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonDelete_clicked();

    void on_actionDelete_this_project_triggered();

    void on_actionEditProject_triggered();

private:
    Ui::ToDoListWindow *ui;
    QString m_file_name;
    QSharedPointer<std::vector<ToDoListData>> m_data_list;
    bool m_is_deleted = false;
    QString m_project_name;
};

#endif // TODOLISTWINDOW_H
