#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimMove.h"

#include "Novel/Data/Scene.h"

ActionSceneryObjectAnimMove::ActionSceneryObjectAnimMove(Event* const parentEvent) noexcept
	: ActionSceneryObjectAnim(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionSceneryObjectAnimMove& first, ActionSceneryObjectAnimMove& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<ActionSceneryObjectAnim<AnimNodeDouble2D>&>(first), static_cast<ActionSceneryObjectAnim<AnimNodeDouble2D>&>(second));
	swap(first.onRun_, second.onRun_);
}

ActionSceneryObjectAnimMove::ActionSceneryObjectAnimMove(Event* const parentEvent, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bFinishAnimationAtEventEnd, SceneryObject* sceneryObject, AssetAnim<AnimNodeDouble2D>* assetAnim)
	: ActionSceneryObjectAnim(parentEvent, sceneryObjectName, assetAnimName, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd, sceneryObject, assetAnim)
{
	if (!assetAnim_)
		assetAnim_ = AssetManager::getInstance().getAssetAnimMove(assetAnimName_);
	errorCheck(true);
}

//deleted
//ActionSceneryObjectAnimMove::ActionSceneryObjectAnimMove(const ActionSceneryObjectAnimMove& obj) noexcept
//	: ActionSceneryObjectAnim(obj.parentEvent, obj.sceneryObjectName_, obj.assetAnimName_, obj.priority, obj.startDelay, obj.speed, obj.timesPlayed, obj.bFinishAnimationAtEventEnd, obj.sceneryObject_, obj.assetAnim_), 
//	onRun_(obj.onRun_)
//{
//}

//deleted
//bool ActionSceneryObjectAnimMove::operator==(const ActionSceneryObjectAnimMove& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return ActionSceneryObjectAnim::operator==(obj);
//}

void ActionSceneryObjectAnimMove::setOnRunListener(std::function<void(const Event* const parentEvent, const SceneryObject* const parentSceneryObject, const AssetAnimMove* const assetAnimMove, const uint& priority, const uint& startDelay, const double& speed, const int& timesPlayed, const bool& bFinishAnimationAtEventEnd)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionSceneryObjectAnimMove::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObjectAnim::serializableLoad(dataStream);
	
	if (!assetAnimName_.isEmpty())
		assetAnim_ = AssetManager::getInstance().getAssetAnimMove(assetAnimName_);
	errorCheck();
}

void ActionSceneryObjectAnimMove::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObjectAnim::serializableSave(dataStream);
}

//  MEMBER_FIELD_SECTION_CHANGE END

ActionSceneryObjectAnimMove::ActionSceneryObjectAnimMove(ActionSceneryObjectAnimMove&& obj) noexcept
	: ActionSceneryObjectAnim(obj.parentEvent)
{
	swap(*this, obj);
}

//deleted
//ActionSceneryObjectAnimMove& ActionSceneryObjectAnimMove::operator=(ActionSceneryObjectAnimMove obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

void ActionSceneryObjectAnimMove::setAssetAnim(const QString& assetAnimName, AssetAnim<AnimNodeDouble2D>* assetAnim) noexcept
{
	if (assetAnim)
	{
		if (assetAnim->name != assetAnimName)
		{
			qCritical() << NovelLib::ErrorType::AssetAnimInvalid << "AssetAnim's name missmatch (assetAnimName=\"" + assetAnimName + "\", assetAnim->name=\"" + assetAnim->name + "\")";
			return;
		}
	}
	else assetAnim = AssetManager::getInstance().getAssetAnimMove(assetAnimName);

	if (!assetAnim)
	{
		qCritical() << NovelLib::ErrorType::AssetAnimMissing << "Move AssetAnim \"" + assetAnimName + "\" does not exist";
		return;
	}
	assetAnimName_ = assetAnimName;
	assetAnim_     = assetAnim;
	errorCheck(true);
}

void ActionSceneryObjectAnimMove::acceptVisitor(ActionVisitor* visitor) 
{ 
	visitor->visitActionSceneryObjectAnimMove(this); 
}

NovelLib::SerializationID ActionSceneryObjectAnimMove::getType() const noexcept 
{ 
	return NovelLib::SerializationID::ActionSceneryObjectAnimMove;
}