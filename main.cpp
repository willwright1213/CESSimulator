#define TEST 0

#ifdef TEST
#include "testcases.h"
QTEST_MAIN(TestCases);
#else
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
#endif
