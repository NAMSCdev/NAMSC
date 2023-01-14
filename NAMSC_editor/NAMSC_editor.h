#pragma once

#include <QFileSystemModel>
#include <QtWidgets/QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMimeDatabase>

#include "GraphNode.h"
#include "ui_NAMSC_editor.h"
#include <Novel/Data/Novel.h>

#include "CustomSortFilterProxyModel.h"
#include "GraphNodePropertiesPack.h"
#include "PropertyConnectionSwitchboard.h"
#include "PropertyTypes.h"

class NAMSC_editor : public QMainWindow
{
    Q_OBJECT

public:
    NAMSC_editor(QWidget *parent = nullptr);
    ~NAMSC_editor();

    void prepareSwitchboard();

public slots:
    void propertyTabChangeRequested(void* object, PropertyTypes dataType);

private:
    Ui::NAMSC_editorClass ui;

    PropertyConnectionSwitchboard switchboard;
    QGraphicsScene* scene; // todo remove?
    GraphNode* node;
    GraphNode* node2;
    QMimeDatabase db;
    QList<QMimeType> supportedImageFormats;
    QList<QMimeType> supportedAudioFormats;
    void prepareAssetsTree();
    void supportedFormats();
    QFileSystemModel* model;
    CustomSortFilterProxyModel* proxyFileFilter;

    void debugConstructorActions();
};
