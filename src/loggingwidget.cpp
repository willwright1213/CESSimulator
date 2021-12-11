#include "loggingwidget.h"
#include "ui_loggingwidget.h"
#include <QStringListModel>
#include <QDebug>
#include <QDateTime>

LoggingWidget::LoggingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoggingWidget)
{
    ui->setupUi(this);
    selectedIndex = 0;
    ui->logs->addItem("cancel");
    ui->logs->addItem("");
    ui->logs->addItem(QString(HEADER_FORMAT).arg("Time", -10).arg("current", -15).arg("wave", -15).arg("freq", -25).arg("Date") + HEADER_LINE);
   // ui->logs->addItem(QString::asprintf(HEADER_FORMAT, "Time", "current", "wave", "freq","Date")+HEADER_LINE);
    //holy grail of spacing
    ui->logs->setSelectionMode(QAbstractItemView::NoSelection);
    selectItem(0);
    qDebug() << ui->logs->count();

}


LoggingWidget::~LoggingWidget()
{
    delete ui;
}

void LoggingWidget::selectItem(int i) {
    ui->logs->item(selectedIndex)->setBackgroundColor(QColor::fromRgb(202,196,196));
    ui->logs->item(selectedIndex)->setTextColor(QColor::fromRgb(27,27,27));
    ui->logs->item(i)->setBackgroundColor(QColor::fromRgb(55,55,55));
    ui->logs->item(i)->setTextColor(QColor::fromRgb(191,191,191));
    selected = ui->logs->item(i);
    selectedIndex = i;
}

void LoggingWidget::unselectItem() {}
void LoggingWidget::refreshUi(){}

void LoggingWidget::moveUp() {
    if(ui->logs->count() < 4) return;
    if(ui->logs->count() < 4) return;
    if(selectedIndex == 3) selectItem(0);
    else selectItem(selectedIndex == 0 ? ui->logs->count() - 1 : selectedIndex - 1);
}

void LoggingWidget::moveDown() {
    if (selectedIndex == 0) selectItem(ui->logs->count() < 4 ? 0: 3);
    else selectItem((selectedIndex + 1) % ui->logs->count());
}

void LoggingWidget::addToLogs(Recording * r) {

    QString timeString = QString::number((r->selectedTime + 1) * 20);
    QString currentString = QString::number(r->selectedAmps).rightJustified(3, '0');
    QString waveString = QString(r->selectedWave == 0 ? "a" : r->selectedWave == 1 ? "B" : "y");
    QString freqString = QString(r->selectedFreq == 0 ? "0.5" : r->selectedFreq == 1 ? "077" : "100");
    ui->logs->addItem(QString("%1%2%3%4%5%6").arg("", -2).arg(timeString, -13).arg(currentString, -18).arg(waveString, -17).arg(freqString, -19).arg(r->date));
}
