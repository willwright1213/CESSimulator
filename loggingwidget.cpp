#include "loggingwidget.h"
#include "ui_loggingwidget.h"
#include <QStringListModel>

LoggingWidget::LoggingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoggingWidget)
{
    ui->setupUi(this);
    ui->logs->addItem("cancel\n");
    ui->logs->addItem(QString::asprintf("%-10s%-15s%-15s%-25s%s", "Time", "current", "wave", "freq","Date"));
    //holy grail of spacing
    ui->logs->addItem(QString::asprintf("%-2s%-13s%-18s%-17s%-12s%s", "", "60", "200", "a", "1.5","21/09/05 HH:MM"));
    ui->logs->setSelectionMode(QAbstractItemView::NoSelection);
}

LoggingWidget::~LoggingWidget()
{
    delete ui;
}
