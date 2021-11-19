#include "mainwindow.h"
#include "ui_mainwindow.h"
/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    onStatus = false;
    reset = true;
    selectedTime = SIXTY;
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
    connect(ui->powerButton, &QPushButton::pressed, this, &MainWindow::powerButtonPress);
    connect(ui->timerButton, &QPushButton::pressed, this, &MainWindow::timeButtonPress);
    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::upButtonPress);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::downButtonPress);
    initialize();

}

MainWindow::~MainWindow()
{
    delete ui;
}



/**
 * @brief MainWindow::setClockLabel
 * Updates the clock label based on the selected time
 */
void MainWindow::setClockLabel() {
    QString clockLabel = QString::number(selectedTime * 20 + 20) + ":00";
    ui->clockLabel->setText(clockLabel);
    ui->clockLabel->setStyleSheet("color: #1b1b1b; font-size: 48pt;");
}

void MainWindow::setTimerLabels() {
    //clear all of the labels first:
    for(QLabel *l: qAsConst(timerLabels)) {
        l->setStyleSheet("color: #bfbfbf; font-size: 14pt;");
    }
    //set our selected label to "selected stylesheet"
    timerLabels[selectedTime]->setStyleSheet("color: #1b1b1b; font-size: 14pt; text-decoration: underline;");

}

void MainWindow::setTime(int newTime) {
    selectedTime = newTime;
    setClockLabel();
    setTimerLabels();
}

/* slots starts here */

/**
 * @brief MainWindow::powerOn
 */
void MainWindow::powerButtonPress() {
    onStatus = !onStatus;
    initialize();
}


void MainWindow::timeButtonPress() {
    setTime((selectedTime + 1) % 3);
}

void MainWindow::upButtonPress() {

}

void MainWindow::downButtonPress() {

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
void MainWindow::initialize() {
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
    setTime(SIXTY);
}
