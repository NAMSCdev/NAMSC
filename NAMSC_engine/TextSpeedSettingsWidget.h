#pragma once

#include <QFrame>
#include "ui_TextSpeedSettingsWidget.h"

class TextSpeedSettingsWidget : public QFrame
{
	Q_OBJECT

public:
	TextSpeedSettingsWidget(QWidget *parent = nullptr);
	~TextSpeedSettingsWidget();

private:
	Ui::TextSpeedSettingsWidgetClass ui;
};
