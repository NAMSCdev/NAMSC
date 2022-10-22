#include "GraphConnectionPoint.h"

GraphConnectionPoint::GraphConnectionPoint(QObject *parent)
	: QGraphicsObject(this)
{ }

GraphConnectionPoint::~GraphConnectionPoint()
{ }

QRectF GraphConnectionPoint::boundingRect() const
{
	return QRectF();
}

void GraphConnectionPoint::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
}
