#pragma once

#include <QTreeWidgetItem>
#include <QUrl>

#include "Novel/Data/Visual/Scenery/SceneryObject.h"

class ImageObjectTreeWidgetItem : public QObject, public QTreeWidgetItem
{
	Q_OBJECT

public:
	ImageObjectTreeWidgetItem();
	ImageObjectTreeWidgetItem(QTreeWidgetItem *parent);
	ImageObjectTreeWidgetItem(QTreeWidget *parent);
	//~ImageObjectTreeWidgetItem();

	SceneryObject* sceneryObject;
	QString relativeAssetPath; // relative path
};
