#include "GraphView.h"

#include <qinputdialog.h>
#include <QKeyEvent>
#include <QMenu>
#include <qmessagebox.h>
#include <ranges>
#include <QPointF>
#include "GraphNode.h"
#include "Novel/Data/Novel.h"
#include "Novel/Event/EventChoice.h"
#include "Novel/Event/EventJump.h"

GraphView::GraphView(QWidget* parent) : QGraphicsView(parent)
{
	setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);
    //setDragMode(ScrollHandDrag);

    createContextMenu();
}

void GraphView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);

    if (event->button() == Qt::MiddleButton)
    {
        // Store original position.
        mousePressOrigin = mapToScene(event->pos());
    }
}

void GraphView::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);
 
    if (/*scene()->mouseGrabberItem() == nullptr && */ event->buttons() == Qt::MiddleButton)
    {
        //QPointF oldPos = mapToScene(mousePressOrigin);
        //QPointF newPos = mapToScene(event->pos());
        //QPointF translation = newPos - oldPos;

        //translate(translation.x(), translation.y());

        //mousePressOrigin = event->pos();
        QPointF difference = mousePressOrigin - mapToScene(event->pos());
        setSceneRect(sceneRect().translated(difference.x(), difference.y()));
    }

}

GraphNode* GraphView::getNodeByName(const QString& name)
{
    for (auto node : scene()->items())
    {
        const auto castNodePtr = dynamic_cast<GraphNode*>(node);
        if (castNodePtr != nullptr && castNodePtr->getLabel() == name) return castNodePtr;
    }

    return nullptr;
}

void GraphView::zoomIn()
{
    scaleView(qreal(1.1));
}

void GraphView::zoomOut()
{
    scaleView(1 / qreal(1.1));
}

void GraphView::passNodeDoubleClick(GraphNode* node)
{
    if (node != nullptr) {
        emit nodeDoubleClicked(node);
    }
}

void GraphView::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphView::wheelEvent(QWheelEvent* event)
{
    scaleView(pow(1.5, event->angleDelta().y() / 240.0));
}

void GraphView::drawBackground(QPainter* painter, const QRectF& rect)
{
    // Grid
    QPen pen;
    pen.setStyle(Qt::DashLine);
    pen.setWidth(2);
    pen.setBrush(Qt::gray);
    painter->setPen(pen);
    
    //auto visibleArea = mapToScene(pos());
    //auto visibleArea = mapToScene(this->width(), this->height());
    //auto visibleArea = mapToScene(rect.topLeft().toPoint());
    auto visibleArea = mapToScene(this->viewport()->geometry()).boundingRect();

    int step = 100;

    // Horizontal
    QLine hline({
	                static_cast<int>(visibleArea.x()) - (static_cast<int>(visibleArea.x()) % step) - step,
	                static_cast<int>(visibleArea.y()) - (static_cast<int>(visibleArea.y()) % step)
                },
                {
	                static_cast<int>(visibleArea.x()) + static_cast<int>(visibleArea.width()),
	                static_cast<int>(visibleArea.y()) - (static_cast<int>(visibleArea.y()) % step)
                });
    for (int i = 0; i < visibleArea.height() + step; i += step) {
        painter->drawLine(hline);
        hline.translate(0, step);
    }
    // Vertical
    QLine vline({
	                static_cast<int>(visibleArea.x()) - (static_cast<int>(visibleArea.x()) % step),
	                static_cast<int>(visibleArea.y()) - (static_cast<int>(visibleArea.y()) % step) - step
                },
                {
	                static_cast<int>(visibleArea.x()) - (static_cast<int>(visibleArea.x()) % step),
	                static_cast<int>(visibleArea.y()) + static_cast<int>(visibleArea.height())
                });
    for (int i = 0; i < visibleArea.width() + step; i += step) {
        painter->drawLine(vline);
        vline.translate(step, 0);
    }
}

void GraphView::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 2)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphView::contextMenuEvent(QContextMenuEvent* event)
{
    contextMenuPosition = mapToScene(event->pos());

    QMenu menu(this);
    menu.addAction(createNodeAction);
    menu.addAction(removeNodeAction);
    //if (itemAt(mapFromScene(contextMenuPosition.toPoint())) == nullptr) removeNodeAction->setDisabled(true);
    if (scene()->focusItem() == nullptr) removeNodeAction->setDisabled(true);
	else removeNodeAction->setEnabled(true);
    menu.exec(event->globalPos());

    qDebug() << scene()->itemAt(mapToScene(event->pos()), QTransform()); // Nodes detection
    qDebug() << scene()->focusItem(); // Nodes are usually focused welp
}

void GraphView::createContextMenu()
{
    createNodeAction = new QAction(tr("Create node"), this);
    // createNodeAction->setShortcut();
    createNodeAction->setStatusTip(tr("Create node at the current mouse position"));

    removeNodeAction = new QAction(tr("Remove node"), this);
    removeNodeAction->setStatusTip(tr("Remove node at the current mouse position"));

    connect(createNodeAction, &QAction::triggered, this, &GraphView::createNode);
    connect(removeNodeAction, &QAction::triggered, this, &GraphView::removeNode);
}

