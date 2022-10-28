#include "MainEditorWindow.h"
#include <nodes/FlowScene>
#include "SceneDataModel.h"
#include <QLayout>

MainEditorWindow::MainEditorWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

MainEditorWindow::~MainEditorWindow()
{}

void MainEditorWindow::runGraphView()
{
    layout = new QGridLayout(ui.centralWidget);

    dataModelRegistry = std::make_shared<DataModelRegistry>();
    dataModelRegistry->registerModel<SceneDataModel>();

    scene = new FlowScene(dataModelRegistry, ui.centralWidget);
    
    graphView = new GraphView(scene);
    graphView->setParent(ui.centralWidget);

    layout->addWidget(graphView);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
}