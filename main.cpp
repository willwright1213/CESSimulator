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
        <QApplication>
        <QThreadPool>
        mainwindow.h
        testcases.h

 * The CES Simulator simulates the alpha-stim. It provides functionalities
 * described in the alpha-stim manual and then more.
 *
 * There are two modes as how this program can run.
 *
 * The first mode is the "normal" mode where a GUI is provided and where the user can interact with the
 * GUI and play along the simulation.
 *
 * The second mode is the "test" mode where no GUI is provided and where the tests from the TestCases class are executed.
 * To execute the program in "test" mode, simply define a TEST macro
 * ----------------------------------------------------------------------
 */

//#define TEST 0

#ifdef TEST
#include "testcases.h"
QTEST_MAIN(TestCases);
#else
#include <QApplication>
#include <QThreadPool>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QThreadPool::globalInstance()->setMaxThreadCount(6);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
#endif
