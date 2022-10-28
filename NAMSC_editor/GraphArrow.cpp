#include "GraphArrow.h"
#include <QPainter>
#include "GraphConnectionPoint.h"

GraphArrow::GraphArrow(GraphConnectionPoint* source, GraphConnectionPoint* dest)
	: QGraphicsObject(nullptr), connectionSource(source), connectionDestination(dest)
{
	adjust();
}

GraphArrow::~GraphArrow()
{ }

//void GraphArrow::setSourcePoint(const QPointF point)
//{
//	sourcePoint = point;
//}
//
//void GraphArrow::setDestinationPoint(const QPointF point)
//{
//	destinationPoint = point;
//}

void GraphArrow::adjust()
{
	if (not connectionSource || not connectionDestination) {
		return;
	}


	QLineF line(mapFromScene(connectionSource->scenePos()), mapFromScene(connectionDestination->scenePos()));
	qreal length = line.length();

	prepareGeometryChange();
	
	QSizeF edgeOffset(connectionSource->boundingRect().size() / 2);
	sourcePoint = line.p1() + QPointF{ edgeOffset.width(), edgeOffset.height() };
	destinationPoint = line.p2() + QPointF{ edgeOffset.width(), edgeOffset.height() };
}

QRectF GraphArrow::boundingRect() const
{
	if (not connectionSource || not connectionDestination)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth) / 2.0;

    return QRectF(sourcePoint, QSizeF(destinationPoint.x() - sourcePoint.x(),
                                      destinationPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void GraphArrow::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (not connectionSource || not connectionDestination) {
		return;
	}

	QLineF line(sourcePoint, destinationPoint);
	if (qFuzzyCompare(line.length(), qreal(0.)))
		return;

	// Draw the line itself
	//painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter->drawLine(line);

	qDebug() << "XD";
}
