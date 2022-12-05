#include "MainMenu.h"
#include "MainMenu.h"

#include <QApplication>
#include <QDebug>
#include <QString>
#include <QGraphicsProxyWidget>

#include "VNButton.h"

MainMenu::MainMenu(QObject *parent)
	: QGraphicsScene(parent)
{
	initButtons();
}

MainMenu::MainMenu(const QRectF& sceneRect, QObject* parent) : QGraphicsScene(sceneRect, parent)
{
	initButtons();
}

MainMenu::~MainMenu()
{}

void MainMenu::setOnClickedListener(QObject* receiver, std::function<void()> onClicked)
{
	connect(dynamic_cast<VNButton*>(settingsButton->widget()), &VNButton::clicked, receiver, onClicked);
}

void MainMenu::initButtons()
{
	// Create buttons
	newGameButton = this->addWidget(new VNButton(nullptr));
	loadGameSaveButton = this->addWidget(new VNButton(nullptr));
	settingsButton = this->addWidget(new VNButton(nullptr));
	exitButton = this->addWidget(new VNButton(nullptr));

	// Set button text
	dynamic_cast<VNButton*>(newGameButton->widget())->setText("New game");
	dynamic_cast<VNButton*>(loadGameSaveButton->widget())->setText("Load saved game");
	dynamic_cast<VNButton*>(settingsButton->widget())->setText("Settings");
	dynamic_cast<VNButton*>(exitButton->widget())->setText("Exit");

	// Set hover
	dynamic_cast<VNButton*>(newGameButton->widget())->setHover(true);
	dynamic_cast<VNButton*>(loadGameSaveButton->widget())->setHover(true);
	dynamic_cast<VNButton*>(settingsButton->widget())->setHover(true);
	dynamic_cast<VNButton*>(exitButton->widget())->setHover(true);

	connect(this, &MainMenu::sceneRectChanged, this, &MainMenu::updateButtons);

	connect(exitButton->widget(), SIGNAL(clicked()), QCoreApplication::instance(), SLOT(quit()));
}

void MainMenu::updateButtons(const QRectF& rect)
{
	// Update positions
	newGameButton->setPos((rect.width() - newGameButton->widget()->width()) / 2, rect.height() * 0.55);
	loadGameSaveButton->setPos((rect.width() - loadGameSaveButton->widget()->width()) / 2, rect.height() * 0.65);
	settingsButton->setPos((rect.width() - settingsButton->widget()->width()) / 2, rect.height() * 0.75);
	exitButton->setPos((rect.width() - exitButton->widget()->width()) / 2, rect.height() * 0.85);

}
