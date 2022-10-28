#include "NAMSC_editor.h"
#include <QGraphicsWidget>

NAMSC_editor::NAMSC_editor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.graphicsView->setSceneRect(ui.graphicsView->contentsRect());

    scene = new QGraphicsScene(this);
    scene->setSceneRect(ui.graphicsView->rect());

    //view->setViewport(new QOpenGLWidget);
    ui.graphicsView->setScene(scene);
    scene->setSceneRect(this->rect());

    node = new GraphNode;
    node->setLabel("To nie jest tak, że dobrze albo, że niedobrze, po prostu NAMSC nam idzie okropnie i to będzie cud jak się wyrobimy");
    node->appendConnectionPoint(GraphConnectionType::In);
    node->appendConnectionPoint(GraphConnectionType::In);
    node->appendConnectionPoint(GraphConnectionType::In);
    node->appendConnectionPoint(GraphConnectionType::In);
    node->appendConnectionPoint(GraphConnectionType::In);
    //node->appendConnectionPoint(GraphConnectionType::In);
    //node->appendConnectionPoint(GraphConnectionType::In);

    node->appendConnectionPoint(GraphConnectionType::Out);
    node->appendConnectionPoint(GraphConnectionType::Out);
    node->appendConnectionPoint(GraphConnectionType::Out);
    node->appendConnectionPoint(GraphConnectionType::Out);
    node->appendConnectionPoint(GraphConnectionType::Out);
    node->appendConnectionPoint(GraphConnectionType::Out);
    node->appendConnectionPoint(GraphConnectionType::Out);
    scene->addItem(node);

    node2 = new GraphNode;
    node2->setLabel("BigD");
    node2->appendConnectionPoint(GraphConnectionType::In);

    scene->addItem(node2);

    node->connectPointTo(0, node2->connectionPointAt(GraphConnectionType::In, 0).get());
}

NAMSC_editor::~NAMSC_editor()
{

}
