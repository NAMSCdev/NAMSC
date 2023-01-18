#pragma once
#include <QGraphicsWidget>

class DisplayTextWidget : public QGraphicsWidget
{
public:
	DisplayTextWidget(const QString& text);
	DisplayTextWidget(const DisplayTextWidget&)            = delete;
	DisplayTextWidget& operator=(const DisplayTextWidget&) = delete;

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	QString text;

private:
	QFont   font_   = QFont("Fantasque Sans Mono", 24);
	int     height_ = 0;
};
