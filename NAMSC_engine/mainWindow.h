#pragma once

#include <QtWidgets/QMainWindow>

#include "MainMenu.h"
#include "MainSettingsMenu.h"
#include "ui_mainWindow.h"

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

protected:
    void showEvent(QShowEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::mainWindowClass ui;

    MainMenu* mainMenu;
    MainSettingsMenu* mainSettingsMenu;

private slots:
    void changeSceneToSettings();
};
