#ifndef CES_H
#define CES_H

#include <QObject>
#include <QPointer>
#include <QLayout>
#include <QThread>
#include "timer.h"
#include "mainscreenwidget.h"
#include "loggingwidget.h"
#include "recording.h"

typedef enum {TWENTY, FOURTY, SIXTY} SelectedTime;
typedef enum {POINT_FIVE, SEVENTY_SEVEN, HUNDRED} selectedFrequency;
typedef enum {ALPHA, BETA, GAMMA} SelectedWave;

constexpr int MAX_AMPERAGE = 500;
constexpr int OVERLOAD_AMP_LIMIT = 700;
constexpr int MAX_TIME = 3600;

class CES : public QObject
{
    Q_OBJECT
    friend class MainScreenWidget;
    friend class TestCases;
public:
    explicit CES(QLayout *screen, QObject *parent = nullptr);
    ~CES();
private:
    bool isLocked = false;
    bool powerStatus = false;
    bool clipStatus = false;
    bool isRecording = false;

    int timer;
    int selectedTime;
    int selectedWave;
    int selectedFreq;
    int selectedAmp;

    float batteryLife = 100.00;

    MainScreenWidget *mainScreen;
    LoggingWidget *logScreen;
    QWidget* selectedScreen = nullptr;

    Timer *clockTimer;
    Timer *idleTimer;
    Timer *batteryTimer;
    Timer *contactTimer;

    QVector<Recording *> recordings;

    void setTime(int);
    void setStartTime(int);
    void setAmperage(int);
    void setFrequency(int);
    void setWave(int);
    void setScreen(QWidget *w = nullptr);
    void toggleClipStatus();
    void toggleLock();
    void toggleRecording();
    void showLogScreen();


signals:
    void updateTimeUi(int);
    void updateWaveUi(int);
    void updateFreqUi(int);
    void updateAmpUi(int);
    void stopClock();
    void startClock();
    void pauseClock();


public slots:

    void powerButtonPress();
    void timeButtonPress();
    void upButtonPress();
    void downButtonPress();
    void waveButtonPress();
    void freqButtonPress();
    void clipperButtonPress();
    void lockButtonPress();
    void logButtonPress();
    void recordButtonPress();
    void togglePower();

    //slots that handles timers
    void decrementClock();
    void decrementBattery();
    void shutDown();
    void bootUp();

};

#endif // CES_H
