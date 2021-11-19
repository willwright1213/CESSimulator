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
    timerLabels.append(ui->twenty);
    timerLabels.append(ui->fourty);
    timerLabels.append(ui->sixty);
    initialize();
    connect(ui->powerButton, &QPushButton::pressed, this, &MainWindow::powerOn);
    connect(ui->timerButton, &QPushButton::pressed, this, &MainWindow::setTime);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::powerOn
 */
void MainWindow::powerOn() {
    onStatus = !onStatus;
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
    setTime();
    reset = !reset;
}

void MainWindow::setTime() {
    int nextTime;
    if(reset) {selectedTime = 1;}
    else {
        nextTime = (selectedTime + 1) % 3;
        QString selectedLabel = QString::number((selectedTime == TWENTY) ? 20 : (selectedTime == FOURTY) ? 40 : 60);
        QString nextLabel = QString::number((nextTime == TWENTY) ? 20 : (nextTime == FOURTY) ? 40 : 60);
        timerLabels[selectedTime]->setText
                ("<html><head/><body><p align=\"center\">"
                 "<span style=\" font-size:14pt; color:#bfbfbf;\">" +
                 selectedLabel +
                 "</span>""</p></body></html>");
        timerLabels[nextTime]->setText
                ("<html><head/><body><p align=\"center\">"
                 "<span style=\" font-size:14pt; color:#1b1b1b; text-decoration: underline;\">" +
                 QString::number((nextTime == TWENTY) ? 20 : (nextTime == FOURTY) ? 40 : 60) +
                 "</span>""</p></body></html>");
        selectedTime = nextTime;
        ui->clockLabel->setText
                ("<html><head/>"
                 "<body><p align=\"right\"><span style=\" font-size:48pt; color:#1b1b1b;\">"
                 + nextLabel + ":00"
                 "</span></p></body></html>"
                );
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
void MainWindow::initialize() {
    ui->screenWidget->setVisible(onStatus);
    ui->upButton->setEnabled(onStatus);
    ui->downButton->setEnabled(onStatus);
    ui->timerButton->setEnabled(onStatus);
    ui->lockButton->setEnabled(onStatus);
    ui->frequencyButton->setEnabled(onStatus);
    ui->waveFormButton->setEnabled(onStatus);
    ui->recordButton->setEnabled(onStatus);
    ui->logButton->setEnabled(onStatus);
    //initialize labels
    ui->clockLabel->setText("<html><head/><body><p align=\"right\"><span style=\" font-size:48pt; color:#1b1b1b;\">60:00</span></p></body></html>");
}
