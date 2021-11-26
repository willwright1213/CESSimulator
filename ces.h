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
typedef enum {START_TIME, AMP, WAVE, FREQ, TIME} Setter;


class CES : public QObject
{
    Q_OBJECT
    friend class MainScreenWidget;
    friend class TestCases;
public:
    explicit CES(QLayout *screen, QObject *parent = nullptr);
    ~CES();
    typedef  void (CES::*FuncP)(int);
private:
    bool isLocked = false;
    bool powerStatus = false;
    bool clipStatus = false;
    QPointer<QWidget> selectedScreen = nullptr;
    uint16_t timer;
    uint8_t selectedTime;
    uint8_t selectedWave;
    uint8_t selectedFreq;
    uint16_t microAmps;

    Timer *clockTimer;

    MainScreenWidget *mainScreen;
    LoggingWidget *logScreen;
    QVector<void (CES::*)(uint16_t)> funcs;
    QVector<Recording *> recordings;
    void setTime(uint16_t);
    void setStartTime(uint16_t);
    void setAmperage(uint16_t);
    void setFrequency(uint16_t);
    void setWave(uint16_t);
    void setScreen(QWidget *w = nullptr);

public:
    uint8_t getStartTime() const &;
    uint16_t getTime() const &;
    uint8_t getWave() const &;
    uint8_t getFreq() const &;
    uint16_t getAmps() const &;
    bool getPowerStatus() const &;
    bool getClipStatus() const &;
    bool getlockStatus() const &;
    QPointer<QWidget> getSelectedScreen() const;
    MainScreenWidget * getMainScreen() const;


    void setValue(uint8_t, const uint16_t val);
    void togglePower();
    void toggleClipStatus();
    void toggleLock();
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
    void decrementClock();

};

#endif // CES_H
