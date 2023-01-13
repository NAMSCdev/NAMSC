#pragma once

#include <QTreeWidgetItem>

#include "Novel/Data/Visual/Scenery/Character.h"

class CharacterTreeWidgetItem : public QObject, public QTreeWidgetItem
{
	Q_OBJECT

public:
	using QTreeWidgetItem::QTreeWidgetItem;

	Character* character;
	QString relativeAssetPath; // relative path
};
