#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimFade.h"

#include "Novel/Data/Scene.h"

ActionSceneryObjectAnimFade::ActionSceneryObjectAnimFade(Event* const parentEvent) noexcept
	: ActionSceneryObjectAnim(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionSceneryObjectAnimFade& first, ActionSceneryObjectAnimFade& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<ActionSceneryObjectAnim<AnimNodeDouble1D>&>(first), static_cast<ActionSceneryObjectAnim<AnimNodeDouble1D>&>(second));
	swap(first.duration, second.duration);
	swap(first.bAppear,  second.bAppear);
	swap(first.onRun_,   second.onRun_);
}

ActionSceneryObjectAnimFade::ActionSceneryObjectAnimFade(Event* const parentEvent, const QString& sceneryObjectName, uint priority, uint startDelay, bool bFinishAnimationAtEventEnd, uint duration, bool bAppear, SceneryObject* sceneryObject, AssetAnim<AnimNodeDouble1D>* assetAnim)
	: ActionSceneryObjectAnim(parentEvent, sceneryObjectName, "", priority, startDelay, 1.0, 1, bFinishAnimationAtEventEnd, sceneryObject, assetAnim),
	duration(duration), 
	bAppear(bAppear)
{
	errorCheck(true);
}

ActionSceneryObjectAnimFade::ActionSceneryObjectAnimFade(const ActionSceneryObjectAnimFade& obj) noexcept
	: ActionSceneryObjectAnim(obj.parentEvent, obj.sceneryObjectName_, "", obj.priority, obj.startDelay, 1.0, 1, obj.bFinishAnimationAtEventEnd, obj.sceneryObject_, obj.assetAnim_), 
	duration(obj.duration), 
	bAppear(obj.bAppear),
	onRun_(obj.onRun_)
{
}

bool ActionSceneryObjectAnimFade::operator==(const ActionSceneryObjectAnimFade& obj) const noexcept
{
	if (this == &obj) return true;

	return ActionSceneryObjectAnim::operator==(obj) &&
		   duration != obj.duration                 &&
		   bAppear  != obj.bAppear;           
}

void ActionSceneryObjectAnimFade::setOnRunListener(std::function<void(const Event* const parentEvent, const SceneryObject* const sceneryObject, const uint& priority, const uint& startDelay, const bool& bFinishAnimationAtEventEnd, uint duration, bool bAppear)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionSceneryObjectAnimFade::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObjectAnim::serializableLoad(dataStream);
	dataStream >> duration >> bAppear;

	errorCheck();
}

void ActionSceneryObjectAnimFade::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObjectAnim::serializableSave(dataStream);
	dataStream << duration << bAppear;
}

//  MEMBER_FIELD_SECTION_CHANGE END

ActionSceneryObjectAnimFade::ActionSceneryObjectAnimFade(ActionSceneryObjectAnimFade&& obj) noexcept
	: ActionSceneryObjectAnim(obj.parentEvent)
{
	swap(*this, obj);
}

ActionSceneryObjectAnimFade& ActionSceneryObjectAnimFade::operator=(ActionSceneryObjectAnimFade obj) noexcept
{
	if (this == &obj) return *this;

	swap(*this, obj);

	return *this;
}

void ActionSceneryObjectAnimFade::setAssetAnim(const QString& assetAnimName, AssetAnim<AnimNodeDouble1D>* assetAnim) noexcept
{
}

void ActionSceneryObjectAnimFade::acceptVisitor(ActionVisitor* visitor)
{
	visitor->visitActionSceneryObjectAnimFade(this);
}

NovelLib::SerializationID ActionSceneryObjectAnimFade::getType() const noexcept
{
	return NovelLib::SerializationID::ActionSceneryObjectAnimFade; 
}