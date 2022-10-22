#include "GraphArrow.h"

GraphArrow::GraphArrow(QObject *parent)
	: QGraphicsObject(this)
{ }

GraphArrow::~GraphArrow()
{ }

QRectF GraphArrow::boundingRect() const
{
	return QRectF();
}

void GraphArrow::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
}
