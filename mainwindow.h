#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef enum {TWENTY, FOURTY, SIXTY} SelectedTime;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool onStatus;
    bool reset;
    int selectedTime;
    double amperage;
    QVector<QLabel *> timerLabels;
    QVector<QWidget *> bars;
    void initialize();
    void setClockLabel();
    void setTimerLabels();
    void refreshCSS(QWidget *);
    void setTime(int);
    void setAmperage(double);

private slots:
    void powerButtonPress();
    void timeButtonPress();
    void upButtonPress();
    void downButtonPress();
};
#endif // MAINWINDOW_H
