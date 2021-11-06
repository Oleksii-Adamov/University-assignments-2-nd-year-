#include "timer.h"
#include "ui_timer.h"
#include <QTimer>

Timer::Timer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);
    ui->label_state->setText("Work. Try not to be distracted");
    m_duration_of_pomodoro_in_seconds = 10;
    m_duration_of_break_in_seconds = 10;
    m_timer = new QTimer(this);
    qDebug() << connect(m_timer, SIGNAL(timeout()), this, SLOT(second_passed()));
    // counting seconds
    m_timer->start(1000);
}

Timer::~Timer()
{
    delete ui;
}

void Timer::on_pushButton_stop_skip_clicked()
{

}

QString Timer::seconds_to_string(int seconds) {
    int minutes = seconds / 60;
    seconds = seconds % 60;
    return QString::number(minutes) + ":" + QString::number(seconds);
}

void Timer::second_passed() {
    m_seconds_passed ++;
    if (!m_is_break && m_seconds_passed == m_duration_of_pomodoro_in_seconds) {
        ui->label_state->setText("Rest");
        m_is_break = true;
        m_seconds_passed = 0;
    }
    else if (m_is_break && m_seconds_passed == m_duration_of_break_in_seconds) {
        ui->label_state->setText("Work. Try not to be distracted");
        m_is_break = false;
        m_seconds_passed = 0;
    }
    if (m_is_break) {
        ui->label_time->setText(seconds_to_string(m_duration_of_break_in_seconds - m_seconds_passed));
    }
    else {
        ui->label_time->setText(seconds_to_string(m_duration_of_pomodoro_in_seconds - m_seconds_passed));
    }
}
