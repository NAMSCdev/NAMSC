#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_PVN_engine.h"

#include "pvnlib/Novel/Data/Novel.h"

class ExampleEngine : public QMainWindow
{
    Q_OBJECT

public:
    ExampleEngine(QWidget *parent = nullptr);
    ~ExampleEngine();

private:
    Ui::mainWindow ui;
};