#pragma once
#include <QTreeWidgetItem>

enum class TreeWidgetItemTypes
{
	ImageObject = QTreeWidgetItem::ItemType::UserType, // Create separate class for images
	SoundObject // Create separate class for sound
};

inline bool operator==(const TreeWidgetItemTypes& type, const int& i)
{
	return static_cast<int>(type) == i;
}

//inline bool operator==(const int& i, const TreeWidgetItemTypes& type);
