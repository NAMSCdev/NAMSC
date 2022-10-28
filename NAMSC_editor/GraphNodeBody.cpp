#include "GraphNodeBody.h"
#include <QPainter>

GraphNodeBody::GraphNodeBody(QGraphicsObject* parent, QRectF bBox)
	: QGraphicsObject(parent), nodeBodyBoundingRect(bBox)
{
	//setParent(parent);
	//setFlag(ItemIsMovable);
	// TODO
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

	QPen pen(Qt::black, roundedCornersRadius);
	pen.setWidth(1);

	QBrush brush(QColor{ 100, 100, 100, 240 }, Qt::SolidPattern);
	//QLinearGradient gradient(QPointF(0.0, 0.0), QPointF(2.0, nodeBodyBoundingRect.height()));

	//gradient.setColorAt(0.0, Qt::white);
	//gradient.setColorAt(0.08, Qt::gray);
	//gradient.setColorAt(0.97, Qt::gray);
	//gradient.setColorAt(1.0, Qt::black);

	painter->setPen(pen);
	//painter->fillPath(path, gradient);
	painter->fillPath(path, brush);
	painter->drawPath(path);

	// Draw text
	QFont font = QFont("Calibri", 16);
	painter->setPen(QColor{ 255, 255, 255 });
	painter->setFont(font);
	QFontMetrics metrics = painter->fontMetrics();
	QRect textboundingRect = boundingRect().toRect();
	painter->drawText(0, 0, boundingRect().width(), boundingRect().height(), Qt::AlignCenter | Qt::TextWordWrap, label, &textboundingRect);
}