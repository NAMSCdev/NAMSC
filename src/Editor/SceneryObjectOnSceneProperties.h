#pragma once

#include <QFrame>
#include "ui_SceneryObjectOnSceneProperties.h"
#include "pvnlib/Novel/Data/Visual/Scenery/SceneryObject.h"

class SceneryObjectOnSceneProperties : public QFrame
{
	Q_OBJECT

public:
	SceneryObjectOnSceneProperties(SceneryObject* sceneryObject, QWidget *parent = nullptr);
	~SceneryObjectOnSceneProperties();

private:
	Ui::SceneryObjectOnScenePropertiesClass ui;

	void prepareConnections();
	void prepareDataInUi();
	SceneryObject* sceneryObject;

	inline static bool expanded = false;

private slots:
	void updatePosX(int val);
	void updatePosY(int val);
};
