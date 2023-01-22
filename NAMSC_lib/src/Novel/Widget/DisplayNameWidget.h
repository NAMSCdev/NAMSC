#pragma once
#include <QGraphicsWidget>
#include <QFont>

class DisplayNameWidget final : public QGraphicsWidget
{
public:
	explicit DisplayNameWidget(const QString& text);
	DisplayNameWidget(const DisplayNameWidget&)            = delete;
	DisplayNameWidget& operator=(const DisplayNameWidget&) = delete;

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

	QString text;

private:
	QFont font_ = QFont("Fantasque Sans Mono", 40, -1, true);
};
