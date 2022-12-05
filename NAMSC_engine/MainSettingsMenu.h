#pragma once

#include <QFrame>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include "VolumeSettingsWidget.h"
#include <QGraphicsProxyWidget>

class MainSettingsMenu  : public QGraphicsScene
{
	Q_OBJECT

public:
	MainSettingsMenu(QObject *parent);
	~MainSettingsMenu();

private:
	QGraphicsProxyWidget* settingsBox;
	VolumeSettingsWidget* volumeSettingsWidget;
	QHBoxLayout* settingsLayout;
	// TODO add vertical layout for each column

	void initializeSettingsBox();

private slots:
	void sceneRectChangedUpdate();
};
