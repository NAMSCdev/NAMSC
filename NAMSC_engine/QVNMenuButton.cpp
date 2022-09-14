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
	//QPushButton::paintEvent(event);
	QPainter painter = QPainter(this);
	QPainterPath textPath = QPainterPath();
	painter.setRenderHint(
		QPainter::Antialiasing
	);

	QPen pen;
	QBrush brush = QBrush();

	painter.setBrush(Qt::NoBrush);
	painter.setPen(Qt::black);
	painter.drawImage(buttonRect, image);
	painter.drawRect(0, 0, buttonRect.width()-1, buttonRect.height()-1);

	brush.setColor(Qt::darkRed);
	brush.setStyle(Qt::SolidPattern);
	pen.setColor(Qt::black);
	pen.setWidth(2);
	painter.setPen(pen);
	painter.setBrush(brush);
	QFont font(QPushButton::font().family(), QPushButton::height() * 0.7, 50, true);
	painter.setFont(font);
	QRect textBound = painter.fontMetrics().boundingRect(QPushButton::text());
	textPath.addText(
		(QPushButton::width() - textBound.width()) / 2,
		(QPushButton::height() + font.pointSize()) / 2,
		font,
		QPushButton::text());
	painter.drawPath(textPath);
}


void QVNMenuButton::enterEvent(QEnterEvent*) {
	image.rgbSwap();
}
void QVNMenuButton::leaveEvent(QEvent*) {
	image.rgbSwap();
}


