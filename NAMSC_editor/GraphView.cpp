#include "GraphView.h"
#include <QKeyEvent>
#include <QMenu>
#include <ranges>
#include <QPointF>
#include "GraphNode.h"

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

GraphNode GraphView::getNodeByName(const QString& name)
{
    for (auto node : scene()->items())
    {
        auto castedNodePtr = qgraphicsitem_cast<GraphNode*>(node);
        if (castedNodePtr->getLabel() == name) return castedNodePtr;
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
    menu.exec(event->globalPos());

    qDebug() << scene()->itemAt(mapToScene(event->pos()), QTransform()); // Nodes detection
    qDebug() << scene()->focusItem(); // Nodes are usually focused welp
}

void GraphView::createContextMenu()
{
    createNodeAction = new QAction(tr("Create Node"), this);
    // createNodeAction->setShortcut();
    createNodeAction->setStatusTip(tr("Create node at the current cursor's position"));

    connect(createNodeAction, &QAction::triggered, this, &GraphView::createNode);
}

void GraphView::createNode()
{
    int step = 100;
    QPoint roundedPos = QPoint{ static_cast<int>(std::round(contextMenuPosition.x() / step)) * step, static_cast<int>(std::round(contextMenuPosition.y() / step)) * step };
    scene()->addItem(new GraphNode(roundedPos));
}
