#include "SceneryObjectOnSceneProperties.h"

SceneryObjectOnSceneProperties::SceneryObjectOnSceneProperties(SceneryObject* sceneryObject, QWidget *parent)
	: QFrame(parent), sceneryObject(sceneryObject)
{
	ui.setupUi(this);

	ui.sceneryObjectCollapseButton->setContent(ui.sceneryObjectContent);
	ui.sceneryObjectCollapseButton->setText(tr("Position on the scene"));
	if (expanded) ui.sceneryObjectCollapseButton->toggle();

	prepareDataInUi();
	prepareConnections();
}

SceneryObjectOnSceneProperties::~SceneryObjectOnSceneProperties()
{}

void SceneryObjectOnSceneProperties::prepareConnections()
{
	connect(ui.sceneryObjectCollapseButton, &CollapseButton::clicked, this, [] { expanded = !expanded; });

	connect(ui.xPositionSpinBox, &QSpinBox::valueChanged, this, &SceneryObjectOnSceneProperties::updatePosX);
	connect(ui.yPositionSpinBox, &QSpinBox::valueChanged, this, &SceneryObjectOnSceneProperties::updatePosY);
}

void SceneryObjectOnSceneProperties::prepareDataInUi()
{
	ui.xPositionSpinBox->setValue(sceneryObject->pos.x());
	ui.yPositionSpinBox->setValue(sceneryObject->pos.y());
}

void SceneryObjectOnSceneProperties::updatePosX(int val)
{
	sceneryObject->pos.setX(val);
}

void SceneryObjectOnSceneProperties::updatePosY(int val)
{
	sceneryObject->pos.setY(val);
}