#include "debugconsole.h"
#include "ui_debugconsole.h"

DebugConsole::DebugConsole(CES *ces, QWidget *parent) :
    QWidget(parent),
    ces(ces),
    ui(new Ui::DebugConsole)
{
    ui->setupUi(this);
    connect(ui->ampSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &DebugConsole::setAmp);
    connect(ui->batterySpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &DebugConsole::setBattery);
    connect(ui->saveButton, &QPushButton::pressed, this, &DebugConsole::saveValues);
}

DebugConsole::~DebugConsole()
{
    delete ui;
}


void DebugConsole::saveValues() {
    ces->setAmperage(amperage);
    ces->batteryLife = battery;
    ces->mainScreen->updateBatteryIconUi(ces->batteryLife/20);
    ces->mainScreen->updateBatteryLifeUi((int)ces->batteryLife);
    ces->batteryTimer->setTimer((ces->batteryLife * 2) - 4);
    this->hide();
}

void DebugConsole::setAmp(int i){ amperage = i;}
void DebugConsole::setBattery(double d) {battery = d;}
