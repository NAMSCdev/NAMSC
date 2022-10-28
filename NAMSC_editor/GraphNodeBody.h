#pragma once

#include <QGraphicsObject>
#include <QPen>

class GraphNodeBody : public QGraphicsObject
{
public:
	GraphNodeBody(QGraphicsObject *parent, QRectF bBox);
	~GraphNodeBody();

	// Inherited via QGraphicsItem
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	QString label;

private:
	QSizeF originalSize; // for potential rescaling due to connection point addition
	QRectF nodeBodyBoundingRect;
	qreal roundedCornersRadius = 10;
};
