#pragma once

#include <QGraphicsObject>
#include "GraphNodeBody.h"
#include "GraphConnectionPoint.h"
#include "Novel/Data/Scene.h"

#include "Serialization.h"

class GraphNode : public QGraphicsObject
{
	Q_OBJECT

public:
	GraphNode(QGraphicsObject *parent = nullptr);
	GraphNode(const QPoint& pos, QGraphicsObject* parent = nullptr);
	~GraphNode();

	// Inherited via QGraphicsObject
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	QList<std::shared_ptr<GraphConnectionPoint>> getConnectionPoints(GraphConnectionType type);
	std::shared_ptr<GraphConnectionPoint> appendConnectionPoint(GraphConnectionType type);
	void insertConnectionPoint(GraphConnectionType type, size_t index);
	void removeConnectionPoint(GraphConnectionType type, size_t index);

	bool removeConnectionPoint(std::shared_ptr<GraphConnectionPoint> point);

	void connectPointTo(std::shared_ptr<GraphConnectionPoint> source, std::shared_ptr<GraphConnectionPoint> destination);
	void disconnectPoint(GraphConnectionType type, size_t index);

	std::shared_ptr<GraphConnectionPoint> connectionPointAt(GraphConnectionType type, size_t index);

	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

	void focusOutEvent(QFocusEvent* event) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

	QString getLabel() const;
	// Assuming names are unique, otherwise will connect to first found
	// Connects this node to nodeName. It only connects it on the graph and does not do it in the lib
	bool connectToNode(QString nodeName);
	// Disconnects only from output nodes
	// Disconnects this node from nodeName. It only disconnects it on the graph and does not do it in the lib
	bool disconnectFrom(QString nodeName);
	
public slots:
	void setLabel(QString label);

	signals:
		void nodeDoubleClicked(GraphNode* node);

private:
	QRectF nodeBoundingRect;
	QPointF lastLeftMousePressPoint;
	GraphNodeBody nodeBody;
	QList<std::shared_ptr<GraphConnectionPoint>> inputConnectionPointList;
	QList<std::shared_ptr<GraphConnectionPoint>> outputConnectionPointList;

	void setFlags();


public:
	void serializableLoad(QDataStream& dataStream);
	void serializableSave(QDataStream& dataStream) const;
};
