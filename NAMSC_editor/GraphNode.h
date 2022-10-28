#pragma once

#include <QGraphicsObject>
#include "GraphNodeBody.h"
#include "GraphConnectionPoint.h"

class GraphNode : public QGraphicsObject
{
public:
	GraphNode(QGraphicsObject *parent = nullptr);
	~GraphNode();

	// Inherited via QGraphicsItem
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void setLabel(QString label);

	void appendConnectionPoint(GraphConnectionType type);
	void insertConnectionPoint(GraphConnectionType type, size_t index);
	void removeConnectionPoint(GraphConnectionType type, size_t index);

	void connectPointTo(size_t index, GraphConnectionPoint* destination);
	void disconnectPoint(GraphConnectionType type, size_t index);

	std::shared_ptr<GraphConnectionPoint> connectionPointAt(GraphConnectionType type, size_t index);

private:
	QRectF nodeBoundingRect;
	GraphNodeBody nodeBody;
	QList<std::shared_ptr<GraphConnectionPoint>> inputConnectionPointList;
	QList<std::shared_ptr<GraphConnectionPoint>> outputConnectionPointList;

};
