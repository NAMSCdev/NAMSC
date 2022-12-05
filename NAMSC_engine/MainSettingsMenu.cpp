#include "MainSettingsMenu.h"

#include <QGraphicsProxyWidget>

MainSettingsMenu::MainSettingsMenu(QObject *parent)
	: QGraphicsScene(parent)
{
	initializeSettingsBox();

	connect(this, &MainSettingsMenu::sceneRectChanged, this, &MainSettingsMenu::sceneRectChangedUpdate);
}

MainSettingsMenu::~MainSettingsMenu()
{}

void MainSettingsMenu::initializeSettingsBox()
{
	settingsBox = this->addWidget(new QFrame(nullptr));

	settingsLayout = new QHBoxLayout(settingsBox->widget());

	//volumeSettingsWidget = new QGraphicsProxyWidget();
	//volumeSettingsWidget->setWidget(new VolumeSettingsWidget(settingsBox->widget()));
	volumeSettingsWidget = new VolumeSettingsWidget(settingsBox->widget());

	dynamic_cast<QFrame*>(settingsBox->widget())->setLayout(settingsLayout);
	settingsLayout->addWidget(volumeSettingsWidget);
}

void MainSettingsMenu::sceneRectChangedUpdate()
{
	dynamic_cast<QFrame*>(settingsBox->widget())->setFixedSize(sceneRect().size().toSize() * 0.8);
	settingsBox->setPos(sceneRect().center() - settingsBox->rect().center());
}
