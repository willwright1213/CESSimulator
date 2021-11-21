#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //blank sreen widget stuff
    ces = new CES;
    //initialize timerLabels vector
    timerLabels.append(ui->twenty);
    timerLabels.append(ui->fourty);
    timerLabels.append(ui->sixty);
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
    waveLabels.append(ui->w1);
    waveLabels.append(ui->w2);
    waveLabels.append(ui->w3);
    //initialize frequency vector
    freqLabels.append(ui->f1);
    freqLabels.append(ui->f2);
    freqLabels.append(ui->f3);
    //connect signals
    connect(ui->powerButton, &QPushButton::pressed, this, &MainWindow::powerButtonPress);
    connect(ui->timerButton, &QPushButton::pressed, this, &MainWindow::timeButtonPress);
    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::upButtonPress);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::downButtonPress);
    connect(ui->frequencyButton, &QPushButton::pressed, this, &MainWindow::freqButtonPress);
    connect(ui->waveFormButton, &QPushButton::pressed, this, &MainWindow::waveButtonPress);
    connect(ces, &CES::updateTimeUi, this, &MainWindow::updateTimeUi);
    connect(ces, &CES::updateWaveUi, this, &MainWindow::updateWaveUi);
    connect(ces, &CES::updateFreqUi, this, &MainWindow::updateFreqUi);
    connect(ces, &CES::updateAmpUi, this, &MainWindow::updateAmpUi);
    connect(ces, &CES::initializeUi, this, &MainWindow::initialize);
    initialize(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateTimeUi(int t) {
    //clear previous selected time
    for(int i=0; i < timerLabels.size(); ++i) {
        timerLabels[i]->setStyleSheet("color: #bfbfbf; font-size: 10pt;");
    }
    // set new selected time and update gui
    QString clockLabel = QString::number(t * 20 + 20) + ":00";
    ui->clockLabel->setText(clockLabel);
    ui->clockLabel->setStyleSheet("color: #1b1b1b; font-size: 48pt;");
    timerLabels[t]->setStyleSheet("color: #1b1b1b; font-size: 14pt; text-decoration: underline;");
}

void MainWindow::updateAmpUi(int a) {
    int count = a / 50;
    for(int i=0; i < bars.size(); ++i) {
        if(i < count) bars[i]->setStyleSheet("background:  #1b1b1b;");
        else bars[i]->setStyleSheet("border: 1px solid #1b1b1b;");
    }
}

void MainWindow::updateFreqUi(int f) {
    for(int i=0; i < freqLabels.size(); ++i) {
        freqLabels[i]->setStyleSheet("color: #bfbfbf; font-size: 10pt;");
    }
    freqLabels[f]->setStyleSheet("color: #1b1b1b; font-size: 10pt; text-decoration: underline;");
}

void MainWindow::updateWaveUi(int w) {
    for(int i=0; i < waveLabels.size(); ++i) {
        waveLabels[i]->setStyleSheet("color: #bfbfbf; font-size: 10pt;");
    }
    waveLabels[w]->setStyleSheet("color: #1b1b1b; font-size: 10pt; text-decoration: underline;");
}

/* slots starts here */

/**
 * @brief MainWindow::powerOn
 */
void MainWindow::powerButtonPress() {
    ces->togglePower();
}


void MainWindow::timeButtonPress() {
    ces->setTime((ces->time() + 1) % 3);
}

void MainWindow::upButtonPress() {
    ces->setAmperage(ces->amps() < 500 ? ces->amps() + 50 : 500);
}

void MainWindow::downButtonPress() {
    ces->setAmperage(ces->amps() > 0 ? ces->amps() - 50 : 0);
}

void MainWindow::waveButtonPress() {
    ces->setWave((ces->wave() + 1) % 3);
}

void MainWindow::freqButtonPress() {
    ces->setFrequency((ces->freq() + 1) % 3);
}

/**
 * void MainWindow::setTime(int nextTime) {
    QString previousLabel = QString::number((selectedTime == TWENTY) ? 20 : (selectedTime == FOURTY) ? 40 : 60);
    QString selectedLabel = QString::number((nextTime == TWENTY) ? 20 : (nextTime == FOURTY) ? 40 : 60);
    timerLabels[nextTime]->setText
            ("<html><head/><body><p align=\"center\">"
             "<span style=\" font-size:14pt; color:#1b1b1b; text-decoration: underline;\">" +
             selectedLabel +
             "</span>""</p></body></html>");
    ui->clockLabel->setText
            ("<html><head/>"
             "<body><p align=\"right\"><span style=\" font-size:48pt; color:#1b1b1b;\">"
             + selectedLabel + ":00"
             "</span></p></body></html>"
            );
    //selectedTime = nextTime;
}
**/

/**
 * @brief MainWindow::initialize
 */
void MainWindow::initialize(bool onStatus) {
    qDebug() << "called";
    ui->screenWidget->setVisible(onStatus);
    ui->blankScreenWidget->setVisible(!onStatus);
    //Disable/Enable buttons
    ui->upButton->setEnabled(onStatus);
    ui->downButton->setEnabled(onStatus);
    ui->timerButton->setEnabled(onStatus);
    ui->lockButton->setEnabled(onStatus);
    ui->frequencyButton->setEnabled(onStatus);
    ui->waveFormButton->setEnabled(onStatus);
    ui->recordButton->setEnabled(onStatus);
    ui->logButton->setEnabled(onStatus);
}
