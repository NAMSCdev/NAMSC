#pragma once
#include "Global.h"

#include "Novel/Action/Action.h"

#include "Novel/Data/Visual/Scenery/SceneryObject.h"

///Action that affects a SceneryObject
class ActionSceneryObject : public Action
{
public:
	ActionSceneryObject() = default;
	ActionSceneryObject(QString&& sceneryObjectName);
	ActionSceneryObject(const ActionSceneryObject& obj) { *this = obj; }
	ActionSceneryObject& operator=(const ActionSceneryObject& obj);
	///Ensures Assets are loaded and if not - loads it
	//virtual void ensureResourcesAreLoaded() override { sceneryObject->ensureResourcesAreLoaded(); }

protected:
	///Name to the Scenery Object, so it can be loaded (if needed)
	QString		  sceneryObjectName;
	///Scenery Object that will be affected by the Action
	SceneryObject* sceneryObject;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream& dataStream) const override;
};

inline ActionSceneryObject::ActionSceneryObject(QString&& sceneryObjectName) :
	Action(), sceneryObjectName(move(sceneryObjectName))
{
	sceneryObject = Novel::getInstance().findSceneryObject(this->sceneryObjectName);
}

inline ActionSceneryObject& ActionSceneryObject::operator=(const ActionSceneryObject& obj)
{
	if (this == &obj) return *this;

	Action::operator=(obj);
	sceneryObjectName = obj.sceneryObjectName;
	sceneryObject = obj.sceneryObject;

	return *this;
}