#pragma once

#include <qobject.h>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsObject>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>

class MainTextBox : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	MainTextBox(QWidget *parent);
	~MainTextBox();
	
	// Inherited via QGraphicsItem
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void setBoundingBoxSize(qreal x, qreal y);

	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);

private:
	enum class BoundingBoxPressedType {
		LeftBorder,
		RightBorder,
		UpperBorder,
		BottomBorder,
		LeftUpperCorner,
		RightUpperCorner,
		LeftBottomCorner,
		RightBottomCorner,
		Inside,
		None
	} boundingBoxPressedType;

	static const size_t boxBorderClickSensitivity = 5;
	static const size_t boxBorderResizeSensitivity = 2;

	QBrush testBrush;
	QRectF boundingBox;
	QString* currentText;

	inline auto   leftCheck(const QGraphicsSceneMouseEvent* const mouseEvent, const size_t& sensitivity) { return mouseEvent->pos().x() < sensitivity; };
	inline auto  rightCheck(const QGraphicsSceneMouseEvent* const mouseEvent, const size_t& sensitivity) { return mouseEvent->pos().x() > boundingBox.size().width() - sensitivity; };
	inline auto  upperCheck(const QGraphicsSceneMouseEvent* const mouseEvent, const size_t& sensitivity) { return mouseEvent->pos().y() > boundingBox.size().height() - sensitivity; };
	inline auto bottomCheck(const QGraphicsSceneMouseEvent* const mouseEvent, const size_t& sensitivity) { return mouseEvent->pos().y() < sensitivity; };

};
