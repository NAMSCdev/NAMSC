#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_NAMSC_engine.h"

#include "pvnlib/Novel/Data/Novel.h"

class NAMSC_engine : public QMainWindow
{
    Q_OBJECT

public:
    NAMSC_engine(QWidget *parent = nullptr);
    ~NAMSC_engine();

private:
    Ui::mainWindow ui;
};