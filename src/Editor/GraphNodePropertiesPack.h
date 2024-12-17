#pragma once
#include "BasicNodeProperties.h"
#include "CollapseButton.h"

class GraphNodePropertiesPack : public QFrame
{
public:
	GraphNodePropertiesPack(GraphNode* node);
	~GraphNodePropertiesPack();
    BasicNodeProperties* basicNodeProperties;


private:
	// Not owning pointers
	GraphNode* currentlySelectedNode;

	// Owning pointers
	QLayout* layout;

	void initProperties();
};

