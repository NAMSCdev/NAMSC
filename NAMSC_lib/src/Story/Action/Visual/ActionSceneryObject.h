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
	ActionSceneryObject(unsigned actionID, QString &&label, QString &&sceneryObjectName) :
		Action(actionID, move(label)), sceneryObjectName(move(sceneryObjectName))
	{ 
		sceneryObject = Story::getInstance().findSceneryObject(this->sceneryObjectName); 
	}
	ActionSceneryObject(const ActionSceneryObject& obj) { *this = obj; }
	ActionSceneryObject& operator=(const ActionSceneryObject& obj)
	{
		if (this == &obj) return *this;

		Action::operator=(obj);
		sceneryObjectName = obj.sceneryObjectName;
		sceneryObject     = obj.sceneryObject;

		return *this;
	}

	///Ensures Assets are loaded and if not - loads it
	virtual void ensureAssetsAreLoaded() override { sceneryObject->ensureAssetsAreLoaded(); }

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