#pragma once
#include <QGraphicsView>

class GraphView : public QGraphicsView
{
	Q_OBJECT

public:
	GraphView(QWidget* parent = nullptr);

	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

public slots:
	void zoomIn();
	void zoomOut();

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

private slots:
	void createNode();
};

