#include "QVNMenuButton.h"
#include "qpainter.h"
#include "qimage.h"
#include "qstring.h"
#include "qevent.h"
#include "qpainterpath.h"

QVNMenuButton::QVNMenuButton(QWidget *parent)
	: QPushButton(parent){
}

QVNMenuButton::~QVNMenuButton()
{}

void QVNMenuButton::paintEvent(QPaintEvent* event) {
	QRect buttonRect = QRect(0, 0, QPushButton::width(), QPushButton::height());
	QPushButton::paintEvent(event);
	QPainter imagePainter = QPainter(this);
	QPainter textPainter = QPainter(this);
	QPainterPath textPath = QPainterPath();

	QPen pen;
	QBrush brush = QBrush();
	brush.setColor(Qt::darkRed);
	brush.setStyle(Qt::SolidPattern);
	pen.setColor(Qt::black);
	pen.setWidth(2);
	textPainter.setPen(pen);
	textPainter.setBrush(brush);
	QFont font(QPushButton::font().family(), 72, 50, true);
	textPainter.setFont(font);
	QRect textBound = textPainter.fontMetrics().boundingRect(QPushButton::text());
	textPath.addText(
		(QPushButton::width()-textBound.width())/2,
		(QPushButton::height()/+textBound.height())/2,
		font,
		QPushButton::text());
	textPath.boundingRect();
	
	imagePainter.drawImage(buttonRect, image);
	textPainter.drawPath(textPath);
}


void QVNMenuButton::enterEvent(QEnterEvent*) {
	image.rgbSwap();
}
void QVNMenuButton::leaveEvent(QEvent*) {
	image.rgbSwap();
}


