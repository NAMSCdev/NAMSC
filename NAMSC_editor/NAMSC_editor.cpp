#include "NAMSC_editor.h"
#include <qfilesystemmodel.h>
#include <qinputdialog.h>
#include <QMimeData>
#include <QMimeDatabase>
#include <qsortfilterproxymodel.h>

#include "BasicNodeProperties.h"
#include "CustomSortFilterProxyModel.h"
#include "EventTreeItemModel.h"
#include "GraphNodePropertiesPack.h"
#include "ObjectTreeWidgetItem.h"
#include "Preview.h"
#include "ProjectConfiguration.h"
#include "ObjectPropertyPack.h"
#include "Novel/Event/EventDialogue.h"

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
    supportedFormats();

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

    debugConstructorActions();
    prepareAssetsTree();
    prepareEventsTree();

    //needs to be after preparing other widgets
    prepareSwitchboard();

    connect(ui.actionNew_project, &QAction::triggered, ProjectConfiguration::getInstance(), &ProjectConfiguration::createNewProject);
    connect(ui.assetsTree, &AssetTreeView::addAssetToObjects, ui.objectsTree, &ObjectsTree::addAssetToObjects);
    connect(ui.assetsTree, &AssetTreeView::addAssetToCharacters, ui.charactersTree, &CharacterTree::addAssetToCharacters);
}

void NAMSC_editor::prepareAssetsTree()
{
    ui.assetsPreview->setSupportedAudioFormats(supportedAudioFormats);
    ui.assetsPreview->setSupportedImageFormats(supportedImageFormats);
    ui.assetsTree->setSupportedAudioFormats(supportedAudioFormats);
    ui.assetsTree->setSupportedImageFormats(supportedImageFormats);
    connect(ui.assetsTree->selectionModel(), &QItemSelectionModel::selectionChanged, ui.assetsPreview, &Preview::selectionChanged);
    ui.assetsTree->setContextMenuPolicy(Qt::CustomContextMenu);
}

void NAMSC_editor::prepareEventsTree()
{
    EventTreeItemModel* model = new EventTreeItemModel("test", nullptr);
    ui.eventsTree->setModel(model);
    ui.eventsTree->setItemsExpandable(true);
}

void NAMSC_editor::prepareSwitchboard()
{
    // Connect to switchboard 
    // Connect selection of a node to switchboard
    connect(ui.graphView->scene(), &QGraphicsScene::selectionChanged, &switchboard, [&]
        {
            if (ui.graphView->scene()->selectedItems().isEmpty())
            {
                switchboard.nodeSelectionChanged(nullptr);
            }
            else {
                switchboard.nodeSelectionChanged(qgraphicsitem_cast<GraphNode*>(ui.graphView->scene()->selectedItems()[0]));
            }
        });
    
    // Connect selection from objects tab to switchboard
    connect(ui.objectsTree, &ObjectsTree::selectedObjectChanged, &switchboard, &PropertyConnectionSwitchboard::objectSelectionChanged);

    // Connect selection from characters tab to switchboard
    connect(ui.charactersTree, &CharacterTree::selectedCharacterChanged, &switchboard, &PropertyConnectionSwitchboard::characterSelectionChanged);

    // Connect from switchboard
    connect(&switchboard, &PropertyConnectionSwitchboard::nodeSelectionChangedSignal, this, &NAMSC_editor::propertyTabChangeRequested);
    connect(&switchboard, &PropertyConnectionSwitchboard::sceneryObjectSelectionChangedSignal, this, &NAMSC_editor::propertyTabChangeRequested);
    connect(&switchboard, &PropertyConnectionSwitchboard::characterSelectionChangedSignal, this, &NAMSC_editor::propertyTabChangeRequested);
}

