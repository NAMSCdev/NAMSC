#pragma once

#include <QGraphicsScene>

#include "QVNMenuButton.h"

class MainMenu final : public QGraphicsScene
{
	Q_OBJECT

public:
	MainMenu(QObject *parent = nullptr);
	MainMenu(const QRectF& sceneRect, QObject* parent = nullptr);
	~MainMenu();

	void loadMainMenuConfig();
	// TODO setOnClickedListener add one for each button
	void setOnClickedListener(QObject* receiver, std::function<void()> onClicked);

private:
	QImage background;
	QImage logo; // TODO? change to list of graphics/images?
	QGraphicsProxyWidget* newGameButton;
	QGraphicsProxyWidget* loadGameSaveButton;
	QGraphicsProxyWidget* settingsButton;
	QGraphicsProxyWidget* exitButton;
	
	void initButtons();

private slots:
	void updateButtons(const QRectF& rect);
};
