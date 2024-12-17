#include "pvnLib/Novel/Action/Visual/Animation/ActionSceneryObjectAnimColor.h"

#include "pvnLib/Novel/Data/Scene.h"

ActionSceneryObjectAnimColor::ActionSceneryObjectAnimColor(Event* const parentEvent) noexcept
	: ActionSceneryObjectAnim(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionSceneryObjectAnimColor& first, ActionSceneryObjectAnimColor& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<ActionSceneryObjectAnim<AnimNodeDouble4D>&>(first), static_cast<ActionSceneryObjectAnim<AnimNodeDouble4D>&>(second));
	swap(first.onRun_, second.onRun_);
}

ActionSceneryObjectAnimColor::ActionSceneryObjectAnimColor(Event* const parentEvent, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bFinishAnimationAtEventEnd, SceneryObject* sceneryObject, AssetAnim<AnimNodeDouble4D>* assetAnim)
	: ActionSceneryObjectAnim(parentEvent, sceneryObjectName, assetAnimName, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd, sceneryObject, assetAnim)
{
	if (!assetAnim_)
		assetAnim_ = AssetManager::getInstance().getAssetAnimColor(assetAnimName_);
	errorCheck(true);
}

ActionSceneryObjectAnimColor::ActionSceneryObjectAnimColor(const ActionSceneryObjectAnimColor& obj) noexcept 
	: ActionSceneryObjectAnim(obj.parentEvent, obj.sceneryObjectName_, obj.assetAnimName_, obj.priority, obj.startDelay, obj.speed, obj.timesPlayed, obj.bFinishAnimationAtEventEnd, obj.sceneryObject_, obj.assetAnim_),
	onRun_(obj.onRun_)
{
}

bool ActionSceneryObjectAnimColor::operator==(const ActionSceneryObjectAnimColor& obj) const noexcept
{
	if (this == &obj) 
		return true;

	return ActionSceneryObjectAnim::operator==(obj);
}

void ActionSceneryObjectAnimColor::setOnRunListener(std::function<void(const Event* const parentEvent, const SceneryObject* const parentSceneryObject, const AssetAnimColor* const assetAnimColor, const uint& priority, const uint& startDelay, const double& speed, const int& timesPlayed, const bool& bFinishAnimationAtEventEnd)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionSceneryObjectAnimColor::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObjectAnim::serializableLoad(dataStream);
	
	if (!assetAnimName_.isEmpty())
		assetAnim_ = AssetManager::getInstance().getAssetAnimColor(assetAnimName_);
	errorCheck();
}

void ActionSceneryObjectAnimColor::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObjectAnim::serializableSave(dataStream);
}

//  MEMBER_FIELD_SECTION_CHANGE END

ActionSceneryObjectAnimColor::ActionSceneryObjectAnimColor(ActionSceneryObjectAnimColor&& obj) noexcept
	: ActionSceneryObjectAnim(obj.parentEvent)
{
	swap(*this, obj);
}

ActionSceneryObjectAnimColor& ActionSceneryObjectAnimColor::operator=(ActionSceneryObjectAnimColor obj) noexcept
{
	if (this == &obj) return *this;

	swap(*this, obj);

	return *this;
}

void ActionSceneryObjectAnimColor::setAssetAnim(const QString& assetAnimName, AssetAnim<AnimNodeDouble4D>* assetAnim) noexcept
{
	if (assetAnim)
	{
		if (assetAnim->name != assetAnimName)
		{
			qCritical() << NovelLib::ErrorType::AssetAnimInvalid << "AssetAnim's name missmatch (assetAnimName=\"" + assetAnimName + "\", assetAnim->name=\"" + assetAnim->name + "\")";
			return;
		}
	}
	else assetAnim = AssetManager::getInstance().getAssetAnimColor(assetAnimName);

	if (!assetAnim)
	{
		qCritical() << NovelLib::ErrorType::AssetAnimMissing << "Color AssetAnim \"" + assetAnimName + "\" does not exist";
		return;
	}
	assetAnimName_ = assetAnimName;
	assetAnim_     = assetAnim;
	errorCheck(true);
}

void ActionSceneryObjectAnimColor::acceptVisitor(ActionVisitor* visitor)
{
	visitor->visitActionSceneryObjectAnimColor(this);
}

NovelLib::SerializationID ActionSceneryObjectAnimColor::getType() const noexcept 
{
	return NovelLib::SerializationID::ActionSceneryObjectAnimColor;
}