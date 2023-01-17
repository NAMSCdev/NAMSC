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
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
	
	void connectArrow(std::shared_ptr<GraphArrow> arrow);
	const QString getSourceNodeName() const;
	const QString getDestinationNodeName() const;

	void setSourceNodeName(const QString& name);
	void setDestinationNodeName(const QString& name);

	bool isConnected() const;

	std::shared_ptr<GraphArrow> arrow;

private:
	QRectF pointBoundingRect;
	QColor pointColor = Qt::darkRed;
	
};
