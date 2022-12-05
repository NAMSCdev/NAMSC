#pragma once

#include <QAbstractButton>
#include <QScopedPointer>

class VNButton final : public QAbstractButton
{
	Q_OBJECT

public:
	VNButton(QWidget *parent);
	~VNButton();

	void setImage(const QImage& image);
	QImage& getImage() const;

	void setFont(const QFont& font);
	const QFont& getFont() const;

	void setTextColor(const QColor& color);
	const QColor& getTextColor() const;

	void setHover(bool b);

	// TODO? Text outline color
	// TODO? Text hover color

protected:
	void paintEvent(QPaintEvent* e) override;
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent* e) override;

private:
	bool acceptHover;
	bool isHovering;
	bool isPressed;
	QScopedPointer<QColor> textColor;
	QScopedPointer<QFont> font;
	QScopedPointer<QImage> buttonImage;
	QScopedPointer<QImage> hoverButtonImage;
	QScopedPointer<QImage> pressedButtonImage;

	void drawBody(QPainter* painter);
	void drawText(QPainter* painter);
};
