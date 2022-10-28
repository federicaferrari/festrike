#include <QtCore>

#include <QtCore/QCoreApplication>
#include <QCoreApplication>
#include "concurrentbtle.h"
//#include "shared_memory.h"


int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    ConcurrentBtle btle;
    btle.init_sm();

    return a.exec();
}


