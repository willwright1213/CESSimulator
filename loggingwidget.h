#ifndef LOGGINGWIDGET_H
#define LOGGINGWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

#define HEADER_FORMAT "%-10s%-15s%-15s%-25s%s"
#define ROW_FORMAT  "%-2s%-13s%-18s%-17s%-12s%s"

namespace Ui {
class LoggingWidget;
}

class LoggingWidget : public QWidget
{
    Q_OBJECT
friend class CES;
friend class TestCases;
public:
    explicit LoggingWidget(QWidget *parent = nullptr);
    ~LoggingWidget();

private:
    Ui::LoggingWidget *ui;
    QListWidgetItem *selected;
    int selectedIndex;
    void selectItem(int i);
    void unselectItem();
    void refreshUi();
    void moveUp();
    void moveDown();
    void choose();
};


#endif // LOGGINGWIDGET_H
