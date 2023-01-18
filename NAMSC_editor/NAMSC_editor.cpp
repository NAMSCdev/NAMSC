#include "NAMSC_editor.h"
#include <qinputdialog.h>
#include <QMessageBox>
#include <QMimeData>
#include <QMimeDatabase>

#include "BasicNodeProperties.h"
#include "ChoiceEventProperties.h"
#include "DialogEventProperties.h"
#include "EventTreeItemModel.h"
#include "EventTreeItem.h"
#include "GraphNodePropertiesPack.h"
#include "JumpEventProperties.h"
#include "Preview.h"
#include "ProjectConfiguration.h"
#include "ObjectPropertyPack.h"
#include "Novel\Data\Asset\AssetManager.h"
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

void errorMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QString category;
    switch (type)
    {
    case QtDebugMsg:
        category = "Debug";
        break;
    default:
    case QtInfoMsg:
        category = "Info";
        break;
    case QtWarningMsg:
        category = "Warning";
        break;
    case QtCriticalMsg:
        category = "Critical";
        break;
    case QtFatalMsg:
        category = "Fatal";
        break;
    }

    QString message = '[' + category + "] [" + context.function + " {" + context.file + ':' + std::to_string(context.line).c_str() + "}]" + msg;
    switch (type)
    {
    case QtDebugMsg:
#ifdef DEBUG
        QMessageBox::information(nullptr, category, message);
#endif
        break;

    default:
    case QtInfoMsg:
    case QtWarningMsg:
        QMessageBox::warning(nullptr, category, message);
        break;

    case QtCriticalMsg:
    case QtFatalMsg:
        QMessageBox::critical(nullptr, category, message);
        throw NovelLib::NovelException(msg);
        break;
    }
}


NAMSC_editor::NAMSC_editor(QWidget *parent)
    : QMainWindow(parent)
{
    supportedFormats();

    // Prepare ui
    ui.setupUi(this);
    //qInstallMessageHandler(errorMessageHandler); // Causes editor to crash -> Retrieving non existing element from a map returns null and is used to check if a key is already used. Also there seems to be an issue with quick dialog boxes, which also return some warning from qt but work anyway.

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

 //   Novel& novel = Novel::getInstance();
 //   novel.newState(0);
	//AssetManager& assetManager = AssetManager::getInstance();
 //   assetManager.addAssetImageSceneryBackground("game/Assets/kot.png", 0, 0, "game/Assets/kot.png");
 //   assetManager.addAssetImageSceneryObject("game/Assets/pies.png", 0, 0, "game/Assets/pies.png");

 //   Scene scene(QString("start"), QString(""));

 //   Character testCharacter(QString("kot1"), QString("game/Assets/pies.png"), false, QPoint(0, 0), QSizeF(1.0, 1.0), 20.0);

 //   Scenery scenery;
 //   scenery.setBackgroundAssetImage("game/Assets/kot.png");
 //   scenery.setDisplayedCharacter("kot1", testCharacter);
 //   testCharacter.name = "kot2";
 //   scenery.setDisplayedCharacter("kot2", testCharacter);

 //   Event* event = new EventDialogue(&scene);
 //   event->scenery = scenery;
 //   scene.addEvent(event);
 //   novel.addScene("start", std::move(scene));

 //   novel.setDefaultCharacter("kot", Character("kot", "game/Assets/pies.png"));
 //   novel.setDefaultSceneryObject("pies", SceneryObject("pies", "game/Assets/kot.png"));

 //   novel.saveNovel(0);

    //Novel::getInstance().loadNovel(0, false);

	//Novel::getInstance().saveNovel(0);
 //   saveEditor();

    //Novel::getInstance().loadNovel(0, false);
    //loadEditor();
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
    connect(ui.eventsTree->selectionModel(), &QItemSelectionModel::selectionChanged, static_cast<EventTreeItemModel*>(ui.eventsTree->model()), &EventTreeItemModel::selectionChanged);
    connect(static_cast<EventTreeItemModel*>(ui.eventsTree->model()), &EventTreeItemModel::propertyTabChangeRequested, this, &NAMSC_editor::propertyTabChangeRequested);
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

void NAMSC_editor::loadEditor()
{
    loadGraph(ui.graphView);
}

void NAMSC_editor::saveEditor()
{
    saveGraph(ui.graphView);
}

void NAMSC_editor::propertyTabChangeRequested(void* object, PropertyTypes dataType)
{
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
        {
                GraphNodePropertiesPack* properties = new GraphNodePropertiesPack(static_cast<GraphNode*>(object));
                ui.propertiesLayout->addWidget(properties);
                static_cast<EventTreeItemModel*>(ui.eventsTree->model())->nodeSelectionChanged(static_cast<GraphNode*>(object));
                connect(properties->basicNodeProperties, &BasicNodeProperties::sceneUpdated, static_cast<EventTreeItemModel*>(ui.eventsTree->model()), &EventTreeItemModel::sceneUpdated);
                break;
        }
        case PropertyTypes::ObjectTreeItem:
            // todo currently assuming it's always Image
        	ui.propertiesLayout->addWidget(new ObjectPropertyPack(static_cast<SceneryObject*>(object)));
            break;
        case PropertyTypes::CharacterTreeItem:
            ui.propertiesLayout->addWidget(new ObjectPropertyPack(static_cast<SceneryObject*>(object)));
            break;
        case PropertyTypes::Scene:
        {
            GraphNodePropertiesPack* properties = new GraphNodePropertiesPack(ui.graphView->getNodeByName(static_cast<Scene*>(object)->getComponentName()));
            ui.propertiesLayout->addWidget(properties);
            connect(properties->basicNodeProperties, &BasicNodeProperties::sceneUpdated, static_cast<EventTreeItemModel*>(ui.eventsTree->model()), &EventTreeItemModel::sceneUpdated);
            break;
        }
        case PropertyTypes::DialogEventItem:
            ui.propertiesLayout->addWidget(new DialogEventProperties(static_cast<EventDialogue*>(object)));
            break;
        case PropertyTypes::ChoiceEventItem:
            ui.propertiesLayout->addWidget(new ChoiceEventProperties(static_cast<EventChoice*>(object), ui.graphView));
            break;
        case PropertyTypes::JumpEventItem:
            ui.propertiesLayout->addWidget(new JumpEventProperties(static_cast<EventJump*>(object), ui.graphView));
            break;
        }

        ui.propertiesLayout->addStretch();
    }
}

