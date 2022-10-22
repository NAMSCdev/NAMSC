#pragma once
#include "Global.h"

#include "Novel/Action/Action.h"
#include "Novel/Data/Visual/Scenery/SceneryObject.h"

/// Action that affects a SceneryObject
class ActionSceneryObject : public Action
{
public:
	ActionSceneryObject() noexcept = default;
	ActionSceneryObject(QString&& sceneryObjectName);
	ActionSceneryObject(const ActionSceneryObject& obj) noexcept { *this = obj; }
	ActionSceneryObject& operator=(const ActionSceneryObject& obj) noexcept;

protected:
	/// Name of the SceneryObject, so it can be loaded (if needed)
	QString		   sceneryObjectName;
	/// SceneryObject that will be affected by the ActionSceneryObject
	SceneryObject* sceneryObject;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const override;
};




inline ActionSceneryObject& ActionSceneryObject::operator=(const ActionSceneryObject& obj)
{
	if (this == &obj) return *this;

	Action::operator=(obj);
	sceneryObjectName = obj.sceneryObjectName;
	sceneryObject     = obj.sceneryObject;

	return *this;
}