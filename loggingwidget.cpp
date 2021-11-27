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
    ui->logs->addItem("cancel");
    ui->logs->addItem("");
    ui->logs->addItem(QString::asprintf(HEADER_FORMAT, "Time", "current", "wave", "freq","Date"));
    //holy grail of spacing
    ui->logs->addItem(QString::asprintf(ROW_FORMAT, "", "60", "200", "a", "1.5","21/09/05 HH:MM"));
    ui->logs->setSelectionMode(QAbstractItemView::NoSelection);
    selectItem(0);
    qDebug() << ui->logs->count();

}


LoggingWidget::~LoggingWidget()
{
    delete ui;
}

void LoggingWidget::selectItem(int i) {
    ui->logs->item(i)->setBackgroundColor(QColor::fromRgb(55,55,55));
    ui->logs->item(i)->setTextColor(QColor::fromRgb(191,191,191));
    selected = ui->logs->item(i);
    selectedIndex = i;
}

void LoggingWidget::unselectItem() {}
void LoggingWidget::refreshUi(){}

void LoggingWidget::moveUp() {
    if(selectedIndex <= 3)
        selectItem(0);
}

void LoggingWidget::moveDown() {
    if(selectedIndex < ui->logs->count() - 1)
        selectItem(selectedIndex + 1);
}
