#include "NAMSC_editor.h"
#include <QGraphicsWidget>
#include <qfilesystemmodel.h>

#include "BasicNodeProperties.h"
#include "Preview.h"

NAMSC_editor::NAMSC_editor(QWidget *parent)
    : QMainWindow(parent)
{
    // Prepare ui
    ui.setupUi(this);

    ui.mainSplitter->setSizes({ 20, 60, 20 });
    ui.middlePanel->setStretchFactor(0, 70);
    ui.middlePanel->setStretchFactor(1, 30);

    ui.graphView->setSceneRect(ui.graphView->contentsRect());

    scene = new QGraphicsScene(this);
    scene->setSceneRect(ui.graphView->rect());

    //view->setViewport(new QOpenGLWidget);
    ui.graphView->setScene(scene);
    scene->setSceneRect(this->rect());

    node = new GraphNode;
    node->setLabel("To nie jest tak, że dobrze albo, że niedobrze, po prostu NAMSC nam idzie okropnie i to będzie cud jak się wyrobimy");
    node->appendConnectionPoint(GraphConnectionType::In);
    node->appendConnectionPoint(GraphConnectionType::In);
    node->appendConnectionPoint(GraphConnectionType::In);
    node->appendConnectionPoint(GraphConnectionType::In);
    node->appendConnectionPoint(GraphConnectionType::In);

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

	QFileSystemModel* model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    ui.assetsTree->setModel(model);
    ui.assetsTree->hideColumn(1);
    ui.assetsTree->hideColumn(3);
    ui.assetsTree->setRootIndex(model->index(QDir::currentPath()));
	connect(ui.assetsTree->selectionModel(), &QItemSelectionModel::selectionChanged, ui.assetsPreview, &Preview::selectionChanged);

    auto* cbutton = new CollapseButton(ui.propertiesWidget);
    auto* props = new BasicNodeProperties(ui.propertiesWidget);
    props->setScene(scene);
    connect(scene, &QGraphicsScene::selectionChanged, props, &BasicNodeProperties::selectedNodeChanged);
    props->show();
    cbutton->setText("Basic node options");
    cbutton->setContent(props);
    ui.propertiesLayout->addWidget(cbutton);
    ui.propertiesLayout->addWidget(props);
    ui.propertiesLayout->addStretch();

    if (QFile::exists("plik")) {
        QFile file = { "plik" };
        QDataStream ds(&file);
        //ds >> novel;
    }
}

NAMSC_editor::~NAMSC_editor()
{

}
