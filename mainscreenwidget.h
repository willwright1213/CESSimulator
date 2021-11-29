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

public slots:
    void updateTimeUi(int);
    void updateWaveUi(int);
    void updateFreqUi(int);
    void updateAmpUi(int);
    void updateClock(int);
    void showLock(bool);
    void showRecordIcon(bool);


private:
    Ui::MainScreenWidget *ui;
    //for test purpose
    QLabel *clockLabel() const;
    QWidget *lockIcon() const;
    QWidget *recIcon() const;
};

#endif // MAINSCREENWIDGET_H