void GraphView::createNode()
{
    int step = 100;
    QPoint roundedPos = QPoint{ static_cast<int>(std::round(contextMenuPosition.x() / step)) * step, static_cast<int>(std::round(contextMenuPosition.y() / step)) * step };

    QString name;
    bool pressedOk = false;
    bool isNameOk = false;
    do {
        name = QInputDialog::getText(this, tr("Add new scene"), tr("Provide unique scene name:"), QLineEdit::Normal, "", &pressedOk);

        if (!pressedOk) break;
        else if (name.isNull() || name.isEmpty())
        {
            continue;
        }
        else if (Novel::getInstance().getScene(name) != nullptr)
        {
            QMessageBox(QMessageBox::Critical, tr("Invalid scene name"), tr("Scene with this name already exists, please provide another name."), QMessageBox::Ok).exec();
            continue;
        }
        else isNameOk = true;
    } while (!isNameOk);

    // Name is ok or pressed cancel
    if (pressedOk)
    {
        Scene s;
        s.name = name;
        Novel::getInstance().addScene(std::move(s));

        GraphNode* node = new GraphNode(roundedPos);
        node->setLabel(name);
        scene()->addItem(node);
    }
}

void GraphView::removeNode()
{
    auto* selectedNode = dynamic_cast<GraphNode*>(scene()->focusItem()); // check if cast is proper

    if (selectedNode == nullptr)
    {
        qDebug() << "[GraphView] Focused item is not GraphNode*";
    }

    // Update jumps from other scenes to this
    for (auto& conn : selectedNode->getConnectionPoints(GraphConnectionType::In))
    {
        for (auto& ev : *Novel::getInstance().getScene(conn->getSourceNodeName())->getEvents())
        {
            switch (ev->getComponentEventType())
            {
            case EventSubType::EVENT_CHOICE:
                for (auto& choice : *static_cast<EventChoice*>(ev.get())->getChoices()) {
                    if (choice.jumpToSceneName == selectedNode->getLabel()) 
                        const_cast<Choice&>(choice).jumpToSceneName = ""; //todo: refactorthis monster later
                }
                break;
            case EventSubType::EVENT_JUMP:
                auto evj = static_cast<EventJump*>(ev.get());
                if (evj->jumpToSceneName == selectedNode->getLabel()) evj->jumpToSceneName = "";
                break;
            }
        }

    }

    while(!selectedNode->getConnectionPoints(GraphConnectionType::In).isEmpty())
    {
        
        if (auto* node = getNodeByName(selectedNode->getConnectionPoints(GraphConnectionType::In).first()->getSourceNodeName()))
        {
            node->disconnectFrom(selectedNode->getLabel());
        }
        else
        {
            qDebug() << "[GraphView] Found non existing node while removing the other";
        }
    }

    while(!selectedNode->getConnectionPoints(GraphConnectionType::Out).isEmpty())
    {
        if (!selectedNode->disconnectFrom(selectedNode->getConnectionPoints(GraphConnectionType::Out).first()->getDestinationNodeName()))
        {
            qDebug() << "[GraphView] Found non existing node while removing the other";
        }
    }

    emit nodeDeleted();

    Novel::getInstance().removeScene(selectedNode->getLabel());
    scene()->removeItem(selectedNode);
    delete selectedNode;
}

void GraphView::serializableLoad(QDataStream& dataStream)
{
    size_t numberOfNodes;
    dataStream >> numberOfNodes;

    for (size_t i = 0ull; i < numberOfNodes; ++i)
    {
        GraphNode* node = new GraphNode();
        dataStream >> *node;
        scene()->addItem(node);
    }

    // Cannot do both at the same time, because a node may be not constructed before, so there's no possible connection
    for (const auto& scenePair : *Novel::getInstance().getScenes())
    {
        // If can get a node
        GraphNode* node = getNodeByName(scenePair.first);
	    if (node != nullptr)
	    {
            // Look through all events and connect nodes wherever applicable
		    for (const auto& ev : *scenePair.second.getEvents())
		    {
			    if (auto evj = dynamic_cast<EventJump*>(ev.get())) node->connectToNode(evj->jumpToSceneName);


                else if (auto evc = dynamic_cast<EventChoice*>(ev.get()))
                {
	                for (const auto& choice : *evc->getChoices()) node->connectToNode(choice.jumpToSceneName);
                }
                // todo check if names of the nodes exist, though it should work anyway
		    }
	    }
    }
}

void GraphView::serializableSave(QDataStream& dataStream) const
{
    const auto& itemsOnScene = scene()->items();

    // Counts GraphNode objects on the scene. It should be the same as the number of scenes in the Novel
    dataStream << [&]() { size_t i = 0;  for (const auto& elem : itemsOnScene) if (dynamic_cast<GraphNode*>(elem) != nullptr) ++i; return i; }();

    for (auto elem : itemsOnScene)
    {
        GraphNode* node = dynamic_cast<GraphNode*>(elem);
	    if (node != nullptr)
	    {
            dataStream << *node;
	    }
    }
}
