#pragma once

#include <QFrame>
#include "ui_LanguageSettingsWidget.h"

class LanguageSettingsWidget : public QFrame
{
	Q_OBJECT

public:
	LanguageSettingsWidget(QWidget *parent = nullptr);
	~LanguageSettingsWidget();

private:
	Ui::LanguageSettingsWidgetClass ui;
};
