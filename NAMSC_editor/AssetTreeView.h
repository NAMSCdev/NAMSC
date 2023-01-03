#pragma once
#include <QFileSystemModel>
#include <QMimeDatabase>
#include <qtreeview.h>

#include "CustomSortFilterProxyModel.h"

class AssetTreeView :
    public QTreeView
{
    Q_OBJECT

public:
    AssetTreeView(QWidget* parent);
    ~AssetTreeView();
    void setSupportedAudioFormats(QList<QMimeType> supportedAudioFormats);
    void setSupportedImageFormats(QList<QMimeType> supportedImageFormats);
private:
    QMimeDatabase db;
    QList<QMimeType> supportedImageFormats;
    QList<QMimeType> supportedAudioFormats;
    QFileSystemModel* fileModel;
    CustomSortFilterProxyModel* proxyFileFilter;
};

