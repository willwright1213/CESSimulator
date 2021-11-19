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
    void initialize();
    QVector<QLabel *> timerLabels;
    //void setTime(int);
    void setClockLabel();
    void setTimerLabels();

private slots:
    void powerOn();
    void setTime();
};
#endif // MAINWINDOW_H
