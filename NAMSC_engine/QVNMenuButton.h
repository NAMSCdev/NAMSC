#pragma once

#include <QPushButton>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>

class QVNMenuButton  : public QPushButton
{
	Q_OBJECT

public:
	QVNMenuButton(QWidget *parent);
	~QVNMenuButton();
	
	void loadImage(QString uri);
	QImage& getImage();
	void loadImageOnHover(QString uri);
	QImage& getImageOnHover();
	void setFontColor(QColor color);
	void setFontColorOnHover(QColor color);
	void drawText(QPainter& painter);

protected:
	void paintEvent(QPaintEvent*) override;
	void enterEvent(QEnterEvent*) override;
	void leaveEvent(QEvent*) override;
	void drawBody(QRect &borders, QPainter &painter);
	void drawImage(QRect &borders, QPainter &painter);

private:
	QColor fontColor;
	QColor fontOutlineColor;
	QColor fontHoverColor;
	bool changeFontColorOnHover = false;
	bool changeImageOnHover = false;
	std::shared_ptr<QImage> image;
	std::shared_ptr<QImage> imageOnHover;
	bool hover = false;
	//int heightForWidth(int w) override {

	//}
};
