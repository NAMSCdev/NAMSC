#pragma once

#include <QPushButton>
#include <qwidget.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qrect.h>

class QVNMenuButton  : public QPushButton
{
	Q_OBJECT

public:
	QVNMenuButton(QWidget *parent);
	~QVNMenuButton();
	QImage image;

protected:
	void paintEvent(QPaintEvent*) override;
	void enterEvent(QEnterEvent*) override;
	void leaveEvent(QEvent*) override;
};
