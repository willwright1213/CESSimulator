#ifndef TIMER_H
#define TIMER_H

#include <QRunnable>
#include <QObject>


class Timer : public QObject, public QRunnable
{
    Q_OBJECT
    friend class TestCases;
    friend class CES;
    friend class DebugConsole;
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
    int countDown = 0;
    void startClock();

private slots:
    void stop();
    void start();
    void pause();
signals:
    void tick();
    void end();

};


#endif // TIMER_H
