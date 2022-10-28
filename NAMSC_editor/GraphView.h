#pragma once
#include <QGraphicsView>

class GraphView : public QGraphicsView
{
	Q_OBJECT

public:
	GraphView(QWidget* parent = nullptr);

public slots:
	void zoomIn();
	void zoomOut();

protected:
	void keyPressEvent(QKeyEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void drawBackground(QPainter* painter, const QRectF& rect) override;
	void scaleView(qreal scaleFactor);
};

