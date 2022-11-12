#include "GraphConnectionPoint.h"
#include <QPainter>

GraphConnectionPoint::GraphConnectionPoint(QGraphicsObject* parent)
	: QGraphicsObject(parent), pointBoundingRect(0, 0, 10, 10)
{ 
	setAcceptHoverEvents(true);
	setFlag(ItemSendsScenePositionChanges);
}

GraphConnectionPoint::~GraphConnectionPoint()
{ }

QRectF GraphConnectionPoint::boundingRect() const
{
	return pointBoundingRect;
}

void GraphConnectionPoint::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->fillRect(pointBoundingRect, pointColor);
}

QVariant GraphConnectionPoint::itemChange(GraphicsItemChange change, const QVariant& value)
{
	if (change == ItemScenePositionHasChanged && arrow) {
		arrow->adjust();
	}

	return QGraphicsItem::itemChange(change, value);
}

void GraphConnectionPoint::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	pointColor = Qt::red;
	update();
}

void GraphConnectionPoint::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	pointColor = Qt::darkRed;
	update();
}

void GraphConnectionPoint::connectArrow(std::shared_ptr<GraphArrow> arrow)
{
	this->arrow = arrow;
}