void NAMSC_editor::debugConstructorActions()
{
    Novel& snovel = Novel::getInstance();
    QString scene1Name = QString("Scene 1");
    snovel.addScene(scene1Name, Scene(scene1Name));
    Scene* scene1 = snovel.getScene(scene1Name);
    scene1->insertEvent(0, new EventJump(scene1, "Jump to Scene 2", "Scene 2"));
    scene1->insertEvent(0, new EventDialogue(scene1, "Dialogue3", {}));
    scene1->insertEvent(0, new EventDialogue(scene1, "Dialogue2", {}));
    scene1->insertEvent(0, new EventDialogue(scene1, "Dialogue1", {}));

    node = new GraphNode;
    node->setLabel(scene1->name);
    scene->addItem(node);
    
    QString scene2Name = QString("Scene 2");
    snovel.addScene(scene2Name, Scene(scene2Name));
    Scene* scene2 = snovel.getScene(scene2Name);
    Translation choicetext = Translation(std::unordered_map<QString, QString>({ {QString("En"), QString("Choice event in scene 2")} }));
    EventChoice* eventChoice = new EventChoice(
        scene2, 
        "Choice Event",
        choicetext);
    eventChoice->choices.push_back(Choice(eventChoice, "Choice 1", Translation(std::unordered_map<QString, QString>({ {"En", "Yes"} })), "", "Scene 1"));
    eventChoice->choices.push_back(Choice(eventChoice, "Choice 2", Translation(std::unordered_map<QString, QString>({ {"En", "No"} }))));

    scene2->insertEvent(0, eventChoice);
    scene2->insertEvent(0, new EventDialogue(scene2, "Dialogue3", {}));
    scene2->insertEvent(0, new EventDialogue(scene2, "Dialogue2", {}));
    scene2->insertEvent(0, new EventDialogue(scene2, "Dialogue1", {}));
    node2 = new GraphNode;
    node2->setLabel(scene2->name);
    //node2->appendConnectionPoint(GraphConnectionType::In);
    scene->addItem(node2);

    node->moveBy(-100, -100);
    node2->moveBy(300, 300);
    //node->connectPointTo(0, node2->connectionPointAt(GraphConnectionType::In, 0).get());
    
    //connect(ui.graphView, &GraphView::nodeDoubleClicked, this, [&](GraphNode* node)
    //    {
    //        qDebug() << node->getLabel() << "has been double clicked!";
    //    });

    //node->connectToNode(node2->getLabel());

    //node->connectToNode(node2->getLabel());
    //node->connectToNode(node->getLabel());
    //node->disconnectFrom(node2->getLabel());

    ProjectConfiguration::getInstance()->setProjectPath(QDir::currentPath());
}

void NAMSC_editor::loadGraph(GraphView* graph)
{
    QDirIterator it("game\\Graph", QStringList(), QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QFile serializedFile(it.next());
        serializedFile.open(QIODeviceBase::ReadOnly);

        QDataStream dataStream(&serializedFile);

        dataStream >> *graph;
    }
}

void NAMSC_editor::saveGraph(GraphView* graph)
{
    QDir graphDir = QDir::currentPath();
    graphDir.mkpath("game\\Graph");
    graphDir.cd("game\\Graph"); // todo check; eventually apply to NovelIO.cpp

    if (ui.graphView != nullptr)
    {
        QFile serializedFile(graphDir.path() + "\\graph");
        serializedFile.open(QIODeviceBase::WriteOnly);

        QDataStream dataStream(&serializedFile);

        dataStream << *graph;
    }
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