#include "MainEditorWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainEditorWindow w;
    w.show();
    w.runGraphView();
    return a.exec();
}
