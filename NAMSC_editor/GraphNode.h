#pragma once

#include <QGraphicsObject>
#include "GraphNodeBody.h"
#include "GraphConnectionPoint.h"
#include "Novel/Data/Scene.h"

class GraphNode : public QGraphicsObject
{
	Q_OBJECT

public:
	GraphNode(QGraphicsObject *parent = nullptr);
	GraphNode(const QPoint& pos, QGraphicsObject* parent = nullptr);
	~GraphNode();

	// Inherited via QGraphicsItem
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

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

	QString getLabel() const;

public slots:
	void setLabel(QString label);

	signals:
		void nodeDoubleClicked(GraphNode* node);

private:
	QRectF nodeBoundingRect;
	QPointF lastLeftMousePressPoint;
	GraphNodeBody nodeBody;
	Scene gameScene;
	QList<std::shared_ptr<GraphConnectionPoint>> inputConnectionPointList;
	QList<std::shared_ptr<GraphConnectionPoint>> outputConnectionPointList;

	void setFlags();

};
