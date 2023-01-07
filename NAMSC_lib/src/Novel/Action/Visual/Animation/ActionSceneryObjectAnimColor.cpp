#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimColor.h"

#include "Novel/Data/Scene.h"

ActionSceneryObjectAnimColor::ActionSceneryObjectAnimColor(Event* const parentEvent) noexcept
	: ActionSceneryObjectAnim(parentEvent)
{
}

ActionSceneryObjectAnimColor::ActionSceneryObjectAnimColor(Event* const parentEvent, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: ActionSceneryObjectAnim(parentEvent, sceneryObjectName, assetAnimName, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd)
{
	assetAnim_ = AssetManager::getInstance().getAssetAnimColor(assetAnimName_);
	//if (assetAnim_ == nullptr)
	//	qCritical() << NovelLib::ErrorType::AssetAnimMissing << "Color AssetAnim \"" + assetAnimName_ + "\" does not exist. Definition file might be corrupted";
	checkForErrors(true);
}

ActionSceneryObjectAnimColor::ActionSceneryObjectAnimColor(const ActionSceneryObjectAnimColor& obj) noexcept 
	: ActionSceneryObjectAnim(obj.parentEvent)
{
	//TODO: change to swap trick for more efficency
	*this = obj;
}

ActionSceneryObjectAnimColor& ActionSceneryObjectAnimColor::operator=(const ActionSceneryObjectAnimColor& obj) noexcept
{
	if (this == &obj) return *this;

	ActionSceneryObjectAnim::operator=(obj);
	//onRun_ = obj.onRun_;

	return *this;
}

bool ActionSceneryObjectAnimColor::operator==(const ActionSceneryObjectAnimColor& obj) const noexcept
{
	if (this == &obj) return true;

	return ActionSceneryObjectAnim::operator==(obj);
}

bool ActionSceneryObjectAnimColor::checkForErrors(bool bComprehensive) const
{
	bool bError = ActionSceneryObjectAnim::checkForErrors(bComprehensive);

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectAnimColor::checkForErrors of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

Action* ActionSceneryObjectAnimColor::clone() const
{
	ActionSceneryObjectAnimColor* clone = new ActionSceneryObjectAnimColor(*this);
	return clone;
}

void ActionSceneryObjectAnimColor::setOnRunListener(std::function<void(Event* const parentEvent, SceneryObject* parentSceneryObject, AssetAnimColor* assetAnimColor, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)> onRun) noexcept
{ 
	onRun_ = onRun;
}

void ActionSceneryObjectAnimColor::setAssetAnim(const QString& assetAnimName) noexcept
{
	AssetAnimColor* newAssetAnim = nullptr;
	newAssetAnim = AssetManager::getInstance().getAssetAnimColor(assetAnimName);
	if (newAssetAnim == nullptr)
		qCritical() << NovelLib::ErrorType::AssetAnimMissing << "Color AssetAnim \"" + assetAnimName + "\" does not exist";
	else
	{
		assetAnimName_ = assetAnimName;
		assetAnim_     = newAssetAnim;
		checkForErrors(true);
	}
}

void ActionSceneryObjectAnimColor::acceptVisitor(ActionVisitor* visitor)
{
	visitor->visitActionSceneryObjectAnimColor(this);
}

/// Needed for Serialization, to know the class of an object about to be Serialization loaded
/// \return NovelLib::SerializationID corresponding to the class of a serialized object

NovelLib::SerializationID ActionSceneryObjectAnimColor::getType() const noexcept 
{
	return NovelLib::SerializationID::ActionSceneryObjectAnimColor;
}

void ActionSceneryObjectAnimColor::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObjectAnim::serializableLoad(dataStream);

	assetAnim_ = AssetManager::getInstance().getAssetAnimColor(assetAnimName_);
	//if (assetAnim_ == nullptr)
	//	qCritical() << NovelLib::ErrorType::AssetAnimMissing << "Color AssetAnim \"" + assetAnimName_ + "\" does not exist. Definition file might be corrupted";
	checkForErrors();
}

void ActionSceneryObjectAnimColor::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObjectAnim::serializableSave(dataStream);
}