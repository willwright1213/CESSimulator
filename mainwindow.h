#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include "ces.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *selectedScreen;
    CES *ces;


private slots:
    void powerButtonPress();
    void timeButtonPress();
    void upButtonPress();
    void downButtonPress();
    void waveButtonPress();
    void freqButtonPress();
    void toggleButtonPress();
};
#endif // MAINWINDOW_H
