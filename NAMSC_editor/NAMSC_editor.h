#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "GraphNode.h"
#include "ui_NAMSC_editor.h"
#include "GraphView.h"

class NAMSC_editor : public QMainWindow
{
    Q_OBJECT

public:
    NAMSC_editor(QWidget *parent = nullptr);
    ~NAMSC_editor();

private:
    Ui::NAMSC_editorClass ui;

    QGraphicsScene* scene;
    GraphNode* node;
    GraphNode* node2;
};
