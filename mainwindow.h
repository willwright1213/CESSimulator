/* ---------------------------------------------------------------------
 * File: mainwindow.h
 * Published: 2021-12-10
 *
 * authors:
 *      William Wright
 *      Soorya Balaji
 *      Anwar Kulane
 *      Mahmoud sabaayon
 *
 * dependencies:
        <QMainWindow>
        <QPushButton>
        <QVector>
        <QLabel>
        ces.h

 * The MainWindow class represents the physical casing of the simulation. Its functionality
 * provide an interactive GUI to the user and send input to the CES object.
 * ----------------------------------------------------------------------
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVector>
#include <QLabel>
#include "ces.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
friend class TestCases;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QWidget *selectedScreen;
    CES *ces;


    /* Below is only necessary for testing purposes */

    QPushButton* powerButton() const;
    QPushButton* upButton() const;
    QPushButton* downButton() const;
    QPushButton* timerButton() const;
    QPushButton* waveButton() const;
    QPushButton* frequencyButton() const;
    QPushButton* lockButton() const;
    QPushButton*  clipperButton() const;
    QPushButton* recordButton() const;
    QPushButton* logButton() const;

};
#endif // MAINWINDOW_H
