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

public:
    explicit MainScreenWidget(QWidget *parent = nullptr);
    QVector<QLabel *> timerLabels;
    QVector<QLabel *> freqLabels;
    QVector<QLabel *> waveLabels;
    QVector<QWidget *> bars;
    QLabel *clockLabel() const;
    ~MainScreenWidget();

public slots:
    void updateTimeUi(int);
    void updateWaveUi(int);
    void updateFreqUi(int);
    void updateAmpUi(int);
    void updateClock(int);
    void showLock(bool);

private:
    Ui::MainScreenWidget *ui;
};

#endif // MAINSCREENWIDGET_H
