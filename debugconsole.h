/* ---------------------------------------------------------------------
 * File: debugconsole.h
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
        <QSpinBox>
        <QPushButton>


 * Debug Console that allows the modification of values that wouldn't be possible
 * under normal use condition.
 * ----------------------------------------------------------------------
 */
#ifndef DEBUGCONSOLE_H
#define DEBUGCONSOLE_H

#include <QWidget>
#include "ces.h"
#include <QSpinBox>
#include <QPushButton>

namespace Ui {
class DebugConsole;
}

class DebugConsole : public QWidget
{
    Q_OBJECT

public:
    explicit DebugConsole(CES *, QWidget *parent = nullptr);
    ~DebugConsole();

private:
    CES * ces;
    Ui::DebugConsole *ui;
    int amperage = 100;
    double battery = 100.00;


private slots:
    void saveValues();
    void setAmp(int);
    void setBattery(double);
};

#endif // DEBUGCONSOLE_H
