#pragma once

#include <QGraphicsObject>

class GraphArrow : public QGraphicsObject
{
	Q_OBJECT

public:
	GraphArrow(QObject *parent);
	~GraphArrow();

	// Inherited via QGraphicsItem
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};
