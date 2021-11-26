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
    CES * getCES() const;
    QPushButton* powerButton() const;
    QPushButton* upButton() const;
    QPushButton* downButton() const;
    QPushButton* timerButton() const;
    QPushButton* waveButton() const;
    QPushButton* frequencyButton() const;
    QPushButton* lockButton() const;
    QPushButton*  clipperButton() const;
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
    void clipperButtonPress();
    void lockButtonPress();
    void logButtonPress();
    void recordButtonPress();
};
#endif // MAINWINDOW_H
