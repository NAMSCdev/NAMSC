#pragma once

#include <QtWidgets/QMainWindow>
#include <QOpenGLWidget>
#include "ui_mainWindow.h"
#include "TextBox.h"

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

private:
    TextBox* textbox2;
    QGraphicsScene* scene;
    Ui::mainWindowClass ui;
};
