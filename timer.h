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
    Timer(int ms, int startTime = 0);
    void run() override;
    void setTimer(int t) { if(!isPaused) clockReset = true; countDown = t;}
private:
    bool clockReset = false;
    bool isRunning = true;
    bool isPaused = true;
    bool countDownFinished = true;
    int msecs;
    TimerType type;
    int countDown = 0;
    void startClock();
    void idleCheck();

private slots:
    void stop();
    void start();
    void pause();
signals:
    void reqDecrementClock();
    void tick();
    void end();

};


#endif // TIMER_H
