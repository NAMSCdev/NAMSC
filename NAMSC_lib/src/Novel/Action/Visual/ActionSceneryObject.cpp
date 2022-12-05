#include "Novel/Action/Visual/ActionSceneryObject.h"

#include "Novel/Data/Scene.h"

ActionSceneryObject::ActionSceneryObject(Event* const parentEvent, Scene* const parentScene) noexcept
	: Action(parentEvent, parentScene)
{
}

ActionSceneryObject::ActionSceneryObject(Event* const parentEvent, Scene* const parentScene, const QString& sceneryObjectName)
	: Action(parentEvent, parentScene), sceneryObjectName_(sceneryObjectName)
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
		if (parentScene_->scenery.getDisplayedSceneryObject(sceneryObjectName_) == nullptr)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::SceneryObjectInvalid << "No valid SceneryObject assigned. Was it deleted and not replaced?";
			if (sceneryObjectName_ != "")
				qCritical() << this << NovelLib::ErrorType::SceneryObjectMissing << "SceneryObject \"" << sceneryObjectName_ << "\" does not exist. Definition file might be corrupted";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObject::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}

void ActionSceneryObject::setSceneryObject(const QString& sceneryObjectName) noexcept
{
	if (parentScene_->scenery.getDisplayedSceneryObject(sceneryObjectName_) == nullptr)
		qCritical() << this << NovelLib::ErrorType::SceneryObjectMissing << "Scenery Object \"" << sceneryObjectName << "\" does not exist";
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
