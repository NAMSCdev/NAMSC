#pragma once

#include <QGraphicsObject>
#include <QPen>
#include <QFont>

class GraphNodeBody : public QGraphicsObject
{
public:
	GraphNodeBody(QGraphicsObject *parent, QRectF bBox);
	~GraphNodeBody();

	// Inherited via QGraphicsItem
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	QString label;

	void setSelectedBorderPen();
	void setDefaultBorderPen();

private:
	qreal roundedCornersRadius = 10;
	QSizeF originalSize; // for potential rescaling due to connection point addition
	QRectF nodeBodyBoundingRect;
	QPen nodeBorderPen;
	QPen textPen = QColor{ 255, 255, 255 };
	QFont textFont = QFont("Calibri", 16);
};
