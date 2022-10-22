#include "NAMSC_editor.h"

NAMSC_editor::NAMSC_editor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.graphicsView->setSceneRect(ui.graphicsView->contentsRect());

    scene = new QGraphicsScene(this);
    scene->setSceneRect(ui.graphicsView->rect());

    //view->setViewport(new QOpenGLWidget);
    ui.graphicsView->setScene(scene);
    //scene->setSceneRect(this->rect());

    //node = new GraphNode;
    //node->setLabel("To nie jest tak, że dobrze albo, że niedobrze, po prostu NAMSC nam idzie okropnie i to będzie cud jak się wyrobimy");
    //scene->addItem(node);

    //scene->addItem(new QGraphicsRectItem(QRectF(10, 10, 50, 50)));
}

NAMSC_editor::~NAMSC_editor()
{}
