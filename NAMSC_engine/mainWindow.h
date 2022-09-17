#pragma once

#include <QtWidgets/QMainWindow>
#include <QOpenGLWidget>
#include "ui_mainWindow.h"
#include "MainTextBox.h"

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

private:
    MainTextBox* textbox;
    QGraphicsScene* scene;
    Ui::mainWindowClass ui;
};
