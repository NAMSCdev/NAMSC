#include "Novel/Widget/DisplayTextWidget.h"

#include <QPainter>

#define RESOLUTION_X 1600.0
#define RESOLUTION_Y 900.0
#define WIDTH RESOLUTION_X * 0.75
#define ADDITIONAL_LINES 5

DisplayTextWidget::DisplayTextWidget(const QString& text)
	: text(text)
{
	font_.setStyleHint(QFont::Helvetica, QFont::PreferAntialias);
	QFontMetrics metrics(font_);
	setMinimumSize(WIDTH, metrics.height() + metrics.lineSpacing() * ADDITIONAL_LINES);
}

void DisplayTextWidget::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setPen(QColor(225, 209, 168, 235));
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setFont(font_);
	painter->drawText(QRectF(8.0, 0.0, rect().width() - 8.0, rect().height()), text);
}