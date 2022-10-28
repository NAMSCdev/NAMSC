#pragma once

#include <QGraphicsObject>
#include "GraphArrow.h"

enum class GraphConnectionType {
	In,
	Out,
	None
};

class GraphConnectionPoint : public QGraphicsObject
{
	Q_OBJECT

public:
	GraphConnectionPoint(QGraphicsObject* parent = nullptr);
	~GraphConnectionPoint();

	// Inherited via QGraphicsItem
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
	
	void connectArrow(std::shared_ptr<GraphArrow> arrow);

private:
	QRectF pointBoundingRect;
	QColor pointColor = Qt::darkRed;
	std::shared_ptr<GraphArrow> arrow;
};
