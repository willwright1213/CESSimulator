#include "timer.h"
#include <QTime>
#include <QDebug>
#include "cesexception.h"
#include <QThread>

Timer::Timer(TimerType t):
    type(t)
{

}

void Timer::run() {
    if(type == CLOCK)
        startClock();
}

void Timer::startClock(){
    while(isRunning) {
        while(countDown > 0) {
            while(isPaused) {
                if(!isRunning) return;
            }
            QTime oneSec = QTime::currentTime().addMSecs(10);
            while (QTime::currentTime() < oneSec) {
                if(clockReset || isPaused) break;
                if(!isRunning) return;
            }
            if(isPaused) continue;
            if(clockReset) {
                clockReset = false;
                continue;
            }
            try {
                emit reqDecrementClock();
            } catch(IllegalValueException &e) {
                qDebug() << "hey";
                return;
            }
        }
    }
}

void Timer::stop() {isRunning = false;}
void Timer::pause() { isPaused = true;}
void Timer::start() {isPaused = false;}
