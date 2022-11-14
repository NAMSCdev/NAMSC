#include "GraphView.h"
#include <QKeyEvent>
#include <ranges>
#include <QPointF>

GraphView::GraphView(QWidget* parent) : QGraphicsView(parent)
{
	setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);
    setDragMode(ScrollHandDrag);
}

void GraphView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);

    if (event->button() == Qt::MiddleButton)
    {
        // Store original position.
        mousePressOrigin = mapToScene(event->pos());
        qDebug() << "Middle button registered, pos: " << mousePressOrigin;
    }
}

void GraphView::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);

    if (scene()->mouseGrabberItem() == nullptr && event->buttons() == Qt::MiddleButton)
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

void GraphView::zoomIn()
{
    scaleView(qreal(1.1));
}

void GraphView::zoomOut()
{
    scaleView(1 / qreal(1.1));
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
    //Q_UNUSED(rect);

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
    QLine hline({ (int)visibleArea.x() - ((int)visibleArea.x() % step) - step, (int)visibleArea.y() - ((int)visibleArea.y() % step)}, {(int)visibleArea.x() + (int)visibleArea.width(), (int)visibleArea.y() - ((int)visibleArea.y() % step)});
    for (int i = 0; i < visibleArea.height(); i += step) {
        painter->drawLine(hline);
        hline.translate(0, step);
    }
    // Vertical
    QLine vline({ (int)visibleArea.x() - ((int)visibleArea.x() % step), (int)visibleArea.y() - ((int)visibleArea.y() % step) - step}, {(int)visibleArea.x() - ((int)visibleArea.x() % step), (int)visibleArea.y() + (int)visibleArea.height()});
    for (int i = 0; i < visibleArea.width(); i += step) {
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
