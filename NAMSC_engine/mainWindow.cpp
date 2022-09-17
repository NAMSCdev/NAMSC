#include "mainWindow.h"

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    scene = new QGraphicsScene(this);
    ui.graphicsView->setViewport(new QOpenGLWidget);
    ui.graphicsView->setScene(scene);

    textbox = new MainTextBox(this);
    textbox->setBoundingBoxSize(500, 200);
    scene->addItem(textbox);
}

mainWindow::~mainWindow()
{}
