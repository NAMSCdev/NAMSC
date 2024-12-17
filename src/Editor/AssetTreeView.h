#pragma once
#include <QTreeView>

#include <QFileSystemModel>
#include <QMimeDatabase>

#include "CustomSortFilterProxyModel.h"
#include "TreeWidgetItemTypes.h"

class AssetTreeView : public QTreeView
{
    Q_OBJECT

public:
    AssetTreeView(QWidget* parent);
    ~AssetTreeView();
    void setSupportedAudioFormats(QList<QMimeType> supportedAudioFormats);
    void setSupportedImageFormats(QList<QMimeType> supportedImageFormats);

signals:
    void addAssetToObjects(QString path, QString name, TreeWidgetItemTypes type);
    void addAssetToCharacters(QString path, QString name, TreeWidgetItemTypes type);

private:
    QMimeDatabase db;
    QList<QMimeType> supportedImageFormats;
    QList<QMimeType> supportedAudioFormats;
    QFileSystemModel* fileModel;
    CustomSortFilterProxyModel* proxyFileFilter;

    QAction* addAssetToObjectsAction;
    QAction* addAssetToCharactersAction;

    void invokeContextMenu(const QPoint& pos);
    void createContextMenu();

protected:
    void mousePressEvent(QMouseEvent* event) override;
};

