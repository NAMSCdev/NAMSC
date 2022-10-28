#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainEditorWindow.h"
#include "GraphView.h"
#include <nodes/DataModelRegistry>

class MainEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainEditorWindow(QWidget *parent = nullptr);
    ~MainEditorWindow();

    void runGraphView();

private:
    Ui::MainEditorWindowClass ui;
    QLayout* layout;
    GraphView* graphView;
    FlowScene* scene;
    std::shared_ptr<DataModelRegistry> dataModelRegistry;
};
