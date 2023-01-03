#include "AssetTreeView.h"

#include <QFileSystemModel>
#include <QMimeData>
#include <QMimeType>
#include <QUrl>

#include "CustomSortFilterProxyModel.h"


AssetTreeView::AssetTreeView(QWidget* parent) : QTreeView(parent)
{
    QUrl projectPath = QUrl::fromLocalFile("F:/inzynierka/NAMSC/NAMSC_editor/");
    fileModel = new QFileSystemModel;
    QModelIndex rootPath = fileModel->setRootPath(projectPath.toLocalFile());
    proxyFileFilter = new CustomSortFilterProxyModel(this);
    
    proxyFileFilter->setSourceModel(fileModel);
    this->setModel(proxyFileFilter);
    this->setRootIndex(proxyFileFilter->mapFromSource(rootPath));
    proxyFileFilter->setRecursiveFilteringEnabled(true);
    proxyFileFilter->setFilter(
        [&](int sourceRow, const QModelIndex& sourceParent)
        {
            QModelIndex index = fileModel->index(sourceRow, 0, sourceParent);
    QMimeData* mime = fileModel->mimeData({ index });
    if (mime->hasUrls())
    {
        QUrl fileUrl = mime->urls().at(0);
        QMimeType fileMime = db.mimeTypeForUrl(fileUrl);
        if (supportedAudioFormats.contains(fileMime) || supportedImageFormats.contains(fileMime) || fileMime.name() == "inode/directory")
        {
            return true;
        }
    }
    return false;
        }
    );
    this->hideColumn(1);
    this->hideColumn(3);
    connect(this, &QTreeView::expanded, this, [&]() {this->resizeColumnToContents(0); });
}

AssetTreeView::~AssetTreeView()
{}

void AssetTreeView::setSupportedAudioFormats(QList<QMimeType> audioFormats)
{
    supportedAudioFormats.clear();
    supportedAudioFormats.append(audioFormats);
}

void AssetTreeView::setSupportedImageFormats(QList<QMimeType> imageFormats)
{
    supportedImageFormats.clear();
    supportedImageFormats.append(imageFormats);
}