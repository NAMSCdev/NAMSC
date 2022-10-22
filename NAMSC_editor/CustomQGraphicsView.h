#pragma once

#include <QGraphicsView>

class CustomQGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	CustomQGraphicsView(QWidget *parent);
	
    qreal panSpeed;
    qreal zoomDelta;
    qreal zoomKey;
    Qt::MouseButton panButton;

    void pan(QPointF delta);
    void zoom(float scaleFactor);
    void zoomIn();
    void zoomOut();

    qreal getScale() const;

protected:

    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;

    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent*) override;

private:

    // Flags to determine if zooming or panning should be done.
    bool _doMousePanning;
    bool _doKeyZoom;

    QPoint _lastMousePos;
    qreal _scale;

    void setMaxSize();

};
