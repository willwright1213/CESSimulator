#include "loggingwidget.h"
#include "ui_loggingwidget.h"

LoggingWidget::LoggingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoggingWidget)
{
    ui->setupUi(this);
}

LoggingWidget::~LoggingWidget()
{
    delete ui;
}
