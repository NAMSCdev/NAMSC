#pragma once

#include <QFrame>
#include "ui_SceneryObjectTreeProperties.h"
#include "Novel/Data/Visual/Scenery/SceneryObject.h"

class SceneryObjectTreeProperties : public QFrame
{
	Q_OBJECT

public:
	SceneryObjectTreeProperties(SceneryObject* sceneryObject, QWidget *parent = nullptr);
	~SceneryObjectTreeProperties();

private:
	void prepareConnections();
	void prepareDataInUi();
	SceneryObject* sceneryObject;

	Ui::SceneryObjectTreePropertiesClass ui;

private slots:
	void updateScaleX(double x);
	void updateScaleY(double y);
	void updateAlphaMultiplier(double multiplier);
	void updateRotation(double rotation);
};
