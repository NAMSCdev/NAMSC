#include "Novel/Action/Visual/ActionSceneryObject.h"

#include "Novel/Data/Scene.h"

ActionSceneryObject::~ActionSceneryObject() = default;

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionSceneryObject& first, ActionSceneryObject& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<Action&>(first), static_cast<Action&>(second));
	swap(first.sceneryObjectName_, second.sceneryObjectName_);
	swap(first.sceneryObject_,     second.sceneryObject_);
}

ActionSceneryObject::ActionSceneryObject(Event* const parentEvent, const QString& sceneryObjectName, SceneryObject* sceneryObject)
	: Action(parentEvent),
	sceneryObjectName_(sceneryObjectName), 
	sceneryObject_(sceneryObject)
{
}

//deleted
//bool ActionSceneryObject::operator==(const ActionSceneryObject& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return Action::operator==(obj)                      &&
//		   sceneryObjectName_ == obj.sceneryObjectName_;// &&
//	       //sceneryObject_     == obj.sceneryObject_;
//}

void ActionSceneryObject::serializableLoad(QDataStream& dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> sceneryObjectName_;
}

void ActionSceneryObject::serializableSave(QDataStream& dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << sceneryObjectName_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

QString ActionSceneryObject::getSceneryObjectName() const noexcept
{
	return sceneryObjectName_;
}

const SceneryObject* ActionSceneryObject::getSceneryObject() const noexcept 
{ 
	return sceneryObject_; 
}

SceneryObject* ActionSceneryObject::getSceneryObject() noexcept
{
	return sceneryObject_;
}

void ActionSceneryObject::setSceneryObject(const QString& sceneryObjectName, SceneryObject* sceneryObject) noexcept
{
	if (sceneryObject)
	{
		if (sceneryObject->name != sceneryObjectName)
		{
			qCritical() << NovelLib::ErrorType::SceneryObjectInvalid << "SceneryObject's name missmatch (sceneryObjectName=\"" + sceneryObjectName + "\", sceneryObject->name=\"" + sceneryObject->name + "\")";
			return;
		}
	}

	if (parentEvent->parentScene->scenery.getDisplayedSceneryObject(sceneryObjectName_) == nullptr)
	{
		qCritical() << NovelLib::ErrorType::SceneryObjectMissing << "Scenery Object \"" + sceneryObjectName + "\" does not exist";
		return;
	}

	sceneryObjectName_ = sceneryObjectName;
	errorCheck(true);
}