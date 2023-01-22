#include "AssetTreeView.h"

#include <QAction>
#include <QFileSystemModel>
#include <QMenu>
#include <QMimeData>
#include <QMimeType>
#include <QUrl>
#include <QContextMenuEvent>
#include <qinputdialog.h>
#include <qmessagebox.h>

#include "CustomSortFilterProxyModel.h"
#include "Novel/Data/Novel.h"


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

    setContextMenuPolicy(Qt::CustomContextMenu);
    createContextMenu();
    connect(this, &AssetTreeView::customContextMenuRequested, this, &AssetTreeView::invokeContextMenu);
}

AssetTreeView::~AssetTreeView()
{ }

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

void AssetTreeView::invokeContextMenu(const QPoint& pos)
{
    if (!selectedIndexes().isEmpty())
    {
        QMenu menu(this);
        menu.addAction(addAssetToObjectsAction);
        menu.addAction(addAssetToCharactersAction);
        menu.exec(mapToGlobal(pos));
    }
}

void AssetTreeView::createContextMenu()
{
    addAssetToObjectsAction = new QAction(tr("Add to objects"), this);
    addAssetToObjectsAction->setStatusTip("Adds selected asset to objects");

    addAssetToCharactersAction = new QAction(tr("Add to characters"), this);
    addAssetToCharactersAction->setStatusTip("Adds selected asset to characters");

    connect(addAssetToObjectsAction, &QAction::triggered, this, [&]
        {
            TreeWidgetItemTypes type;
			QString objectName;
            bool isNameOk = false;
            bool pressedOk = false;
			QUrl selectedItem = selectionModel()->model()->mimeData({ currentIndex().siblingAtColumn(0) })->urls().at(0);
            QMimeType selectedItemMimeType = db.mimeTypeForUrl(selectedItem);

    		if (supportedImageFormats.contains(selectedItemMimeType))
			{
                type = TreeWidgetItemTypes::ImageObject;
			}
            else if (supportedAudioFormats.contains(selectedItemMimeType))
            {
                type = TreeWidgetItemTypes::SoundObject;
            }
            else
            {
	            // todo error
            }

			do
			{
                objectName = QInputDialog::getText(this, tr("Create object"),
                    tr("Enter name for created object:"), QLineEdit::Normal,
                    selectedItem.fileName(), &pressedOk);

                // Name input checks
                if (!pressedOk)
                {
                    break;
                }
				else if (objectName.isNull() || objectName.isEmpty())
                {
                    continue;
                }
				else if (Novel::getInstance().getDefaultSceneryObject(objectName) != nullptr)
                {
                    QMessageBox(QMessageBox::Critical, tr("Object name incorrect"),tr("Provided object name already exists.\nPlease provide other name."), QMessageBox::Ok).exec();
                    continue;
                }
                else {
                    isNameOk = true; // todo remove in the future
                }
            } while (!isNameOk);

            if (!pressedOk) return;
			
			emit addAssetToObjects(QDir(QDir::currentPath()).relativeFilePath(selectedItem.toLocalFile()), objectName, type);
        });

        connect(addAssetToCharactersAction, &QAction::triggered, this, [&]
            {
                TreeWidgetItemTypes type;
        QString objectName;
        bool isNameOk = false;
        bool pressedOk = false;
        QUrl selectedItem = selectionModel()->model()->mimeData({ currentIndex().siblingAtColumn(0) })->urls().at(0);
        QMimeType selectedItemMimeType = db.mimeTypeForUrl(selectedItem);

        if (supportedImageFormats.contains(selectedItemMimeType))
        {
            type = TreeWidgetItemTypes::ImageObject;
        }
        else if (supportedAudioFormats.contains(selectedItemMimeType))
        {
            type = TreeWidgetItemTypes::SoundObject;
        }
        else
        {
            // todo error
        }

        do
        {
            objectName = QInputDialog::getText(this, tr("Create character"),
                tr("Enter name for created character:"), QLineEdit::Normal,
                selectedItem.fileName(), &pressedOk);

            // Name input checks
            if (!pressedOk)
            {
                break;
            }
            else if (objectName.isNull() || objectName.isEmpty())
            {
                continue;
            }
            else if (Novel::getInstance().getDefaultCharacter(objectName) != nullptr)
            {
                QMessageBox(QMessageBox::Critical, tr("Character name incorrect"), tr("Provided character name already exists.\nPlease provide other name."), QMessageBox::Ok).exec();
                continue;
            }
            else {
                isNameOk = true; // todo remove in the future
            }
        } while (!isNameOk);

        if (!pressedOk) return;

        emit addAssetToCharacters(QDir(QDir::currentPath()).relativeFilePath(selectedItem.toLocalFile()), objectName, type);
            });
}

void AssetTreeView::mousePressEvent(QMouseEvent* event)
{
    clearSelection(); //todo implement deselection for preview
	QTreeView::mousePressEvent(event);
}
