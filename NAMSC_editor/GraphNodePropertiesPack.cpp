#include "GraphNodePropertiesPack.h"

GraphNodePropertiesPack::GraphNodePropertiesPack(GraphNode* node) : currentlySelectedNode(node)
{
	layout = new QVBoxLayout(this);
	initProperties();
}

GraphNodePropertiesPack::~GraphNodePropertiesPack()
{
	delete basicNodeProperties;
	delete layout;
}

void GraphNodePropertiesPack::initProperties()
{
	basicNodeProperties = new BasicNodeProperties(currentlySelectedNode, layout->parentWidget());

	layout->addWidget(basicNodeProperties);
}
