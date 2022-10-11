#pragma once

#include <QObject>
#include <QGraphicsItem>
#include <QTextDocument>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QVariant>
#include <QFocusEvent>
#include <QApplication>

class TextBox : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	TextBox(QObject* parent);
	// TODO Decide on which constructors will be needed
	~TextBox();

	QRectF boundingBox;
	QRectF textBoundingBox;
	QRectF characterNameBoundingBox;

	QTextDocument text;
	QTextDocument characterName;

	QBrush brush;

	// Inherited via QGraphicsItem
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void setBoundingBoxSize(QSizeF size);
	void setBackground(QImage image);
	void setBackground(std::shared_ptr<QImage> imageptr);

	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
	void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
	void focusOutEvent(QFocusEvent* event) override;

private:
	enum class BoundingBoxMousePosition {
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
	} boundingBoxMousePosition = BoundingBoxMousePosition::None;

	static const size_t boxBorderActionSensitivity = 7;
	static const size_t boxBorderResizeActionSensitivity = 2;

	std::shared_ptr<QImage> image;
	QColor averageColor;

	inline auto   leftCheck(const QGraphicsSceneMouseEvent* const mouseEvent, const size_t& sensitivity) { return mouseEvent->pos().x() < sensitivity + boundingBox.x(); };
	inline auto  rightCheck(const QGraphicsSceneMouseEvent* const mouseEvent, const size_t& sensitivity) { return mouseEvent->pos().x() - boundingBox.x() > boundingBox.size().width() - sensitivity; };
	inline auto bottomCheck(const QGraphicsSceneMouseEvent* const mouseEvent, const size_t& sensitivity) { return mouseEvent->pos().y() - boundingBox.y() > boundingBox.size().height() - sensitivity; };
	inline auto  upperCheck(const QGraphicsSceneMouseEvent* const mouseEvent, const size_t& sensitivity) { return mouseEvent->pos().y() < sensitivity + boundingBox.y(); }

	inline auto   leftCheck(const QGraphicsSceneHoverEvent* const mouseEvent, const size_t& sensitivity) { return mouseEvent->pos().x() < sensitivity + boundingBox.x(); };
	inline auto  rightCheck(const QGraphicsSceneHoverEvent* const mouseEvent, const size_t& sensitivity) { return mouseEvent->pos().x() - boundingBox.x() > boundingBox.size().width() - sensitivity; };
	inline auto bottomCheck(const QGraphicsSceneHoverEvent* const mouseEvent, const size_t& sensitivity) { return mouseEvent->pos().y() - boundingBox.y() > boundingBox.size().height() - sensitivity; };
	inline auto  upperCheck(const QGraphicsSceneHoverEvent* const mouseEvent, const size_t& sensitivity) { return mouseEvent->pos().y() < sensitivity + boundingBox.y(); }

	void setAverageColor();
};
