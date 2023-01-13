#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnim.h"

#include "Novel/Data/Scene.h"

template <class AnimNode>
ActionSceneryObjectAnim<AnimNode>::~ActionSceneryObjectAnim() = default;

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

template<typename AnimNode>
void swap(ActionSceneryObjectAnim<AnimNode>& first, ActionSceneryObjectAnim<AnimNode>& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<ActionSceneryObject&>(first), static_cast<ActionSceneryObject&>(second));
	swap(first.priority,                   second.priority);
	swap(first.startDelay,                 second.startDelay);
	swap(first.speed,                      second.speed);
	swap(first.timesPlayed,                second.timesPlayed);
	swap(first.bFinishAnimationAtEventEnd, second.bFinishAnimationAtEventEnd);
	first.swapPrivate(second);
}

template<typename AnimNode>
void ActionSceneryObjectAnim<AnimNode>::swapPrivate(ActionSceneryObjectAnim& second) noexcept
{
	using std::swap;
	swap(this->assetAnimName_, second.assetAnimName_);
	swap(this->assetAnim_,     second.assetAnim_);
	swap(this->animator_,      second.animator_);
}

template <class AnimNode>
ActionSceneryObjectAnim<AnimNode>::ActionSceneryObjectAnim(Event* const parentEvent, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bFinishAnimationAtEventEnd, SceneryObject* sceneryObject, AssetAnim<AnimNode>* assetAnim)
	: ActionSceneryObject(parentEvent, sceneryObjectName, sceneryObject),
	assetAnimName_(assetAnimName), 
	priority(priority), 
	startDelay(startDelay), 
	speed(speed), 
	timesPlayed(timesPlayed), 
	bFinishAnimationAtEventEnd(bFinishAnimationAtEventEnd), 
	assetAnim_(assetAnim)
{
}

//deleted
//template <class AnimNode> 
//bool ActionSceneryObjectAnim<AnimNode>::operator==(const ActionSceneryObjectAnim<AnimNode>& obj) const noexcept
//{
//	if (this == &obj)
//		return true;
//
//	return ActionSceneryObject::operator==(obj)                         &&
//		   assetAnimName_ == obj.assetAnimName_                         &&
//		   priority       == obj.priority                               &&
//		   startDelay     == obj.startDelay                             &&
//		   speed          == obj.speed                                  &&
//		   timesPlayed    == obj.timesPlayed                            &&
//		   bFinishAnimationAtEventEnd == obj.bFinishAnimationAtEventEnd;
//}

template<typename AnimNode>
void ActionSceneryObjectAnim<AnimNode>::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObject::serializableLoad(dataStream);
	dataStream >> assetAnimName_ >> priority >> startDelay >> speed >> timesPlayed >> bFinishAnimationAtEventEnd;
	//assetAnim_ is loaded in a derived class
}

template<typename AnimNode>
void ActionSceneryObjectAnim<AnimNode>::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObject::serializableSave(dataStream);
	dataStream << assetAnimName_ << priority << startDelay << speed << timesPlayed << bFinishAnimationAtEventEnd;
}

//  MEMBER_FIELD_SECTION_CHANGE END

//SetAssetAnim is defined in concrete ActionSceneryObjectAnims
template<typename AnimNode>
const AssetAnim<AnimNode>* ActionSceneryObjectAnim<AnimNode>::getAssetAnim() const noexcept
{ 
	return assetAnim_; 
}

template<typename AnimNode>
QString ActionSceneryObjectAnim<AnimNode>::getAssetAnimName() const noexcept
{
	return assetAnimName_; 
}

template<typename AnimNode>
AssetAnim<AnimNode>* ActionSceneryObjectAnim<AnimNode>::getAssetAnim() noexcept
{
	return assetAnim_;
}

#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimInstances.h"