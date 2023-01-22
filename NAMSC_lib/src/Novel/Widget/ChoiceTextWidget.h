#pragma once
#include <QGraphicsWidget>
#include <QFont>

class ChoiceTextWidget : public QGraphicsWidget
{
	Q_OBJECT
public:
	ChoiceTextWidget(uint index, const QString& text, double width);
	ChoiceTextWidget(const ChoiceTextWidget&)            noexcept = delete;
	ChoiceTextWidget& operator=(const ChoiceTextWidget&) noexcept = delete;

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	QString text;

signals:
	void chosen(uint choiceID);

private:
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

	uint index_  = 0;

	bool bHover_ = false;

	QFont font_  = QFont("Fantasque Sans Mono", 24);
};
