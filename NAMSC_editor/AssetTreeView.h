#pragma once
#include <QFileSystemModel>
#include <QMimeDatabase>
#include <qtreeview.h>
#include <QUrl>

#include "CustomSortFilterProxyModel.h"
#include "TreeWidgetItemTypes.h"
#include "ProjectConfiguration.h"

class AssetTreeView :
    public QTreeView
{
    Q_OBJECT

public:
    AssetTreeView(QWidget* parent, QUrl projectPath = QUrl::fromLocalFile(ProjectConfiguration::getInstance()->getProjectPath().path()));
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

    QUrl projectPath;

    QAction* addAssetToObjectsAction;
    QAction* addAssetToCharactersAction;

    void invokeContextMenu(const QPoint& pos);
    void createContextMenu();

protected:
    void mousePressEvent(QMouseEvent* event) override;
};

