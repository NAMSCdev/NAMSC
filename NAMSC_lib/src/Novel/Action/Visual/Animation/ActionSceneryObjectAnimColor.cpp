#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimColor.h"

#include "Novel/Data/Scene.h"

ActionSceneryObjectAnimColor::ActionSceneryObjectAnimColor(Event* const parentEvent, Scene* const parentScene) noexcept
	: ActionSceneryObjectAnim(parentEvent, parentScene)
{
}

ActionSceneryObjectAnimColor::ActionSceneryObjectAnimColor(Event* const parentEvent, Scene* const parentScene, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: ActionSceneryObjectAnim(parentEvent, parentScene, sceneryObjectName, assetAnimName, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd)
{
	assetAnim_ = AssetManager::getInstance().getAssetAnimColor(assetAnimName_);
	//if (assetAnim_ == nullptr)
	//	qCritical() << this << NovelLib::ErrorType::AssetAnimMissing << "Color AssetAnim \"" << assetAnimName_ << "\" does not exist. Definition file might be corrupted";
	checkForErrors(true);
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

/// Sets a function pointer that is called (if not nullptr) after the ActionSceneryObjectAnimColor's `void run()` allowing for data read

void ActionSceneryObjectAnimColor::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, SceneryObject* parentSceneryObject, AssetAnimColor* assetAnimColor, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)> onRun) noexcept
{ 
	onRun_ = onRun;
}

void ActionSceneryObjectAnimColor::setAssetAnim(const QString& assetAnimName) noexcept
{
	AssetAnimColor* newAssetAnim = nullptr;
	newAssetAnim = AssetManager::getInstance().getAssetAnimColor(assetAnimName);
	if (newAssetAnim == nullptr)
		qCritical() << this << NovelLib::ErrorType::AssetAnimMissing << "Color AssetAnim \"" << assetAnimName << "\" does not exist";
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

bool ActionSceneryObjectAnimColor::checkForErrors(bool bComprehensive) const
{
	bool bError = ActionSceneryObjectAnim::checkForErrors(bComprehensive);

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectAnimColor::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}

void ActionSceneryObjectAnimColor::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObjectAnim::serializableLoad(dataStream);

	assetAnim_ = AssetManager::getInstance().getAssetAnimColor(assetAnimName_);
	//if (assetAnim_ == nullptr)
	//	qCritical() << this << NovelLib::ErrorType::AssetAnimMissing << "Color AssetAnim \"" << assetAnimName_ << "\" does not exist. Definition file might be corrupted";
	checkForErrors();
}

void ActionSceneryObjectAnimColor::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObjectAnim::serializableSave(dataStream);
}