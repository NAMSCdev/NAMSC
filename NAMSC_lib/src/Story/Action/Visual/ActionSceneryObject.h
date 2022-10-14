#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

#include "Story/Data/Story.h"
#include "Story/Data/Visual/Scenery/SceneryObject.h"

///Action that affects a SceneryObject
class ActionSceneryObject : public Action
{
public:
	ActionSceneryObject() = default;
	ActionSceneryObject(Event *parent, unsigned actionID, QString &&label, QString &&sceneryObjectName) :
		Action(parent, actionID, move(label)), sceneryObjectName(move(sceneryObjectName))
	{ 
		sceneryObject = Story::getInstance().findSceneryObject(this->sceneryObjectName); 
	}
	ActionSceneryObject(const ActionSceneryObject& asset)				= default;
	ActionSceneryObject& operator=(const ActionSceneryObject& asset)	= default;

	///Ensures Assets are loaded and if not - loads it
	virtual void ensureAssetsAreLoaded() override			{ sceneryObject->ensureAssetsAreLoaded(); }

protected:
	///Name to the Scenery Object, so it can be loaded (if needed)
	QString		  sceneryObjectName;
	///Scenery Object that will be affected by the Action
	SceneryObject *sceneryObject;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const override;
};