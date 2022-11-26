#pragma once

#include <QGraphicsObject>
#include "GraphNodeBody.h"
#include "GraphConnectionPoint.h"

class GraphNode : public QGraphicsObject
{
public:
	GraphNode(QGraphicsObject *parent = nullptr);
	GraphNode(const QPoint& pos, QGraphicsObject* parent = nullptr);
	~GraphNode();

	// Inherited via QGraphicsItem
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void setLabel(QString label);

	void appendConnectionPoint(GraphConnectionType type);
	void insertConnectionPoint(GraphConnectionType type, size_t index);
	void removeConnectionPoint(GraphConnectionType type, size_t index);

	void connectPointTo(size_t index, GraphConnectionPoint* destination);
	void disconnectPoint(GraphConnectionType type, size_t index);

	std::shared_ptr<GraphConnectionPoint> connectionPointAt(GraphConnectionType type, size_t index);

	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

	void focusOutEvent(QFocusEvent* event) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
	QRectF nodeBoundingRect;
	QPointF lastLeftMousePressPoint;
	GraphNodeBody nodeBody;
	// TODO there should be a pointer to the in game scene
	QList<std::shared_ptr<GraphConnectionPoint>> inputConnectionPointList;
	QList<std::shared_ptr<GraphConnectionPoint>> outputConnectionPointList;

	void setFlags();

};
