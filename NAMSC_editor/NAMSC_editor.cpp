#include "NAMSC_editor.h"
#include <QGraphicsWidget>
#include <qfilesystemmodel.h>
#include <qinputdialog.h>
#include <QMimeData>

#include "BasicNodeProperties.h"
#include "ImageObjectTreeWidgetItem.h"
#include "Preview.h"
#include "ProjectConfiguration.h"

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

    prepareSwitchboard();

    connect(ui.actionNew_project, &QAction::triggered, ProjectConfiguration::getInstance(), &ProjectConfiguration::createNewProject);
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

    if (QFile::exists("plik")) {
        QFile file = { "plik" };
        QDataStream ds(&file);
        //ds >> novel;
    }

    // Add raw context menu to assets tab
    ui.assetsTree->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui.assetsTree, &QTreeView::customContextMenuRequested, this, [&](QPoint pos)
        {
            QAction addToObjectsAction(tr("Add to objects"), ui.assetsTree);
			// TODO change this to target class
			 connect(&addToObjectsAction, &QAction::triggered, this, [&]
				{
					auto selectedFile = ui.assetsTree->selectionModel()->model()->mimeData({ ui.assetsTree->currentIndex().siblingAtColumn(0) });

			 		bool isOk = false;
                    QString objectName; // TODO check name, show error if name is invalid
                    while (!isOk) {
                        objectName = QInputDialog::getText(this, tr("Create object"),
                            tr("Enter name for created object:"), QLineEdit::Normal,
                            selectedFile->urls()[0].fileName(), &isOk);
                    }

                    SceneryObject newSceneryObject;
                    newSceneryObject.name = objectName;
                    Novel::getInstance().setDefaultSceneryObject(objectName, newSceneryObject); // todo object will be deleted -> beware

					// TODO Check file type/extension
					ImageObjectTreeWidgetItem* newItem = new ImageObjectTreeWidgetItem(ui.objectsTree);
                    newItem->relativeAssetPath = selectedFile->urls()[0].toString();
					newItem->setText(0, objectName);
                    newItem->setIcon(0, QIcon(":/NAMSC_editor/imageIcon"));

    				ui.objectsTree->addTopLevelItem(newItem);
				});

            QMenu contextMenu = QMenu(ui.assetsTree);
            contextMenu.addAction(&addToObjectsAction);
            contextMenu.exec(mapToGlobal(pos));
        });
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

    // Connect addToScene action from objects tab
    //connect(ui.objectsTree, &ObjectsTree::addObjectToScene, &switchboard, );

    // Connect from switchboard
    connect(&switchboard, &PropertyConnectionSwitchboard::nodeSelectionChangedSignal, this, &NAMSC_editor::propertyTabChangeRequested);
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

    switch (dataType)
	{
		case PropertyTypes::Node:
			if (object != nullptr) {
				ui.propertiesLayout->addWidget(new GraphNodePropertiesPack(static_cast<GraphNode*>(object)));
				ui.propertiesLayout->addStretch();
			}
        break;
    }
}

void NAMSC_editor::debugConstructorActions()
{
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

    connect(ui.graphView, &GraphView::nodeDoubleClicked, this, [&](GraphNode* node)
        {
            qDebug() << node->getLabel() << "has been double clicked!";
        });

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

NAMSC_editor::~NAMSC_editor()
{

}
