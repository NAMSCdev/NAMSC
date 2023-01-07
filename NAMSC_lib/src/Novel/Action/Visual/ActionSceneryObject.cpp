#include "Novel/Action/Visual/ActionSceneryObject.h"

#include "Novel/Data/Scene.h"

ActionSceneryObject::ActionSceneryObject(Event* const parentEvent) noexcept
	: Action(parentEvent)
{
}

ActionSceneryObject::ActionSceneryObject(Event* const parentEvent, const QString& sceneryObjectName)
	: Action(parentEvent), sceneryObjectName_(sceneryObjectName)
{
	///checkForErrors(true);
}

ActionSceneryObject& ActionSceneryObject::operator=(const ActionSceneryObject& obj) noexcept
{
	if (this == &obj) return *this;

	Action::operator=(obj);
	sceneryObjectName_ = obj.sceneryObjectName_;
	sceneryObject_     = obj.sceneryObject_;

	return *this;
}

bool ActionSceneryObject::operator==(const ActionSceneryObject& obj) const noexcept
{
	if (this == &obj) return true;

	return	Action::operator==(obj)                      &&
			sceneryObjectName_ == obj.sceneryObjectName_;// &&
			//sceneryObject_     == obj.sceneryObject_;
}

bool ActionSceneryObject::checkForErrors(bool bComprehensive) const
{
	bool bError = Action::checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		if (parentEvent->parentScene->scenery.getDisplayedSceneryObject(sceneryObjectName_) == nullptr)
		{
			bError = true;
			qCritical() << NovelLib::ErrorType::SceneryObjectInvalid << "No valid SceneryObject assigned. Was it deleted and not replaced?";
			if (sceneryObjectName_ != "")
				qCritical() << NovelLib::ErrorType::SceneryObjectMissing << "SceneryObject \"" + sceneryObjectName_ + "\" does not exist. Definition file might be corrupted";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObject::checkForErrors of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

void ActionSceneryObject::setSceneryObject(const QString& sceneryObjectName) noexcept
{
	if (parentEvent->parentScene->scenery.getDisplayedSceneryObject(sceneryObjectName_) == nullptr)
		qCritical() << NovelLib::ErrorType::SceneryObjectMissing << "Scenery Object \"" + sceneryObjectName + "\" does not exist";
	else
	{
		sceneryObjectName_ = sceneryObjectName;  
		checkForErrors(true);
	}
}

SceneryObject* ActionSceneryObject::getSceneryObject() noexcept 
{ 
	return sceneryObject_;
}

const SceneryObject* ActionSceneryObject::getSceneryObject() const noexcept 
{ 
	return sceneryObject_; 
}

QString ActionSceneryObject::getSceneryObjectName() const noexcept
{
	return sceneryObjectName_; 
}

void ActionSceneryObject::serializableLoad(QDataStream& dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> sceneryObjectName_;
	///checkForErrors();
}

void ActionSceneryObject::serializableSave(QDataStream& dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << sceneryObjectName_;
}
