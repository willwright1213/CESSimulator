#ifndef TIMER_H
#define TIMER_H

#include <QRunnable>
#include <QObject>


typedef enum {CLOCK, BATTERY, IDLE} TimerType;


class Timer : public QObject, public QRunnable
{
    Q_OBJECT
    friend class TestCases;
    friend class CES;
public:
    Timer(TimerType t);
    void run() override;
    void resetClock(int t) {clockReset = true; countDown = t;}
    void setTimer(int t) { if(!isPaused) clockReset = true; countDown = t;}
private:
    bool clockReset;
    bool isRunning = true;
    bool isPaused = true;
    TimerType type;
    int countDown = 0;
    void startClock();

private slots:
    void stop();
    void start();
    void pause();
signals:
    void reqDecrementClock();

};


#endif // TIMER_H
