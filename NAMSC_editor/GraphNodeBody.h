#pragma once

#include <QGraphicsObject>
#include <QPen>

class GraphNodeBody : public QGraphicsObject
{
	Q_OBJECT

public:
	GraphNodeBody(QGraphicsObject *parent, QRectF bBox);
	~GraphNodeBody();

	// Inherited via QGraphicsItem
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	QString label;
private:
	QRectF nodeBodyBoundingRect;
	qreal roundedCornersRadius = 10;
};
