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

void MainSettingsMenu::setScreenModeSettingsListener(QObject* receiver, std::function<void(int)> onClicked)
{
	screenModeSettingsWidget->setListener(receiver, onClicked);
}

void MainSettingsMenu::initializeSettingsBox()
{
	// Initialize
	settingsBox = this->addWidget(new QFrame(nullptr));
	settingsLayout = new QHBoxLayout(settingsBox->widget());
	leftColumnLayout = new QVBoxLayout(nullptr);
	rightColumnLayout = new QVBoxLayout(nullptr);
	volumeSettingsWidget = new VolumeSettingsWidget(settingsBox->widget());
	textSpeedSettingsWidget = new TextSpeedSettingsWidget(settingsBox->widget());
	screenModeSettingsWidget = new ScreenModeSettingsWidget(settingsBox->widget());
	languageSettingsWidget = new LanguageSettingsWidget(settingsBox->widget());

	// Setup layout
	dynamic_cast<QFrame*>(settingsBox->widget())->setLayout(settingsLayout);
	settingsLayout->addLayout(leftColumnLayout);
	settingsLayout->addLayout(rightColumnLayout);
	
	// Add widgets to layout
	leftColumnLayout->addWidget(textSpeedSettingsWidget);
	leftColumnLayout->addWidget(screenModeSettingsWidget);
	leftColumnLayout->addWidget(languageSettingsWidget);
	rightColumnLayout->addWidget(volumeSettingsWidget);

	
	//connect();
}

void MainSettingsMenu::sceneRectChangedUpdate()
{
	dynamic_cast<QFrame*>(settingsBox->widget())->setFixedSize(sceneRect().size().toSize() * 0.8);
	settingsBox->setPos(sceneRect().center() - settingsBox->rect().center());
	//settingsLayout->setSpacing(settingsBox->size().width() / 10);
	
}
