#include "NAMSC_editor.h"
#include <QGraphicsWidget>
#include <qfilesystemmodel.h>
#include "Preview.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    }
}


NAMSC_editor::NAMSC_editor(QWidget *parent)
    : QMainWindow(parent)
{
    // Prepare ui
    ui.setupUi(this);

    ui.mainSplitter->setSizes({ 20, 60, 20 });
    // ui.middlePanel->setSizes({ 80, 20 });
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

    prepareAssetsTree();

}

void NAMSC_editor::prepareAssetsTree()
{
    QFileSystemModel* model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    ui.assetsTree->setModel(model);
    ui.assetsTree->hideColumn(1);
    ui.assetsTree->hideColumn(3);
    ui.assetsTree->setRootIndex(model->index(QDir::currentPath()));
    connect(ui.assetsTree->selectionModel(), &QItemSelectionModel::selectionChanged, ui.assetsPreview, &Preview::selectionChanged);
    
    ui.assetsPreview->setSceneRect(ui.assetsPreview->contentsRect());
}

NAMSC_editor::~NAMSC_editor()
{

}
