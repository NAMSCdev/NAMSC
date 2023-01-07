#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimScale.h"

#include "Novel/Data/Scene.h"

ActionSceneryObjectAnimScale::ActionSceneryObjectAnimScale(Event* const parentEvent) noexcept
	: ActionSceneryObjectAnim(parentEvent)
{
}

ActionSceneryObjectAnimScale::ActionSceneryObjectAnimScale(Event* const parentEvent, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: ActionSceneryObjectAnim(parentEvent, sceneryObjectName, assetAnimName, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd)
{
	assetAnim_ = AssetManager::getInstance().getAssetAnimScale(assetAnimName_);
	//if (assetAnim_ == nullptr)
	//	qCritical() << NovelLib::AssetAnimMissing << "Scale AssetAnim \"" + assetAnimName_ + "\" does not exist. Definition file might be corrupted";
	checkForErrors(true);
}

ActionSceneryObjectAnimScale::ActionSceneryObjectAnimScale(const ActionSceneryObjectAnimScale& obj) noexcept
	: ActionSceneryObjectAnim(obj.parentEvent)
{
	//TODO: change to swap trick for more efficency
	*this = obj;
}

ActionSceneryObjectAnimScale& ActionSceneryObjectAnimScale::operator=(const ActionSceneryObjectAnimScale& obj) noexcept
{
	if (this == &obj) return *this;

	ActionSceneryObjectAnim::operator=(obj);
	//onRun_ = obj.onRun_;

	return *this;
}

bool ActionSceneryObjectAnimScale::operator==(const ActionSceneryObjectAnimScale& obj) const noexcept
{
	if (this == &obj) return true;

	return ActionSceneryObjectAnim::operator==(obj);
}

bool ActionSceneryObjectAnimScale::checkForErrors(bool bComprehensive) const
{
	bool bError = ActionSceneryObjectAnim::checkForErrors(bComprehensive);

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectAnimScale::checkForErrors of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

Action* ActionSceneryObjectAnimScale::clone() const
{
	ActionSceneryObjectAnimScale* clone = new ActionSceneryObjectAnimScale(*this);
	return clone;
}

void ActionSceneryObjectAnimScale::setOnRunListener(std::function<void(Event* const parentEvent, SceneryObject* parentSceneryObject, AssetAnimScale* assetAnimScale, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)> onRun) noexcept
{ 
	onRun_ = onRun; 
}

void ActionSceneryObjectAnimScale::setAssetAnim(const QString& assetAnimName) noexcept
{
	AssetAnimScale* newAssetAnim = nullptr;
	newAssetAnim = AssetManager::getInstance().getAssetAnimScale(assetAnimName);
	if (newAssetAnim == nullptr)
		qCritical() << NovelLib::ErrorType::AssetAnimMissing << "Scale AssetAnim \"" + assetAnimName + "\" does not exist";
	else
	{
		assetAnimName_ = assetAnimName;
		assetAnim_     = newAssetAnim;
		checkForErrors(true);
	}
}

void ActionSceneryObjectAnimScale::acceptVisitor(ActionVisitor* visitor)
{ 
	visitor->visitActionSceneryObjectAnimScale(this); 
}

/// Needed for Serialization, to know the class of an object about to be Serialization loaded
/// \return NovelLib::SerializationID corresponding to the class of a serialized object

NovelLib::SerializationID ActionSceneryObjectAnimScale::getType() const noexcept
{ 
	return NovelLib::SerializationID::ActionSceneryObjectAnimScale; 
}

void ActionSceneryObjectAnimScale::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObjectAnim::serializableLoad(dataStream);

	assetAnim_ = AssetManager::getInstance().getAssetAnimScale(assetAnimName_);
	//if (assetAnim_ == nullptr)
	//	qCritical() << NovelLib::ErrorType::AssetAnimMissing << "Scale AssetAnim \"" + assetAnimName_ + "\" does not exist. Definition file might be corrupted";
	checkForErrors();
}

void ActionSceneryObjectAnimScale::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObjectAnim::serializableSave(dataStream);
}