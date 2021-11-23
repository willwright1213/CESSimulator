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
    connect(ui->toggleButton, &QPushButton::pressed, this, &MainWindow::toggleButtonPress);

}

MainWindow::~MainWindow()
{
    delete ui;
}



/* slots starts here */

/**
 * @brief MainWindow::powerOn
 */
void MainWindow::powerButtonPress() {
    ces->togglePower();
}


void MainWindow::timeButtonPress() {
    ces->changeValue(TIME,(ces->time() + 1) % 3);
}

void MainWindow::upButtonPress() {
    ces->changeValue(AMP, ces->amps() < 500 ? ces->amps() + 50 : 500);
}

void MainWindow::downButtonPress() {
   ces->changeValue(AMP, ces->amps() > 0 ? ces->amps() - 50 : 0);
}

void MainWindow::waveButtonPress() {
    ces->changeValue(WAVE, (ces->wave() + 1) % 3);
}

void MainWindow::freqButtonPress() {
    ces->changeValue(FREQ, (ces->freq() + 1) % 3);
}


void MainWindow::toggleButtonPress() {
    ces->toggleClipStatus();
}

