#pragma once

#include <QGraphicsObject>

class GraphConnectionPoint;

class GraphArrow : public QGraphicsObject
{
public:
	GraphArrow(QGraphicsObject *parent);
	GraphArrow(GraphConnectionPoint* source, GraphConnectionPoint* dest);
	~GraphArrow();

	//void setSourcePoint(const QPointF point);
	//void setDestinationPoint(const QPointF point);

	void adjust();

	// Inherited via QGraphicsItem
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
	QPointF sourcePoint;
	QPointF destinationPoint;

	GraphConnectionPoint* connectionSource;
	GraphConnectionPoint* connectionDestination;
};
