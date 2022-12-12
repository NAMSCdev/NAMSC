#include "mainWindow.h"

#include <QGraphicsProxyWidget>

#include "VNButton.h"

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //qDebug() << QRectF(0, 0, ui.graphicsView->size().width(), ui.graphicsView->size().height());
    mainMenu = new MainMenu(ui.graphicsView);

    mainSettingsMenu = new MainSettingsMenu(ui.graphicsView);

    //connect(mainMenu->settingsButton->widget(), SIGNAL(clicked()), this, SLOT(changeSceneToSettings()));
    mainMenu->setOnClickedListener(this, std::bind(&mainWindow::changeSceneToSettings, this));
    mainSettingsMenu->setScreenModeSettingsListener(this, [&](int isFullscreen) { setWindowState(windowState() ^ Qt::WindowFullScreen); });

	ui.graphicsView->setScene(mainMenu);
    ui.graphicsView->setFrameStyle(0);

}

mainWindow::~mainWindow()
{}

void mainWindow::showEvent(QShowEvent* event)
{
    mainMenu->setSceneRect(ui.graphicsView->rect());
    mainSettingsMenu->setSceneRect(ui.graphicsView->rect());

	QMainWindow::showEvent(event);
}

void mainWindow::resizeEvent(QResizeEvent* event)
{
    mainMenu->setSceneRect(ui.graphicsView->rect());
    mainSettingsMenu->setSceneRect(ui.graphicsView->rect());

	QMainWindow::resizeEvent(event);
}

void mainWindow::changeSceneToSettings()
{
    ui.graphicsView->setScene(mainSettingsMenu);
}
