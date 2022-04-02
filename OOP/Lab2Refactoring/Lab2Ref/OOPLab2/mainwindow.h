#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void callToDoList(QString file_name);
    //QStringList m_project_list;
    void add_button(QString name);
    QVBoxLayout* m_button_layout;
    QWidget* m_button_container;
public slots:
    void create_project(const QString& file_name);
    void delete_project_button(const QString& name);
    void edit_project_button(const QString& old_name, const QString& new_name);
private slots:
    void on_projectButton_clicked();
    void on_actionNew_triggered();
    void on_actionSettings_triggered();
};
#endif // MAINWINDOW_H
