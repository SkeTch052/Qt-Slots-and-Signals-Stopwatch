#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _stopwatch(new Stopwatch(this))
{
    ui->setupUi(this);

    setWindowTitle("Секундомер");

    ui->pb_start_stop->setText("Старт");
    ui->pb_start_stop->setCheckable(true);
    ui->pb_clear->setText("Очистить");
    ui->pb_lap->setText("Круг");
    ui->pb_lap->setEnabled(false);

    connect(_stopwatch, &Stopwatch::timeUpdated, this, &MainWindow::updateTimerDisplay);
    connect(_stopwatch, &Stopwatch::lapCompleted, this, &MainWindow::addLapToLog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_start_stop_clicked()
{
    if (ui->pb_start_stop->isChecked()) {
        ui->pb_start_stop->setText("Стоп");
        _stopwatch->start();
        ui->pb_lap->setEnabled(true);
    } else {
        ui->pb_start_stop->setText("Старт");
        _stopwatch->stop();
        ui->pb_lap->setEnabled(false);

        QString text = ui->textb_log->toPlainText();
        QStringList lines = text.split('\n');
        QString lastLine = lines.last();
        if (lastLine.startsWith("Круг")) {
            ui->textb_log->append("===============");
        }
    }
}

void MainWindow::on_pb_clear_clicked()
{
    _stopwatch->clear();
    ui->textb_log->clear();
}

void MainWindow::on_pb_lap_clicked()
{
    _stopwatch->lap();
}

void MainWindow::updateTimerDisplay(double time)
{
    QString timeString = QString::number(time, 'f', 1);
    ui->lb_timer->setText(timeString + " сек");
}

void MainWindow::addLapToLog(int lapNumber, double lapTime)
{
    QString lapString = QString("Круг %1, время: %2 сек").arg(lapNumber).arg(lapTime, 0, 'f', 1);
    ui->textb_log->append(lapString);
}
