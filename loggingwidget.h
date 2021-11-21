#ifndef LOGGINGWIDGET_H
#define LOGGINGWIDGET_H

#include <QWidget>

namespace Ui {
class LoggingWidget;
}

class LoggingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoggingWidget(QWidget *parent = nullptr);
    ~LoggingWidget();

private:
    Ui::LoggingWidget *ui;
};

#endif // LOGGINGWIDGET_H
