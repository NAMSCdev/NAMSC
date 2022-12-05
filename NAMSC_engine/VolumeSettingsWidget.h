#pragma once

#include <QFrame>
#include "ui_VolumeSettingsWidget.h"

class VolumeSettingsWidget : public QFrame
{
	Q_OBJECT

public:
	VolumeSettingsWidget(QWidget *parent = nullptr);
	~VolumeSettingsWidget();

private:
	Ui::VolumeSettingsWidgetClass ui;
};
