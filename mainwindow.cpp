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

    //connect signals
    connect(ui->powerButton, &QPushButton::pressed, this, &MainWindow::powerButtonPress);
    connect(ui->timerButton, &QPushButton::pressed, this, &MainWindow::timeButtonPress);
    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::upButtonPress);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::downButtonPress);
    connect(ui->frequencyButton, &QPushButton::pressed, this, &MainWindow::freqButtonPress);
    connect(ui->waveFormButton, &QPushButton::pressed, this, &MainWindow::waveButtonPress);
    connect(ces, &CES::unlockButtons, this, &MainWindow::unlockButtons);
    connect(ces, &CES::loadScreen, this, &MainWindow::loadScreen);
    connect(ces, &CES::selectScreen, this, &MainWindow::selectScreen);

    ces->loadScreens();
    unlockButtons(false);

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

void MainWindow::loadScreen(QWidget *w) {
    ui->screenHolderWidget->layout()->addWidget(w);
    w->hide();
}

void MainWindow::selectScreen(QWidget *w) {
    if(w == nullptr) {
        if(selectedScreen) selectedScreen->hide();
    }
    else {
        if(selectedScreen) selectedScreen->hide();
        selectedScreen = w;
        selectedScreen->show();
    }
}

void MainWindow::unlockButtons(bool onStatus) {
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
