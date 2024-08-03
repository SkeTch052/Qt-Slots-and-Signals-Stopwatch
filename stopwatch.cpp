#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject{parent}, _timer(new QTimer(this)), _elapsedTime(0.0), _lastLapTime(0.0), _lapCount(0)
{
    connect(_timer, &QTimer::timeout, this, &Stopwatch::updateTime);
    _timer->setInterval(100);
}

Stopwatch::~Stopwatch() {}

void Stopwatch::start()
{
    _elapsedTime = 0.0;
    _lastLapTime = 0.0;
    _lapCount = 0;
    emit timeUpdated(_elapsedTime);

    _timer->start();
}

void Stopwatch::stop()
{
    _timer->stop();
}

void Stopwatch::clear()
{
    _elapsedTime = 0.0;
    _lastLapTime = 0.0;
    _lapCount = 0;
    emit timeUpdated(_elapsedTime);
}

void Stopwatch::lap()
{
    _lapCount++;
    double lapTime = _elapsedTime - _lastLapTime;
    _lastLapTime = _elapsedTime;
    emit lapCompleted(_lapCount, lapTime);
}

double Stopwatch::getElapsedTime() const
{
    return _elapsedTime;
}

void Stopwatch::updateTime()
{
    _elapsedTime += 0.1;
    emit timeUpdated(_elapsedTime);
}
