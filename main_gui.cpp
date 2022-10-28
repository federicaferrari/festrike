#include "mainwindow.h"
#include "temp2.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    temp2 tmp2;
    tmp2.initsm();
    MainWindow w;
    w.show();
    return a.exec();

}
