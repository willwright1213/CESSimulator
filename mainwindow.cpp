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
    connect(ui->powerButton, &QPushButton::pressed, ces, &CES::powerButtonPress);
    connect(ui->timerButton, &QPushButton::pressed, ces, &CES::timeButtonPress);
    connect(ui->upButton, &QPushButton::pressed, ces, &CES::upButtonPress);
    connect(ui->downButton, &QPushButton::pressed, ces, &CES::downButtonPress);
    connect(ui->frequencyButton, &QPushButton::pressed, ces, &CES::freqButtonPress);
    connect(ui->waveFormButton, &QPushButton::pressed, ces, &CES::waveButtonPress);
    connect(ui->clipperButton, &QPushButton::pressed, ces, &CES::clipperButtonPress);
    connect(ui->lockButton, &QPushButton::pressed, ces, &CES::lockButtonPress);
    connect(ui->logButton, &QPushButton::pressed, ces, &CES::logButtonPress);
    connect(ui->recordButton, &QPushButton::pressed, ces, &CES::recordButtonPress);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ces;
}

QPushButton* MainWindow::powerButton() const {return ui->powerButton;}
QPushButton* MainWindow::upButton() const {return ui->upButton;}
QPushButton* MainWindow::downButton() const {return ui->downButton;}
QPushButton* MainWindow::timerButton() const {return ui->timerButton;}
QPushButton* MainWindow::waveButton() const {return ui->waveFormButton;}
QPushButton* MainWindow::frequencyButton() const {return ui->frequencyButton;}
QPushButton* MainWindow::lockButton() const {return ui->lockButton;}
QPushButton* MainWindow::clipperButton() const {return ui->clipperButton;}
QPushButton* MainWindow::recordButton() const {return ui->recordButton;}
QPushButton* MainWindow::logButton() const {return ui->logButton;}
/* slots starts here */

/**
 * @brief MainWindow::powerOn
 */

/*!
 *
 * Sends a request to the CES to set the value of time.
 */

