#include "ObjectsTree.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>

ObjectsTree::ObjectsTree(QWidget* parent) : QTreeWidget(parent)
{
	createContextMenu();
}

void ObjectsTree::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	//emit 

	QTreeWidget::selectionChanged(selected, deselected);
}

void ObjectsTree::contextMenuEvent(QContextMenuEvent* context_menu_event)
{
	contextMenuInvokePosition = context_menu_event->globalPos();

	QMenu menu(this);
	menu.addAction(addObjectToSceneAction);
	menu.exec(context_menu_event->globalPos());
	//QTreeWidget::contextMenuEvent(context_menu_event);
}

void ObjectsTree::createContextMenu()
{
	addObjectToSceneAction = new QAction(tr("Add object to scene"), this);
	addObjectToSceneAction->setStatusTip("Object will be added to the currently edited scene");

	connect(addObjectToSceneAction, &QAction::triggered, this, [&]
		{
			emit addObjectToScene(this->currentItem(), static_cast<TreeWidgetItemTypes>(this->currentItem()->type()));
		});
}
