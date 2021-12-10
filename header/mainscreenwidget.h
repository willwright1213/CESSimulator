/* ---------------------------------------------------------------------
 * File: mainscreenwidget.h
 * Published: 2021-12-10
 *
 * authors:
 *      William Wright
 *      Soorya Balaji
 *      Anwar Kulane
 *      Mahmoud sabaayon
 *
 * dependencies:
        <QWidget>
        <QLabel>
        <QVector>

 * The LoggingWidget class is a visual GUI for the therapy session and is the screen to show when power is set to on.
 * It shows the set values and the time remaining for the therapy and handles functions that update the UI.
 * ----------------------------------------------------------------------
 */
#ifndef MAINSCREENWIDGET_H
#define MAINSCREENWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVector>

namespace Ui {
class MainScreenWidget;
}

class MainScreenWidget : public QWidget
{
    Q_OBJECT
friend class TestCases;
friend class CES;
private:
    explicit MainScreenWidget(QWidget *parent = nullptr);
    QVector<QLabel *> timerLabels;
    QVector<QLabel *> freqLabels;
    QVector<QLabel *> waveLabels;
    QVector<QWidget *> bars;


    ~MainScreenWidget();

public:
    void updateTimeUi(int);
    void updateWaveUi(int);
    void updateFreqUi(int);
    void updateAmpUi(int);
    void updateClock(int);
    void showLock(bool);
    void showRecordIcon(bool);
    void updateBatteryLifeUi(int);
    void updateBatteryIconUi(int);

private:
    Ui::MainScreenWidget *ui;
    //for test purpose
    QLabel *clockLabel() const;
    QWidget *lockIcon() const;
    QWidget *recIcon() const;
};

#endif // MAINSCREENWIDGET_H
