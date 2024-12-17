#include "pvnLib/Novel/Widget/ChoiceTextWidget.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#define RESOLUTION_X 1600.0
#define RESOLUTION_Y 900.0

ChoiceTextWidget::ChoiceTextWidget(uint index, const QString& text, double width)
	: index_(index),
	text(text)
{
	setAcceptHoverEvents(true);
	font_.setStyleHint(QFont::Helvetica, QFont::PreferAntialias);
	QFontMetrics metrics(font_);
	QRectF textRect = metrics.boundingRect(QRect(0, 0, static_cast<uint>(width), RESOLUTION_Y), Qt::TextWordWrap, text);

	setMinimumSize(width + 16.0, textRect.height() + 16.0);
}

void ChoiceTextWidget::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(bHover_ ? QPen(QColor(255, 249, 208, 255), 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin) : QPen(QColor(225, 209, 168, 235), 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter->setFont(font_);
	painter->setBrush(bHover_ ? QColor(80, 88, 97, 255) : QColor(80, 88, 97, 200));
	painter->drawRoundedRect(4.0, 4.0, rect().width() - 8.0, rect().height() - 8.0, 4.0, 4.0);

	QTextOption options;
	options.setAlignment(Qt::AlignCenter);
	painter->drawText(QRectF(8.0, 8.0, rect().width() - 16.0, rect().height() - 16.0), text, options);
}

void ChoiceTextWidget::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	QGraphicsWidget::hoverEnterEvent(event);
	bHover_ = true;
}

void ChoiceTextWidget::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	QGraphicsWidget::hoverLeaveEvent(event);
	bHover_ = false;
}

void ChoiceTextWidget::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
		emit chosen(index_);
}