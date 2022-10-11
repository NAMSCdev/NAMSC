#include "mainWindow.h"

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    scene = new QGraphicsScene(this);
    ui.graphicsView->setViewport(new QOpenGLWidget);
    ui.graphicsView->setScene(scene);

    scene->setSceneRect(this->rect());
    textbox2 = new TextBox(this);
    scene->addItem(textbox2);
}

mainWindow::~mainWindow()
{}
