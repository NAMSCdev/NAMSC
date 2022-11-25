#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "GraphNode.h"
#include "ui_NAMSC_editor.h"
#include "GraphView.h"
#include "CollapseButton.h"
#include <Novel/Data/Novel.h>
#include "NodeGraphPropertiesManager.h"

class NAMSC_editor : public QMainWindow
{
    Q_OBJECT

public:
    NAMSC_editor(QWidget *parent = nullptr);
    ~NAMSC_editor();
    void prepareAssetsTree();

private:
    Ui::NAMSC_editorClass ui;
    Novel novel;

    NodeGraphPropertiesManager* nodePropertiesManager;
    QGraphicsScene* scene;
    GraphNode* node;
    GraphNode* node2;
};
