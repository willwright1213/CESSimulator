#include "mainscreenwidget.h"
#include "ui_mainscreenwidget.h"

MainScreenWidget::MainScreenWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainScreenWidget)
{
    ui->setupUi(this);
    timerLabels.append(ui->t1);
    timerLabels.append(ui->t2);
    timerLabels.append(ui->t3);
    //initialize bars vector
    bars.append(ui->bar1);
    bars.append(ui->bar2);
    bars.append(ui->bar3);
    bars.append(ui->bar4);
    bars.append(ui->bar5);
    bars.append(ui->bar6);
    bars.append(ui->bar7);
    bars.append(ui->bar8);
    bars.append(ui->bar9);
    bars.append(ui->bar10);
    //initialze wave vector
    waveLabels.append(ui->wave1);
    waveLabels.append(ui->wave2);
    waveLabels.append(ui->wave3);
    //initialize frequency vector
    freqLabels.append(ui->freq1);
    freqLabels.append(ui->freq2);
    freqLabels.append(ui->freq3);
}

QLabel * MainScreenWidget::clockLabel() const {
    return ui->clockLabel;
}

void MainScreenWidget::updateTimeUi(int t) {
    int secs = (t * 20 + 20) * 60;
    for(int i=0; i < timerLabels.size(); ++i) {
        timerLabels[i]->setStyleSheet("color: #bfbfbf; font-size: 10pt;");
    }
    // set new selected time and update gui
    timerLabels[t]->setStyleSheet("color: #1b1b1b; font-size: 14pt; text-decoration: underline;");
    updateClock(secs);

}

void MainScreenWidget::updateClock(int secs) {
    QString mString = QString::number(secs / 60).rightJustified(2, '0');
    QString sString = QString::number(secs % 60).rightJustified(2, '0');
    ui->clockLabel->setText(mString + ":" + sString);
}

void MainScreenWidget::updateAmpUi(int a) {
    int count = a / 50;
    for(int i=0; i < bars.size(); ++i) {
        if(i < count)
            bars[i]->setStyleSheet("background:  #1b1b1b;");
        else
            bars[i]->setStyleSheet("border: 1px solid #1b1b1b;");
    }
}

void MainScreenWidget::updateFreqUi(int f) {
    for(int i=0; i < freqLabels.size(); ++i) {
        freqLabels[i]->setStyleSheet("color: #bfbfbf; font-size: 10pt;");
    }
    freqLabels[f]->setStyleSheet("color: #1b1b1b; font-size: 10pt; text-decoration: underline;");
}

void MainScreenWidget::updateWaveUi(int w) {
    for(int i=0; i < waveLabels.size(); ++i) {
        waveLabels[i]->setStyleSheet("color: #bfbfbf; font-size: 10pt;");
    }
    waveLabels[w]->setStyleSheet("color: #1b1b1b; font-size: 10pt; text-decoration: underline;");
}

void MainScreenWidget::showLock(bool show) {
    if(show)
        ui->lockIcon->setStyleSheet("border-image: url(:/images/icons8-lock-24.png)");
    else
        ui->lockIcon->setStyleSheet("");
}

MainScreenWidget::~MainScreenWidget()
{
    delete ui;
}
