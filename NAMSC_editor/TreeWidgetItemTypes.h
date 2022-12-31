#pragma once
#include <QTreeWidgetItem>

enum class TreeWidgetItemTypes
{
	ImageObject = QTreeWidgetItem::ItemType::UserType, // Create separate class for images
	SoundObject // Create separate class for sound
};
