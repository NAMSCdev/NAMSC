#include "VNButton.h"

#include <QPainter>
#include <QPainterPath>
#include <QDebug>

VNButton::VNButton(QWidget *parent)
	: QAbstractButton(parent)
{
	setFixedSize(QSize(150, 50));
	isHovering = false;
	acceptHover = false;
	isPressed = false;
}

VNButton::~VNButton()
{}

void VNButton::setImage(const QImage& image)
{
	buttonImage.reset(new QImage(image));
}

QImage& VNButton::getImage() const
{
	return *buttonImage;
}

void VNButton::setFont(const QFont& font)
{
	this->font.reset(new QFont(font));
}

const QFont& VNButton::getFont() const
{
	return *font;
}

void VNButton::setTextColor(const QColor& color)
{
	textColor.reset(new QColor(color));
}

const QColor& VNButton::getTextColor() const
{
	return *textColor;
}

void VNButton::setHover(bool b)
{
	acceptHover = b;
}

void VNButton::paintEvent(QPaintEvent* e)
{
	QPainter painter = QPainter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	drawBody(&painter);
	drawText(&painter);
}

void VNButton::enterEvent(QEnterEvent* event)
{
	isHovering = true;
	// TODO !MVP - hover sound effect
	QAbstractButton::enterEvent(event);
}

void VNButton::leaveEvent(QEvent* event)
{
	isHovering = false;
	QAbstractButton::leaveEvent(event);
}

void VNButton::mousePressEvent(QMouseEvent* e)
{
	isPressed = true;

	QAbstractButton::mousePressEvent(e);
}

void VNButton::mouseReleaseEvent(QMouseEvent* e)
{
	isPressed = false;
	// TODO !MVP - mouse release sound effect
	QAbstractButton::mouseReleaseEvent(e);
}

void VNButton::drawBody(QPainter* painter)
{
	// Default buttonImage
	if (buttonImage.isNull())
	{
		buttonImage.reset(new QImage(size(), QImage::Format_RGBA16FPx4));
		buttonImage->fill(Qt::gray);
	}

	// Default hoverButtonImage
	if (hoverButtonImage.isNull() && acceptHover)
	{
		hoverButtonImage.reset(new QImage(size(), QImage::Format_RGBA16FPx4));
		hoverButtonImage->fill(Qt::darkGray);
	}

	// Default pressedButtonImage
	if (pressedButtonImage.isNull())
	{
		pressedButtonImage.reset(new QImage(size(), QImage::Format_RGBA16FPx4));
		pressedButtonImage->fill(QColor(Qt::darkGray).darker(120));
	}

	if (isPressed)
	{
		painter->drawImage(rect(), *pressedButtonImage);
	}
	else if (acceptHover && isHovering)
	{
		painter->drawImage(rect(), *hoverButtonImage);
	}
	else
	{
		painter->drawImage(rect(), *buttonImage);
	}
}

void VNButton::drawText(QPainter* painter)
{
	if (not text().isNull())
	{
		if (font.isNull())
		{
			font.reset(new QFont("Calibri"));
		}

		QPainterPath textPath = QPainterPath();

		QBrush brush = QBrush();
		brush.setColor(textColor.isNull() ? Qt::black : *textColor);
		brush.setStyle(Qt::SolidPattern);

		QFontMetricsF textMetrics = QFontMetricsF(*font);
		QRectF textBoundingRect = textMetrics.boundingRect(text());

		textPath.addText(rect().center() - textBoundingRect.center(), *font, text());
	
		painter->setBrush(brush);

		painter->drawPath(textPath);
	}
}
