#pragma once

#include <QTreeWidgetItem>
#include <QUrl>

#include "pvnlib/Novel/Data/Visual/Scenery/SceneryObject.h"

class ObjectTreeWidgetItem : public QObject, public QTreeWidgetItem
{
	Q_OBJECT

public:
	using QTreeWidgetItem::QTreeWidgetItem;
	//ObjectTreeWidgetItem();
	//ObjectTreeWidgetItem(QTreeWidgetItem *parent);
	//ObjectTreeWidgetItem(QTreeWidget *parent);
	//~ObjectTreeWidgetItem();

	SceneryObject* sceneryObject;
	QString relativeAssetPath; // relative path
};
