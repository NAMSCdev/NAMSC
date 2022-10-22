#pragma once

#include <QGraphicsObject>
#include "GraphArrow.h"

class GraphConnectionPoint : public QGraphicsObject
{
	Q_OBJECT

public:
	GraphConnectionPoint(QObject *parent);
	~GraphConnectionPoint();

	// Inherited via QGraphicsItem
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
	QRectF pointBoundingRect;
	QList<GraphArrow> arrowList;
};
