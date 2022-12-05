#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimMove.h"

#include "Novel/Data/Scene.h"

ActionSceneryObjectAnimMove::ActionSceneryObjectAnimMove(Event* const parentEvent, Scene* const parentScene) noexcept
	: ActionSceneryObjectAnim(parentEvent, parentScene)
{
}

ActionSceneryObjectAnimMove::ActionSceneryObjectAnimMove(Event* const parentEvent, Scene* const parentScene, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: ActionSceneryObjectAnim(parentEvent, parentScene, sceneryObjectName, assetAnimName, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd)
{
	assetAnim_ = AssetManager::getInstance().getAssetAnimMove(assetAnimName_);
	//if (assetAnim_ == nullptr)
	//	qCritical() << this << NovelLib::AssetAnimMissing << "Move AssetAnim \"" << assetAnimName_ << "\" does not exist. Definition file might be corrupted";
	checkForErrors(true);
}

ActionSceneryObjectAnimMove& ActionSceneryObjectAnimMove::operator=(const ActionSceneryObjectAnimMove& obj) noexcept
{
	if (this == &obj) return *this;

	ActionSceneryObjectAnim::operator=(obj);
	//onRun_ = obj.onRun_;

	return *this;
}

bool ActionSceneryObjectAnimMove::operator==(const ActionSceneryObjectAnimMove& obj) const noexcept
{
	if (this == &obj) return true;

	return ActionSceneryObjectAnim::operator==(obj);
}

bool ActionSceneryObjectAnimMove::checkForErrors(bool bComprehensive) const
{
	bool bError = ActionSceneryObjectAnim::checkForErrors(bComprehensive);

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectAnimMove::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}


/// Sets a function pointer that is called (if not nullptr) after the ActionSceneryObjectAnimMove's `void run()` allowing for data read

void ActionSceneryObjectAnimMove::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, SceneryObject* parentSceneryObject, AssetAnimMove* assetAnimMove, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)> onRun) noexcept 
{ 
	onRun_ = onRun;
}

void ActionSceneryObjectAnimMove::setAssetAnim(const QString& assetAnimName) noexcept
{
	AssetAnimMove* newAssetAnim = nullptr;
	newAssetAnim = AssetManager::getInstance().getAssetAnimMove(assetAnimName);
	if (newAssetAnim == nullptr)
		qCritical() << this << NovelLib::ErrorType::AssetAnimMissing << "Move AssetAnim \"" << assetAnimName << "\" does not exist";
	else
	{
		assetAnimName_ = assetAnimName;
		assetAnim_     = newAssetAnim;
		checkForErrors(true);
	}
}

void ActionSceneryObjectAnimMove::acceptVisitor(ActionVisitor* visitor) 
{ 
	visitor->visitActionSceneryObjectAnimMove(this); 
}

/// Needed for Serialization, to know the class of an object about to be Serialization loaded
/// \return NovelLib::SerializationID corresponding to the class of a serialized object

NovelLib::SerializationID ActionSceneryObjectAnimMove::getType() const noexcept 
{ 
	return NovelLib::SerializationID::ActionSceneryObjectAnimMove;
}

void ActionSceneryObjectAnimMove::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObjectAnim::serializableLoad(dataStream);
	//if (assetAnimName_ == "")
	//	qCritical() << this << NovelLib::AssetAnimInvalid << "Move AssetAnim is not specified";

	assetAnim_ = AssetManager::getInstance().getAssetAnimMove(assetAnimName_);
	//if (assetAnim_ == nullptr)
	//	qCritical() << this << NovelLib::AssetAnimMissing << "Move AssetAnim \"" << assetAnimName_ << "\" does not exist. Definition file might be corrupted";

	checkForErrors();
}

void ActionSceneryObjectAnimMove::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObjectAnim::serializableSave(dataStream);
}