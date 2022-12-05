#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimScale.h"

#include "Novel/Data/Scene.h"

ActionSceneryObjectAnimScale::ActionSceneryObjectAnimScale(Event* const parentEvent, Scene* const parentScene) noexcept
	: ActionSceneryObjectAnim(parentEvent, parentScene)
{
}

ActionSceneryObjectAnimScale::ActionSceneryObjectAnimScale(Event* const parentEvent, Scene* const parentScene, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: ActionSceneryObjectAnim(parentEvent, parentScene, sceneryObjectName, assetAnimName, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd)
{
	assetAnim_ = AssetManager::getInstance().getAssetAnimScale(assetAnimName_);
	//if (assetAnim_ == nullptr)
	//	qCritical() << this << NovelLib::AssetAnimMissing << "Scale AssetAnim \"" << assetAnimName_ << "\" does not exist. Definition file might be corrupted";
	checkForErrors(true);
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
		qDebug() << "Error occurred in ActionSceneryObjectAnimScale::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}


/// Sets a function pointer that is called (if not nullptr) after the ActionSceneryObjectAnimScale's `void run()` allowing for data read

void ActionSceneryObjectAnimScale::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, SceneryObject* parentSceneryObject, AssetAnimScale* assetAnimScale, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)> onRun) noexcept
{ 
	onRun_ = onRun; 
}

void ActionSceneryObjectAnimScale::setAssetAnim(const QString& assetAnimName) noexcept
{
	AssetAnimScale* newAssetAnim = nullptr;
	newAssetAnim = AssetManager::getInstance().getAssetAnimScale(assetAnimName);
	if (newAssetAnim == nullptr)
		qCritical() << this << NovelLib::ErrorType::AssetAnimMissing << "Scale AssetAnim \"" << assetAnimName << "\" does not exist";
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
	//	qCritical() << this << NovelLib::ErrorType::AssetAnimMissing << "Scale AssetAnim \"" << assetAnimName_ << "\" does not exist. Definition file might be corrupted";
	checkForErrors();
}

void ActionSceneryObjectAnimScale::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObjectAnim::serializableSave(dataStream);
}