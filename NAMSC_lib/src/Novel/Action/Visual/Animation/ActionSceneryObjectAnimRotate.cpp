#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimRotate.h"

#include "Novel/Data/Scene.h"

ActionSceneryObjectAnimRotate::ActionSceneryObjectAnimRotate(Event* const parentEvent) noexcept
	: ActionSceneryObjectAnim<AnimNodeDouble1D>(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionSceneryObjectAnimRotate& first, ActionSceneryObjectAnimRotate& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<ActionSceneryObjectAnim<AnimNodeDouble1D>&>(first), static_cast<ActionSceneryObjectAnim<AnimNodeDouble1D>&>(second));
	swap(first.onRun_, second.onRun_);
}

ActionSceneryObjectAnimRotate::ActionSceneryObjectAnimRotate(Event* const parentEvent, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bFinishAnimationAtEventEnd, SceneryObject* sceneryObject, AssetAnim<AnimNodeDouble1D>* assetAnim)
	: ActionSceneryObjectAnim(parentEvent, sceneryObjectName, assetAnimName, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd, sceneryObject, assetAnim)
{
	if (!assetAnim_)
		assetAnim_ = AssetManager::getInstance().getAssetAnimRotate(assetAnimName_);
	errorCheck(true);
}

//deleted	
//ActionSceneryObjectAnimRotate::ActionSceneryObjectAnimRotate(const ActionSceneryObjectAnimRotate& obj) noexcept
//	: ActionSceneryObjectAnim(obj.parentEvent, obj.sceneryObjectName_, obj.assetAnimName_, obj.priority, obj.startDelay, obj.speed, obj.timesPlayed, obj.bFinishAnimationAtEventEnd, obj.sceneryObject_, obj.assetAnim_),
//	onRun_(obj.onRun_)
//{
//}

//deleted
//bool ActionSceneryObjectAnimRotate::operator==(const ActionSceneryObjectAnimRotate& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return ActionSceneryObjectAnim::operator==(obj);
//}

void ActionSceneryObjectAnimRotate::setOnRunListener(std::function<void(const Event* const parentEvent, const SceneryObject* const parentSceneryObject, const AssetAnimRotate* const assetAnimRotate, const uint& priority, const uint& startDelay, const double& speed, const int& timesPlayed, const bool& bFinishAnimationAtEventEnd)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionSceneryObjectAnimRotate::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObjectAnim::serializableLoad(dataStream);

	if (!assetAnimName_.isEmpty())
		assetAnim_ = AssetManager::getInstance().getAssetAnimRotate(assetAnimName_);
	errorCheck();
}

void ActionSceneryObjectAnimRotate::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObjectAnim::serializableSave(dataStream);
}

//  MEMBER_FIELD_SECTION_CHANGE END

ActionSceneryObjectAnimRotate::ActionSceneryObjectAnimRotate(ActionSceneryObjectAnimRotate&& obj) noexcept
	: ActionSceneryObjectAnim(obj.parentEvent)
{
	swap(*this, obj);
}

//deleted
//ActionSceneryObjectAnimRotate& ActionSceneryObjectAnimRotate::operator=(ActionSceneryObjectAnimRotate obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

void ActionSceneryObjectAnimRotate::setAssetAnim(const QString& assetAnimName, AssetAnim<AnimNodeDouble1D>* assetAnim) noexcept
{
	if (assetAnim)
	{
		if (assetAnim->name != assetAnimName)
		{
			qCritical() << NovelLib::ErrorType::AssetAnimInvalid << "AssetAnim's name missmatch (assetAnimName=\"" + assetAnimName + "\", assetAnim->name=\"" + assetAnim->name + "\")";
			return;
		}
	}
	else assetAnim = AssetManager::getInstance().getAssetAnimRotate(assetAnimName);

	if (!assetAnim)
	{
		qCritical() << NovelLib::ErrorType::AssetAnimMissing << "Rotate AssetAnim \"" + assetAnimName + "\" does not exist";
		return;
	}
	assetAnimName_ = assetAnimName;
	assetAnim_     = assetAnim;
	errorCheck(true);
}

void ActionSceneryObjectAnimRotate::acceptVisitor(ActionVisitor* visitor) 
{ 
	visitor->visitActionSceneryObjectAnimRotate(this); 
}

NovelLib::SerializationID ActionSceneryObjectAnimRotate::getType() const noexcept 
{ 
	return NovelLib::SerializationID::ActionSceneryObjectAnimRotate; 
}
