#include "QVNMenuButton.h"
#include "qpainter.h"
#include "qimage.h"
#include "qstring.h"
#include "qevent.h"
#include "qpainterpath.h"
#include <QFontDatabase>

QVNMenuButton::QVNMenuButton(QWidget *parent)
	: QPushButton(parent){
	fontColor = Qt::black;
	fontOutlineColor = Qt::white;
}

QVNMenuButton::~QVNMenuButton()
{}

void QVNMenuButton::paintEvent(QPaintEvent* event) {
	QRect buttonRect = QRect(0, 0, QPushButton::width(), QPushButton::height());
	QPainter painter = QPainter(this);
	painter.setRenderHint(
		QPainter::Antialiasing
	);
	drawBody(buttonRect, painter);
	drawText(painter);
}

void QVNMenuButton::drawBody(QRect& borders, QPainter& painter) {
	drawImage(borders, painter);
	QPen pen;
	QBrush brush = QBrush();
	painter.setBrush(Qt::NoBrush);
	painter.setPen(Qt::black);
	painter.drawRect(0, 0, borders.width() - 1, borders.height() - 1);
}

void QVNMenuButton::drawImage(QRect& borders, QPainter& painter) {
	painter.drawImage(
		borders,
		(hover && changeImageOnHover)
			? getImageOnHover()
			: getImage()
	);
}

void QVNMenuButton::drawText(QPainter& painter) {
	QPainterPath textPath = QPainterPath();
	QPen pen;
	QBrush brush = QBrush();
	brush.setColor(
		(hover && changeImageOnHover) 
			? fontHoverColor
			: fontColor
	);
	brush.setStyle(Qt::SolidPattern);
	pen.setColor(fontOutlineColor);
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
	hover = true;
}
void QVNMenuButton::leaveEvent(QEvent*) {
	hover = false;
}

void QVNMenuButton::loadImage(QString uri) {
	image = std::make_shared<QImage>(QImage(uri));
	if (image.get()->isNull()) throw std::invalid_argument("Missing image " + uri.toStdString());
};

QImage& QVNMenuButton::getImage()
{
	return *image;
};

void QVNMenuButton::loadImageOnHover(QString uri) {
	imageOnHover = std::make_shared<QImage>(QImage(uri));
	if (imageOnHover.get()->isNull()) throw std::invalid_argument("Missing image " + uri.toStdString());
	changeImageOnHover = true;
};

QImage& QVNMenuButton::getImageOnHover()
{
	return *imageOnHover;
};


void QVNMenuButton::setFontColor(QColor color) {
	fontColor = color;
};

void QVNMenuButton::setFontColorOnHover(QColor color) {
	fontHoverColor = color;
	changeFontColorOnHover = true;
};

