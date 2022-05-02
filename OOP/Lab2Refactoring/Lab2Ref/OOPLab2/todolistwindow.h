#ifndef TODOLISTWINDOW_H
#define TODOLISTWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "todolistdata.h"
#include <vector>
#include "todolistmodel.h"
namespace Ui {
class ToDoListWindow;
}

class ToDoListWindow : public QMainWindow
{
    Q_OBJECT
    friend class UnitTests;
public:
    explicit ToDoListWindow(QWidget *parent = nullptr);
    ~ToDoListWindow();
    ToDoListWindow(QString file_name, QWidget *parent = nullptr);

signals:
    void delete_project_button(const QString& name);
    void edit_project_button(const QString& oldname, const QString& new_name);

public slots:
    void edit_project(const QString& new_name);
    void increment_pomodoros();

private slots:
    void on_actionBack_triggered();

    void on_pushButtonAdd_clicked();

    void on_pushButtonStartTimer_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonDelete_clicked();

    void on_actionDelete_this_project_triggered();

    void on_actionEditProject_triggered();

    void on_pushButton_task_completed_clicked();

    void on_actionSettings_triggered();

private:
    Ui::ToDoListWindow *ui;
    /// eg. ./UserProjects/Today
    QString m_file_name;
    QSharedPointer<ToDoListModel> model;
    bool m_is_deleted = false;
    /// Today
    QString m_project_name;
};

#endif // TODOLISTWINDOW_H
