#include "timer.h"
#include <QTime>
#include <QDebug>
#include "cesexception.h"
#include <QThread>

Timer::Timer(int ms, int startTime):
    msecs(ms),countDown(startTime)
{

}

void Timer::run() {
    startClock();
}

void Timer::startClock(){
    while(isRunning) {
        while(countDown > 0) {
            countDownFinished = false;
            while(isPaused) {
                if(!isRunning) return;
            }
            QTime oneSec = QTime::currentTime().addMSecs(msecs);
            while (QTime::currentTime() < oneSec) {
                if(clockReset || isPaused) break;
                if(!isRunning) return;
            }
            if(isPaused) continue;
            if(clockReset) {
                clockReset = false;
                continue;
            }
            emit tick();
            countDown--;
        }
        if(!countDownFinished) {
            emit end();
            countDownFinished = true;
        }
    }
}

void Timer::stop() {isRunning = false;}
void Timer::pause() { isPaused = true;}
void Timer::start() {isPaused = false;}
