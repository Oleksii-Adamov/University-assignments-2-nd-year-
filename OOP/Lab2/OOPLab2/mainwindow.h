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
public slots:
  //  void onListItemDoubleClicked(QListWidgetItem*);
private slots:
    void on_pushButton_today_clicked();
    void on_pushButton_tomorrow_clicked();
    void on_pushButton_all_tasks_clicked();
};
#endif // MAINWINDOW_H
