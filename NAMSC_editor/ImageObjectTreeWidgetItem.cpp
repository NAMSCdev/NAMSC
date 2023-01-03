#include "ImageObjectTreeWidgetItem.h"

#include "TreeWidgetItemTypes.h"

ImageObjectTreeWidgetItem::ImageObjectTreeWidgetItem()
	: QTreeWidgetItem(static_cast<int>(TreeWidgetItemTypes::ImageObject))
{
}

ImageObjectTreeWidgetItem::ImageObjectTreeWidgetItem(QTreeWidgetItem *parent)
	: QTreeWidgetItem(parent, static_cast<int>(TreeWidgetItemTypes::ImageObject))
{
}

ImageObjectTreeWidgetItem::ImageObjectTreeWidgetItem(QTreeWidget* parent)
	: QTreeWidgetItem(parent, static_cast<int>(TreeWidgetItemTypes::ImageObject))
{
}

