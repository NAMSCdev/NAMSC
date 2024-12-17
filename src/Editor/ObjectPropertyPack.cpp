#include "ObjectPropertyPack.h"

ObjectPropertyPack::ObjectPropertyPack(ObjectTreeWidgetItem* item)
{
	currentlySelectedObject = item->sceneryObject;
	layout = new QVBoxLayout(this);
	initProperties();
}

ObjectPropertyPack::ObjectPropertyPack(SceneryObject* item)
{
	currentlySelectedObject = item;
	layout = new QVBoxLayout(this);
	initProperties();
}

ObjectPropertyPack::~ObjectPropertyPack()
{
	delete sceneryObjectTreeProperties;
	delete layout;
}

void ObjectPropertyPack::initProperties()
{
	sceneryObjectTreeProperties = new SceneryObjectTreeProperties(currentlySelectedObject, layout->parentWidget());

	//layout->setSizeConstraint(QLayout::SetDefaultConstraint);
	layout->addWidget(sceneryObjectTreeProperties);
}
