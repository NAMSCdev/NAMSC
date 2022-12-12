#pragma once

#include <QFrame>
#include "ui_ScreenModeSettingsWidget.h"

class ScreenModeSettingsWidget : public QFrame
{
	Q_OBJECT

public:
	ScreenModeSettingsWidget(QWidget *parent = nullptr);
	~ScreenModeSettingsWidget();

	void setListener(QObject* receiver, std::function<void(int)> onClicked);

private:
	Ui::ScreenModeSettingsWidgetClass ui;
};
