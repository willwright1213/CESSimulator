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
    ces = new CES(ui->screenHolderWidget->layout());
    //initialize timerLabels vector

    //connect signals
    connect(ui->powerButton, &QPushButton::pressed, this, &MainWindow::powerButtonPress);
    connect(ui->timerButton, &QPushButton::pressed, this, &MainWindow::timeButtonPress);
    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::upButtonPress);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::downButtonPress);
    connect(ui->frequencyButton, &QPushButton::pressed, this, &MainWindow::freqButtonPress);
    connect(ui->waveFormButton, &QPushButton::pressed, this, &MainWindow::waveButtonPress);
    connect(ui->clipperButton, &QPushButton::pressed, this, &MainWindow::clipperButtonPress);
    connect(ui->lockButton, &QPushButton::pressed, this, &MainWindow::lockButtonPress);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QPushButton* MainWindow::powerButton() const {return ui->powerButton;}
QPushButton* MainWindow::upButton() const {return ui->upButton;}
QPushButton* MainWindow::downButton() const {return ui->downButton;}
QPushButton* MainWindow::timerButton() const {return ui->timerButton;}
QPushButton* MainWindow::waveButton() const {return ui->waveFormButton;}
QPushButton* MainWindow::frequencyButton() const {return ui->frequencyButton;}
QPushButton* MainWindow::lockButton() const {return ui->lockButton;}
QPushButton* MainWindow::clipperButton() const {return ui->clipperButton;}

CES * MainWindow::getCES() const {return ces;}
/* slots starts here */

/**
 * @brief MainWindow::powerOn
 */

/*!
 *
 * Sends a request to the CES to set the value of time.
 */
void MainWindow::timeButtonPress() {
    ces->setValue(TIME,(ces->getStartTime() + 1) % 3);
}

/*!
 *
 * Sends a request to the CES to increase the value of amperage.
 */
void MainWindow::upButtonPress() {
    ces->setValue(AMP, ces->getAmps() < 500 ? ces->getAmps() + 50 : 500);
}

/*!
 *
 * Sends a request to the CES to decrease the value of amperage.
 */
void MainWindow::downButtonPress() {
   ces->setValue(AMP, ces->getAmps() > 0 ? ces->getAmps() - 50 : 0);
}

/*!
 *
 * Sends a request to the CES to change the value of wave.
 */
void MainWindow::waveButtonPress() {
    ces->setValue(WAVE, (ces->getWave() + 1) % 3);
}

/*!
 *
 * Sends a request to the CES to decrease the value of frequency.
 */
void MainWindow::freqButtonPress() {
    ces->setValue(FREQ, (ces->getFreq() + 1) % 3);
}

/*!
 *
 * Sends a request to the CES to toggle the power status.
 */
void MainWindow::powerButtonPress() {
    ces->togglePower();
}

/*!
 *
 * Sends a request to the CES to toggle the clip status.
 */
void MainWindow::clipperButtonPress() {
    ces->toggleClipStatus();
}

/*!
 *
 * Sends a request to the CES to toggle the lock status.
 */
void MainWindow::lockButtonPress() {
    ces->toggleLock();
}
