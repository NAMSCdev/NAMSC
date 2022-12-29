#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
#ifdef DEBUG
    AssetManager::getInstance().insertAssetImageSceneryBackground("testBackground", 0, 0, "C:\\Users\\Murloc\\Downloads\\kot.jpg");
    Scenery scenery;
    scenery.setBackgroundAssetImage("testBackground");
    Scene scene(QString("test"), QString(""), scenery);
    novel.setScene("test", scene);
#endif
}

MainWindow::~MainWindow()
{
}