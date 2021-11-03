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
public slots:
  //  void onListItemDoubleClicked(QListWidgetItem*);
private slots:
    /*void on_pushButton_today_clicked();
    void on_pushButton_tomorrow_clicked();
    void on_pushButton_someday_clicked();*/
    void on_projectButton_clicked();
};
#endif // MAINWINDOW_H
