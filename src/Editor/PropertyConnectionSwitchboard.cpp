#include "PropertyConnectionSwitchboard.h"

#include "pvnLib/Novel/Data/Novel.h"

PropertyConnectionSwitchboard::PropertyConnectionSwitchboard()
{}

PropertyConnectionSwitchboard::~PropertyConnectionSwitchboard()
{}

void PropertyConnectionSwitchboard::nodeSelectionChanged(GraphNode* node)
{
	emit nodeSelectionChangedSignal(node);
}

void PropertyConnectionSwitchboard::objectSelectionChanged(QString sceneryObjectName)
{
	emit sceneryObjectSelectionChangedSignal(Novel::getInstance().getDefaultSceneryObject(sceneryObjectName));
}

void PropertyConnectionSwitchboard::characterSelectionChanged(QString characterName)
{
	emit characterSelectionChangedSignal(Novel::getInstance().getDefaultCharacter(characterName));
}
