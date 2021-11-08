#include "timer.h"
#include "ui_timer.h"
#include <QTimer>
#include "windows.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QAudioDevice>

Timer::Timer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timer)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    m_duration_of_pomodoro_in_seconds = 10;
    m_duration_of_break_in_seconds = 10;
    ui->label_state->setText("Work. Try not to be distracted");
    ui->label_time->setText(seconds_to_string(m_duration_of_pomodoro_in_seconds));
    ui->pushButton_stop_skip_start->setText("Stop");
    m_timer = new QTimer(this);
    qDebug() << connect(m_timer, SIGNAL(timeout()), this, SLOT(second_passed()));
    // counting seconds
    m_timer->start(1000);
    m_player = new QMediaPlayer(this);
    QAudioOutput* audio_output = new QAudioOutput(this);
    audio_output->setDevice(QMediaDevices::defaultAudioOutput());
    audio_output->setVolume(100);
    m_player->setAudioOutput(audio_output);
    // ":/Sounds/Timer-alarm"
    m_player->setSource(QUrl::fromLocalFile("./Twin-bell-alarm-clock.mp3"));
}

Timer::~Timer()
{
    delete ui;
}

void Timer::on_pushButton_stop_skip_start_clicked()
{
    if (m_is_timer_counting) {
        m_timer->stop();
        m_seconds_passed = 0;
        m_is_timer_counting = false;
        ui->label_time->setText(seconds_to_string(m_duration_of_pomodoro_in_seconds));
        if (m_is_break) { // skip
            m_is_break = false;
            ui->label_state->setText("Work. Try not to be distracted");
        }
        ui->pushButton_stop_skip_start->setText("Start");
    }
    else { // start
        m_timer->start();
        m_is_timer_counting = true;
    }
}

QString Timer::seconds_to_string(int seconds) {
    int minutes = seconds / 60;
    seconds = seconds % 60;
    QString min, sec;
    if (minutes < 10) min += '0';
    min += QString::number(minutes);
    if (seconds < 10) sec += '0';
    sec += QString::number(seconds);
    return min + ":" + sec;
}

void Timer::second_passed() {
    m_seconds_passed ++;
    if (!m_is_break && m_seconds_passed == m_duration_of_pomodoro_in_seconds) {
        ui->label_state->setText("Rest");
        m_is_break = true;
        m_player->play();
        m_seconds_passed = 0;
        ui->pushButton_stop_skip_start->setText("Skip");
        // emit signal to incerment number of pomodoros
        emit pomodoro_finished();
    }
    else if (m_is_break && m_seconds_passed == m_duration_of_break_in_seconds) {
        ui->label_state->setText("Work. Try not to be distracted");
        m_is_break = false;
        m_player->play();
        m_seconds_passed = 0;
        ui->pushButton_stop_skip_start->setText("Stop");
    }
    if (m_is_break) {
        ui->label_time->setText(seconds_to_string(m_duration_of_break_in_seconds - m_seconds_passed));
    }
    else {
        ui->label_time->setText(seconds_to_string(m_duration_of_pomodoro_in_seconds - m_seconds_passed));
    }
}
