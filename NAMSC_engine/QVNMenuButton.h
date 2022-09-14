#pragma once

#include <QPushButton>
#include <qwidget.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qrect.h>

class QVNMenuButton  : public QPushButton
{
	Q_OBJECT

private:
	QColor fontColor;
	QColor fontOutlineColor;
	QColor fontHoverColor;
	bool changeFontColorOnHover = false;
	bool changeImageOnHover = false;
	std::shared_ptr<QImage> image;
	std::shared_ptr<QImage> imageOnHover;
	bool hover = false;
	int heightForWidth(int w) override {

	}
public:
	QVNMenuButton(QWidget *parent);
	~QVNMenuButton();
protected:
	void paintEvent(QPaintEvent*) override;
	void enterEvent(QEnterEvent*) override;
	void leaveEvent(QEvent*) override;
	void drawBody(QRect &borders, QPainter &painter);
	void drawImage(QRect &borders, QPainter &painter);
	void drawText(QPainter& painter);
public:
	void loadImage(QString uri);
	QImage& getImage();
	void loadImageOnHover(QString uri);
	QImage& getImageOnHover();
	void setFontColor(QColor color);
	void setFontColorOnHover(QColor color);
};
