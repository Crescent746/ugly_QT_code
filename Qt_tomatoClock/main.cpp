#include "tomatoclock.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TomatoClock w;
    w.show();
    return a.exec();
}

