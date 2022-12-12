#pragma once

#include <QFrame>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "VolumeSettingsWidget.h"
#include <QGraphicsProxyWidget>

#include "LanguageSettingsWidget.h"
#include "ScreenModeSettingsWidget.h"
#include "TextSpeedSettingsWidget.h"

class MainSettingsMenu  : public QGraphicsScene
{
	Q_OBJECT

public:
	MainSettingsMenu(QObject *parent);
	~MainSettingsMenu();

	void setScreenModeSettingsListener(QObject* receiver, std::function<void(int)> onClicked);

private:
	QImage* background;
	QGraphicsProxyWidget* settingsBox;
	VolumeSettingsWidget* volumeSettingsWidget;
	TextSpeedSettingsWidget* textSpeedSettingsWidget;
	ScreenModeSettingsWidget* screenModeSettingsWidget;
	LanguageSettingsWidget* languageSettingsWidget;
	QHBoxLayout* settingsLayout;
	QVBoxLayout* leftColumnLayout;
	QVBoxLayout* rightColumnLayout;
	
	void initializeSettingsBox();

private slots:
	void sceneRectChangedUpdate();
};
