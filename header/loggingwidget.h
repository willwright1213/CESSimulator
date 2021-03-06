/* ---------------------------------------------------------------------
 * File: loggingwidget.h
 * Published: 2021-12-10
 *
 * authors:
 *      William Wright
 *      Soorya Balaji
 *      Anwar Kulane
 *      Mahmoud sabaayon
 *
 * dependencies:
        <QWidget>
        <QListWidgetItem>
        recording.h

 * The LoggingWidget class is a visual GUI for the saved recordings handled by the CES.
 * ----------------------------------------------------------------------
 */
#ifndef LOGGINGWIDGET_H
#define LOGGINGWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include "recording.h"

#define HEADER_FORMAT "%1%2%3%4%5"
#define ROW_FORMAT  "%1%2%3%4%5%6"
#define HEADER_LINE "\n-------------------------------------------------------------"

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
    void addToLogs(Recording *);
};


#endif // LOGGINGWIDGET_H
