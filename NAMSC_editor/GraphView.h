#pragma once
#include <QGraphicsView>

#include "GraphNode.h"
#include "Serialization.h"

class GraphView : public QGraphicsView
{
	Q_OBJECT

public:
	GraphView(QWidget* parent = nullptr);

	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	GraphNode* getNodeByName(const QString& name);

public slots:
	void zoomIn();
	void zoomOut();
	void passNodeDoubleClick(GraphNode* node);

	signals:
	void nodeDoubleClicked(GraphNode* node);
	void nodeDeleted();

protected:
	void keyPressEvent(QKeyEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void drawBackground(QPainter* painter, const QRectF& rect) override;
	void scaleView(qreal scaleFactor);
	void contextMenuEvent(QContextMenuEvent* event) override;

private:
	void createContextMenu();

	QPointF mousePressOrigin;
	QPointF contextMenuPosition;

	QAction* createNodeAction;
	QAction* removeNodeAction;

private slots:
	void createNode();
	void removeNode();


public:
	void serializableLoad(QDataStream& dataStream);
	void serializableSave(QDataStream& dataStream) const;
};

