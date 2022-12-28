#pragma once
#include "BasicNodeProperties.h"
#include "CollapseButton.h"

class NodeGraphPropertiesManager
{
public:
	NodeGraphPropertiesManager(QLayout* layout, QGraphicsScene* scene);
	~NodeGraphPropertiesManager();


private:
	// Not owning pointers
	QLayout* layout;
	QGraphicsScene* scene;

	// Owning pointer
	BasicNodeProperties* basicNodeProperties;

	void initProperties();
};

