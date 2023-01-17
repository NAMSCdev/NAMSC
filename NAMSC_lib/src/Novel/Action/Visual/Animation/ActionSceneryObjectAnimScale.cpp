#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimScale.h"

#include "Novel/Data/Scene.h"

ActionSceneryObjectAnimScale::ActionSceneryObjectAnimScale(Event* const parentEvent) noexcept
	: ActionSceneryObjectAnim(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionSceneryObjectAnimScale& first, ActionSceneryObjectAnimScale& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<ActionSceneryObjectAnim<AnimNodeDouble2D>&>(first), static_cast<ActionSceneryObjectAnim<AnimNodeDouble2D>&>(second));
	swap(first.onRun_, second.onRun_);
}

ActionSceneryObjectAnimScale::ActionSceneryObjectAnimScale(Event* const parentEvent, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bFinishAnimationAtEventEnd, SceneryObject* sceneryObject, AssetAnim<AnimNodeDouble2D>* assetAnim)
	: ActionSceneryObjectAnim(parentEvent, sceneryObjectName, assetAnimName, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd, sceneryObject, assetAnim)
{
	if (!assetAnim_)
		assetAnim_ = AssetManager::getInstance().getAssetAnimScale(assetAnimName_);
	errorCheck(true);
}

//deleted
//ActionSceneryObjectAnimScale::ActionSceneryObjectAnimScale(const ActionSceneryObjectAnimScale& obj) noexcept
//	: ActionSceneryObjectAnim(obj.parentEvent, obj.sceneryObjectName_, obj.assetAnimName_, obj.priority, obj.startDelay, obj.speed, obj.timesPlayed, obj.bFinishAnimationAtEventEnd, obj.sceneryObject_, obj.assetAnim_),
//	onRun_(obj.onRun_)
//{
//}

//deleted
//bool ActionSceneryObjectAnimScale::operator==(const ActionSceneryObjectAnimScale& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return ActionSceneryObjectAnim::operator==(obj);
//}

void ActionSceneryObjectAnimScale::setOnRunListener(std::function<void(const Event* const parentEvent, const SceneryObject* const parentSceneryObject, const AssetAnimScale* const assetAnimScale, const uint& priority, const uint& startDelay, const double& speed, const int& timesPlayed, const bool& bFinishAnimationAtEventEnd)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionSceneryObjectAnimScale::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObjectAnim::serializableLoad(dataStream);
	
	if (!assetAnimName_.isEmpty())
		assetAnim_ = AssetManager::getInstance().getAssetAnimScale(assetAnimName_);
	errorCheck();
}

void ActionSceneryObjectAnimScale::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObjectAnim::serializableSave(dataStream);
}

//  MEMBER_FIELD_SECTION_CHANGE END

ActionSceneryObjectAnimScale::ActionSceneryObjectAnimScale(ActionSceneryObjectAnimScale&& obj) noexcept
	: ActionSceneryObjectAnim(obj.parentEvent)
{
	swap(*this, obj);
}

//deleted
//ActionSceneryObjectAnimScale& ActionSceneryObjectAnimScale::operator=(ActionSceneryObjectAnimScale obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

void ActionSceneryObjectAnimScale::setAssetAnim(const QString& assetAnimName, AssetAnim<AnimNodeDouble2D>* assetAnim) noexcept
{
	if (assetAnim)
	{
		if (assetAnim->name != assetAnimName)
		{
			qCritical() << NovelLib::ErrorType::AssetAnimInvalid << "AssetAnim's name missmatch (assetAnimName=\"" + assetAnimName + "\", assetAnim->name=\"" + assetAnim->name + "\")";
			return;
		}
	}
	else assetAnim = AssetManager::getInstance().getAssetAnimScale(assetAnimName);

	if (assetAnim == nullptr)
	{
		qCritical() << NovelLib::ErrorType::AssetAnimMissing << "Scale AssetAnim \"" + assetAnimName + "\" does not exist";
		return;
	}
	assetAnimName_ = assetAnimName;
	assetAnim_     = assetAnim;
	errorCheck(true);
}

void ActionSceneryObjectAnimScale::acceptVisitor(ActionVisitor* visitor)
{ 
	visitor->visitActionSceneryObjectAnimScale(this); 
}

NovelLib::SerializationID ActionSceneryObjectAnimScale::getType() const noexcept
{ 
	return NovelLib::SerializationID::ActionSceneryObjectAnimScale; 
}