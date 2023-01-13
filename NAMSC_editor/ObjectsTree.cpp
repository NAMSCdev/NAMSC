#include "ObjectsTree.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>

#include "ObjectTreeWidgetItem.h"
#include "ProjectConfiguration.h"
#include "Novel/Data/Novel.h"

ObjectsTree::ObjectsTree(QWidget* parent) : QTreeWidget(parent)
{
	createContextMenu();
}

void ObjectsTree::addAssetToObjects(QString path, QString name, TreeWidgetItemTypes type)
{
	ObjectTreeWidgetItem* tempTreeItem;
	

	if (type == TreeWidgetItemTypes::ImageObject) {
		SceneryObject tempSceneryObject;
		tempSceneryObject.name = name;
		tempSceneryObject.setAssetImage(path);
		Novel::getInstance().setDefaultSceneryObject(name, tempSceneryObject); // todo check if setting scenery objects like that is ok

		tempTreeItem = new ObjectTreeWidgetItem(this, static_cast<int>(type));
		tempTreeItem->sceneryObject = Novel::getInstance().getDefaultSceneryObject(name);
		tempTreeItem->setIcon(0, QIcon(":/NAMSC_editor/imageIcon"));
	}
	else if (type == TreeWidgetItemTypes::SoundObject)
	{
		// todo
	}

	tempTreeItem->relativeAssetPath = ProjectConfiguration::getInstance()->getProjectPath().relativeFilePath(path);

	
	tempTreeItem->setText(0, name);

	addTopLevelItem(tempTreeItem);
}

void ObjectsTree::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	//emit selectedObjectChanged(static_cast<ObjectTreeWidgetItem>(selectedItems().first()).sceneryObject); // todo check if correct
	emit selectedObjectChanged(selectedItems().first()->text(0));
	QTreeWidget::selectionChanged(selected, deselected);
}

void ObjectsTree::contextMenuEvent(QContextMenuEvent* context_menu_event)
{
	if (!selectedItems().isEmpty()) {
		contextMenuInvokePosition = context_menu_event->globalPos();

		QMenu menu(this);
		menu.addAction(addObjectToSceneAction);
		menu.exec(context_menu_event->globalPos());
	}
	//QTreeWidget::contextMenuEvent(context_menu_event);
}

void ObjectsTree::mousePressEvent(QMouseEvent* event)
{
	// clearSelection(); todo deselection in preview
	QTreeWidget::mousePressEvent(event);
}

void ObjectsTree::createContextMenu()
{
	addObjectToSceneAction = new QAction(tr("Add object to scene"), this);
	addObjectToSceneAction->setStatusTip(tr("Object will be added to the currently edited scene"));
	
	connect(addObjectToSceneAction, &QAction::triggered, this, [&]
		{
			emit addObjectToScene(dynamic_cast<ObjectTreeWidgetItem*>(this->currentItem()));
		});
}
