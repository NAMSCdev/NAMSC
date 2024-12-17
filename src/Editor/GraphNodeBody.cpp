#include "GraphNodeBody.h"
#include <QPainter>

GraphNodeBody::GraphNodeBody(QGraphicsObject* parent, QRectF bBox)
	: QGraphicsObject(parent), nodeBodyBoundingRect(bBox)
{
	setDefaultBorderPen();
	//setParent(parent);
	//setFlag(ItemIsMovable);
	setFlag(ItemIsSelectable, false);
}

GraphNodeBody::~GraphNodeBody()
{ }

QRectF GraphNodeBody::boundingRect() const
{
	return nodeBodyBoundingRect;
}

void GraphNodeBody::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	//painter->setRenderHint(QPainter::Antialiasing);
	//prepareGeometryChange();

	// Draw nodebody
	QPainterPath path;
	path.addRoundedRect(nodeBodyBoundingRect, roundedCornersRadius, roundedCornersRadius);

	QBrush brush(QColor{ 100, 100, 100, 240 }, Qt::SolidPattern);

	// Draw body
	painter->setPen(nodeBorderPen);
	painter->fillPath(path, brush);
	painter->drawPath(path);

	// Draw text
	painter->setPen(textPen);
	painter->setFont(textFont);
	QFontMetrics metrics = painter->fontMetrics();
	QRect textboundingRect = boundingRect().toRect();
	painter->drawText(boundingRect().x(), boundingRect().y(), boundingRect().width(), boundingRect().height(), Qt::AlignCenter | Qt::TextWordWrap, label, &textboundingRect);
}

void GraphNodeBody::setSelectedBorderPen()
{
	nodeBorderPen = QPen(Qt::red, roundedCornersRadius);
	nodeBorderPen.setWidth(4);
	update();
}

void GraphNodeBody::setDefaultBorderPen()
{
	nodeBorderPen = QPen(Qt::black, roundedCornersRadius);
	nodeBorderPen.setWidth(1);
	update();
}
