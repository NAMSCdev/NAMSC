#include "NodeGraphPropertiesManager.h"

NodeGraphPropertiesManager::NodeGraphPropertiesManager(QLayout* layout, QGraphicsScene* scene) : layout(layout), scene(scene)
{
	initProperties();
}

NodeGraphPropertiesManager::~NodeGraphPropertiesManager()
{
	delete basicNodeProperties;
}

void NodeGraphPropertiesManager::initProperties()
{
	basicNodeProperties = new BasicNodeProperties(scene, layout->parentWidget());
	layout->addWidget(basicNodeProperties);

}
