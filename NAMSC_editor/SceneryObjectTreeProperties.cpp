#include "SceneryObjectTreeProperties.h"

SceneryObjectTreeProperties::SceneryObjectTreeProperties(SceneryObject* sceneryObject, QWidget *parent)
	: QFrame(parent), sceneryObject(sceneryObject)
{
	ui.setupUi(this);
	ui.sceneryObjectTreeItemContent->setGeometry({ {0, 0}, ui.sceneryObjectCollapseButtonContent->totalSizeHint() });
	ui.sceneryObjectCollapseButton->setContent(ui.sceneryObjectTreeItemContent);
	//qDebug() << "size hint: " << ui.sceneryObjectCollapseButtonContent->totalSizeHint();
	ui.sceneryObjectCollapseButton->setText("Object properties");

	prepareDataInUi();
	prepareConnections();
}

SceneryObjectTreeProperties::~SceneryObjectTreeProperties()
{}

void SceneryObjectTreeProperties::prepareConnections()
{
	connect(ui.scaleXDoubleSpinBox, &QDoubleSpinBox::valueChanged, this, &SceneryObjectTreeProperties::updateScaleX);
	connect(ui.scaleYDoubleSpinBox, &QDoubleSpinBox::valueChanged, this, &SceneryObjectTreeProperties::updateScaleY);

	connect(ui.alphaMultipierSpinBox, &QSpinBox::valueChanged, this, &SceneryObjectTreeProperties::updateAlphaMultiplier);
	connect(ui.rotationSpinBox, &QSpinBox::valueChanged, this, &SceneryObjectTreeProperties::updateRotation);
}

void SceneryObjectTreeProperties::prepareDataInUi()
{
	ui.scaleXDoubleSpinBox->setValue(sceneryObject->scale.width());
	ui.scaleYDoubleSpinBox->setValue(sceneryObject->scale.height());

	ui.alphaMultipierSpinBox->setValue(static_cast<int>(sceneryObject->alphaMultiplier));
	ui.rotationSpinBox->setValue(static_cast<int>(sceneryObject->rotationDegree));
}

void SceneryObjectTreeProperties::updateScaleX(double x)
{
	sceneryObject->scale = QSizeF(x, sceneryObject->scale.height());
	// todo eventually emit signal to inform about change
}

void SceneryObjectTreeProperties::updateScaleY(double y)
{
	sceneryObject->scale = QSizeF(sceneryObject->scale.width(), y);
	// todo eventually emit signal to inform about change
}

void SceneryObjectTreeProperties::updateAlphaMultiplier(double multiplier)
{
	sceneryObject->alphaMultiplier = multiplier;
	// todo eventually emit signal to inform about change
}

void SceneryObjectTreeProperties::updateRotation(double rotation)
{
	sceneryObject->rotationDegree = rotation;
	// todo eventually emit signal to inform about change
}
