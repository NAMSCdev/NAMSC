#pragma once

#include <QFileSystemModel>

#include "GraphNode.h"
#include "ui_NAMSC_editor.h"
#include <pvnlib/Novel/Data/Novel.h>

#include "CustomSortFilterProxyModel.h"
#include "PropertyConnectionSwitchboard.h"
#include "PropertyTypes.h"

/// Main window of the Editor
class NAMSC_editor : public QMainWindow
{
    Q_OBJECT

public:
    NAMSC_editor(QWidget *parent = nullptr);
    ~NAMSC_editor();

    void prepareSwitchboard();

    void loadEditor();
    void saveEditor();

public slots:
    void propertyTabChangeRequested(void* object, PropertyTypes dataType);

private:
    void setupSupportedFormats();

    void setupAssetTree();
    void setupEventTree();

    void createDanglingContextMenuActions();
    void invokeEventsContextMenu(const QPoint& pos);

    void loadGraph(GraphView* graph);
    void saveGraph(GraphView* graph);

    void debugConstructorActions();

    PropertyConnectionSwitchboard switchboard;
    QGraphicsScene* scene; // todo remove?
    GraphNode* node;
    GraphNode* node2;
    QMimeDatabase db;
    QList<QMimeType> supportedImageFormats;
    QList<QMimeType> supportedAudioFormats;

    QFileSystemModel* model;
    CustomSortFilterProxyModel* proxyFileFilter;
    SceneWidget* sceneWidget;


    QAction* addDialogueEventAction;
    QAction* addChoiceEventAction;
    QAction* addJumpEventAction;


    Ui::NAMSC_editorClass ui;

};
