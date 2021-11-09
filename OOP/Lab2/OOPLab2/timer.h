#ifndef TIMER_H
#define TIMER_H

#include <QDialog>
#include <QMediaPlayer>

namespace Ui {
class Timer;
}

class Timer : public QDialog
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = nullptr);
    ~Timer();

signals:
    void pomodoro_finished();

private slots:
    void on_pushButton_stop_skip_start_clicked();
    void second_passed();

private:
    Ui::Timer *ui;
    int m_duration_of_pomodoro_in_seconds;
    int m_duration_of_break_in_seconds;
    int m_seconds_passed = 0;
    QTimer* m_timer;
    bool m_is_break = false;
    bool m_is_timer_counting = true;
    QString seconds_to_string(int seconds);
    QMediaPlayer* m_player;
};

#endif // TIMER_H
