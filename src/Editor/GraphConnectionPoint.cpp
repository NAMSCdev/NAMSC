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

const QString GraphConnectionPoint::getSourceNodeName() const
{
	return arrow.get()->sourceNodeName;
}

const QString GraphConnectionPoint::getDestinationNodeName() const
{
	return arrow.get()->destinationNodeName;
}

void GraphConnectionPoint::setSourceNodeName(const QString& name)
{
	arrow.get()->sourceNodeName = name;
}

void GraphConnectionPoint::setDestinationNodeName(const QString& name)
{
	arrow.get()->destinationNodeName = name;
}

bool GraphConnectionPoint::isConnected() const
{
	return arrow.get() != nullptr;
}
