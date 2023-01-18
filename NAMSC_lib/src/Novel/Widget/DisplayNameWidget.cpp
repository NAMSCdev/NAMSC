#include "Novel/Widget/DisplayNameWidget.h"

#include <QPainter>

#define RESOLUTION_X 1600.0
#define RESOLUTION_Y 900.0
#define WIDTH RESOLUTION_X * 0.75

DisplayNameWidget::DisplayNameWidget(const QString& text)
	: text(text)
{
	font_.setStyleHint(QFont::Helvetica, QFont::PreferAntialias);
	QFontMetrics metrics(font_);
	height_ = metrics.height();
	setMinimumSize(WIDTH, height_);
}

void DisplayNameWidget::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setPen(QColor(225, 209, 168, 210));
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setFont(font_);

	QTextOption options;
	options.setAlignment(Qt::AlignVCenter);

	painter->drawText(QRectF(0, 0, WIDTH, height_), text, options);
}