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

};
#endif // MAINWINDOW_H
