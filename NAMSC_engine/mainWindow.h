#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"

#include "Novel/Data/Novel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::mainWindow ui;
    Novel novel;
};