void NAMSC_editor::propertyTabChangeRequested(void* object, PropertyTypes dataType)
{
    qDebug() << "test";
    while (ui.propertiesLayout->count() != 0)
    {
        auto childItem = ui.propertiesLayout->takeAt(0);
        if (childItem->widget() != 0)
        {
            delete childItem->widget();
        }
    }

    if (object != nullptr) {
        switch (dataType)
        {
        case PropertyTypes::Node:
        	ui.propertiesLayout->addWidget(new GraphNodePropertiesPack(static_cast<GraphNode*>(object)));
            static_cast<EventTreeItemModel*>(ui.eventsTree->model())->nodeSelectionChanged(static_cast<GraphNode*>(object));
            break;

        case PropertyTypes::ObjectTreeItem:
            // todo currently assuming it's always Image
        	ui.propertiesLayout->addWidget(new ObjectPropertyPack(static_cast<SceneryObject*>(object)));
            break;
        case PropertyTypes::CharacterTreeItem:
            ui.propertiesLayout->addWidget(new ObjectPropertyPack(static_cast<SceneryObject*>(object)));
            break;
        }

        ui.propertiesLayout->addStretch();
    }
}

void NAMSC_editor::debugConstructorActions()
{
    node = new GraphNode;
    node->setLabel("To nie jest tak, że dobrze albo, że niedobrze, po prostu NAMSC nam idzie okropnie i to będzie cud jak się wyrobimy");
    //node->appendConnectionPoint(GraphConnectionType::In);
    //node->appendConnectionPoint(GraphConnectionType::In);
    //node->appendConnectionPoint(GraphConnectionType::In);
    //node->appendConnectionPoint(GraphConnectionType::In);
    //node->appendConnectionPoint(GraphConnectionType::In);

    //node->appendConnectionPoint(GraphConnectionType::Out);
    //node->appendConnectionPoint(GraphConnectionType::Out);
    //node->appendConnectionPoint(GraphConnectionType::Out);
    //node->appendConnectionPoint(GraphConnectionType::Out);
    //node->appendConnectionPoint(GraphConnectionType::Out);
    //node->appendConnectionPoint(GraphConnectionType::Out);
    //node->appendConnectionPoint(GraphConnectionType::Out);
    scene->addItem(node);

    node2 = new GraphNode;
    node2->setLabel("BigD");
    //node2->appendConnectionPoint(GraphConnectionType::In);

    scene->addItem(node2);

    //node->connectPointTo(0, node2->connectionPointAt(GraphConnectionType::In, 0).get());

    connect(ui.graphView, &GraphView::nodeDoubleClicked, this, [&](GraphNode* node)
        {
            qDebug() << node->getLabel() << "has been double clicked!";
        });

    node->connectToNode(node2->getLabel());
    node->disconnectFrom(node2->getLabel());
    // Raw properties add
    //auto* cbutton = new CollapseButton(ui.propertiesWidget);
    //auto* props = new BasicNodeProperties(ui.propertiesWidget);
    //props->setScene(scene);
    //connect(scene, &QGraphicsScene::selectionChanged, props, &BasicNodeProperties::selectedNodeChanged);
    //cbutton->setText("Basic node options");
    //cbutton->setContent(props);
    //ui.propertiesLayout->addWidget(cbutton);
    //ui.propertiesLayout->addWidget(props);

    ProjectConfiguration::getInstance()->setProjectPath(QDir::currentPath());
}

void NAMSC_editor::supportedFormats()
{
    supportedImageFormats.append(db.mimeTypeForName("image/png"));
    supportedImageFormats.append(db.mimeTypeForName("image/bmp"));
    supportedImageFormats.append(db.mimeTypeForName("image/jpeg"));

    /*
    supportedAudioFormats.append(db.mimeTypeForName("audio/mpeg"));
    supportedAudioFormats.append(db.mimeTypeForName("audio/MPA"));
    supportedAudioFormats.append(db.mimeTypeForName("audio/mpa-robust"));

    supportedAudioFormats.append(db.mimeTypeForName("audio/x-wav"));
    supportedAudioFormats.append(db.mimeTypeForName("audio/wav"));
    supportedAudioFormats.append(db.mimeTypeForName("audio/wave"));
    supportedAudioFormats.append(db.mimeTypeForName("audio/vnd.wave"));

    supportedAudioFormats.append(db.mimeTypeForName("audio/flac"));
    */
}

NAMSC_editor::~NAMSC_editor()
{

}
