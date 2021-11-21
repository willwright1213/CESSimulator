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
    if(w == nullptr) {
        if(selectedScreen != nullptr) {
            qDebug() << "here";
            selectedScreen->hide();
        }
    }
    else if(!selectedScreen){
        selectedScreen = w;
        ui->screenHolderWidget->layout()->addWidget(selectedScreen);
    }
    else {
        selectedScreen->show();
    }
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
