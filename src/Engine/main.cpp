#include "NAMSC_engine.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NAMSC_engine w;
    w.show();
    return a.exec();
}
