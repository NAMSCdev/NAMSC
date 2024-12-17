#pragma once

#include <QFrame>

#include "ObjectTreeWidgetItem.h"
#include "SceneryObjectTreeProperties.h"

class ObjectPropertyPack : public QFrame
{
public:
	ObjectPropertyPack(ObjectTreeWidgetItem *item);
	ObjectPropertyPack(SceneryObject* item);
	~ObjectPropertyPack();

private:
	SceneryObject* currentlySelectedObject;

	QLayout* layout;

	SceneryObjectTreeProperties* sceneryObjectTreeProperties;

	void initProperties();
};
