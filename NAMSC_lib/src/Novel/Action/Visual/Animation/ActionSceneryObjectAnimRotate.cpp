#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimRotate.h"

#include "Novel/Data/Scene.h"

ActionSceneryObjectAnimRotate::ActionSceneryObjectAnimRotate(Event* const parentEvent, Scene* const parentScene) noexcept
	: ActionSceneryObjectAnim<AnimNodeDouble1D>(parentEvent, parentScene)
{
}

ActionSceneryObjectAnimRotate::ActionSceneryObjectAnimRotate(Event* const parentEvent, Scene* const parentScene, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: ActionSceneryObjectAnim(parentEvent, parentScene, sceneryObjectName, assetAnimName, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd)
{
	assetAnim_ = AssetManager::getInstance().getAssetAnimRotate(assetAnimName_);
	//if (assetAnim_ == nullptr)
	//	qCritical() << this << NovelLib::AssetAnimMissing << "Rotate AssetAnim \"" << assetAnimName_ << "\" does not exist. Definition file might be corrupted";
	checkForErrors(true);
}

ActionSceneryObjectAnimRotate& ActionSceneryObjectAnimRotate::operator=(const ActionSceneryObjectAnimRotate& obj) noexcept
{
	if (this == &obj) return *this;

	ActionSceneryObjectAnim::operator=(obj);
	//onRun_ = obj.onRun_;

	return *this;
}

bool ActionSceneryObjectAnimRotate::operator==(const ActionSceneryObjectAnimRotate& obj) const noexcept
{
	if (this == &obj) return true;

	return ActionSceneryObjectAnim::operator==(obj);
}

bool ActionSceneryObjectAnimRotate::checkForErrors(bool bComprehensive) const
{
	bool bError = ActionSceneryObjectAnim::checkForErrors(bComprehensive);

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectAnimRotate::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}

void ActionSceneryObjectAnimRotate::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, SceneryObject* parentSceneryObject, AssetAnimRotate* assetAnimRotate, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)> onRun) noexcept
{ 
	onRun_ = onRun;
}

void ActionSceneryObjectAnimRotate::setAssetAnim(const QString& assetAnimName) noexcept
{
	AssetAnimRotate* newAssetAnim = nullptr;
	newAssetAnim = AssetManager::getInstance().getAssetAnimRotate(assetAnimName);
	if (newAssetAnim == nullptr)
		qCritical() << this << NovelLib::ErrorType::AssetAnimMissing << "Rotate AssetAnim \"" << assetAnimName << "\" does not exist";
	else
	{
		assetAnimName_ = assetAnimName;
		assetAnim_     = newAssetAnim;
		checkForErrors(true);
	}
}

void ActionSceneryObjectAnimRotate::acceptVisitor(ActionVisitor* visitor) 
{ 
	visitor->visitActionSceneryObjectAnimRotate(this); 
}

/// Needed for Serialization, to know the class of an object about to be Serialization loaded
/// \return NovelLib::SerializationID corresponding to the class of a serialized object

NovelLib::SerializationID ActionSceneryObjectAnimRotate::getType() const noexcept 
{ 
	return NovelLib::SerializationID::ActionSceneryObjectAnimRotate; 
}

void ActionSceneryObjectAnimRotate::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObjectAnim::serializableLoad(dataStream);

	assetAnim_ = AssetManager::getInstance().getAssetAnimRotate(assetAnimName_);
	//if (assetAnim_ == nullptr)
	//	qCritical() << this << NovelLib::ErrorType::AssetAnimMissing << "Rotate AssetAnim \"" << assetAnimName_ << "\" does not exist. Definition file might be corrupted";
	checkForErrors();
}

void ActionSceneryObjectAnimRotate::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObjectAnim::serializableSave(dataStream);
}