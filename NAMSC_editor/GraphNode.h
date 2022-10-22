#pragma once

#include <QGraphicsObject>
#include "GraphNodeBody.h"
#include "GraphConnectionPoint.h"

class GraphNode : public QGraphicsObject
{
	Q_OBJECT

public:
	GraphNode(QGraphicsObject *parent = nullptr);
	~GraphNode();

	// Inherited via QGraphicsItem
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void setLabel(QString label);

private:
	QRectF nodeBoundingRect;
	GraphNodeBody nodeBody;
	QList<std::shared_ptr<GraphConnectionPoint>> inputConnectionPointList;
	QList<std::shared_ptr<GraphConnectionPoint>> outputConnectionPointList;

};
