#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT

public:
    explicit Stopwatch(QObject *parent = nullptr);
    ~Stopwatch();

    void start();
    void stop();
    void clear();
    void lap();
    double getElapsedTime() const;

signals:
    void timeUpdated(double time);
    void lapCompleted(int lapNumber, double lapTime);

private slots:
    void updateTime();

private:
    QTimer *_timer;
    double _elapsedTime;
    double _lastLapTime;
    int _lapCount;
};

#endif // STOPWATCH_H
