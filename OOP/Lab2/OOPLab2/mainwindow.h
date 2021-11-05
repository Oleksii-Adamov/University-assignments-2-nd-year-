#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
public slots:
    void create_project(QString file_name);

private slots:
    void on_projectButton_clicked();
    void on_actionNew_triggered();
    void on_actionDelete_triggered();
};
#endif // MAINWINDOW_H
