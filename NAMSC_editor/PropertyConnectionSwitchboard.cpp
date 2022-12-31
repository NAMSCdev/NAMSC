#include "PropertyConnectionSwitchboard.h"

PropertyConnectionSwitchboard::PropertyConnectionSwitchboard()
{}

PropertyConnectionSwitchboard::~PropertyConnectionSwitchboard()
{}

void PropertyConnectionSwitchboard::nodeSelectionChanged(GraphNode* node)
{
	emit nodeSelectionChangedSignal(node);
}
