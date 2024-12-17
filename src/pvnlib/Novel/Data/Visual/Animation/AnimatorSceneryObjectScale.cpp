#include "pvnLib/Novel/Data/Visual/Animation/AnimatorSceneryObjectScale.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(AnimatorSceneryObjectScale& first, AnimatorSceneryObjectScale& second) noexcept
{
	using std::swap;
	swap(static_cast<AnimatorSceneryObjectInterface<AnimNodeDouble2D>&>(first), static_cast<AnimatorSceneryObjectInterface<AnimNodeDouble2D>&>(second));
}

AnimatorSceneryObjectScale::AnimatorSceneryObjectScale(SceneryObject* const parentSceneryObject, AssetAnimScale* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bFinishAnimationAtEventEnd)
	: AnimatorSceneryObjectInterface<AnimNodeDouble2D>(parentSceneryObject, assetAnim, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd)
{
}

AnimatorSceneryObjectScale::AnimatorSceneryObjectScale(const AnimatorSceneryObjectScale& obj) noexcept
	: AnimatorSceneryObjectInterface<AnimNodeDouble2D>(obj.parentSceneryObject_, obj.assetAnim_, obj.priority, obj.startDelay, obj.speed, obj.timesPlayed, obj.bFinishAnimationAtEventEnd)
{
}

bool AnimatorSceneryObjectScale::operator==(const AnimatorSceneryObjectScale& obj) const noexcept
{
	if (this == &obj)
		return true;

	return AnimatorSceneryObjectInterface<AnimNodeDouble2D>::operator==(obj) &&
		   parentSceneryObject_ == parentSceneryObject_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

AnimatorSceneryObjectScale::AnimatorSceneryObjectScale(AnimatorSceneryObjectScale&& obj) noexcept
	: AnimatorSceneryObjectScale(obj.parentSceneryObject_)
{
	swap(*this, obj);
}

AnimatorSceneryObjectScale& AnimatorSceneryObjectScale::operator=(AnimatorSceneryObjectScale obj) noexcept
{
	if (this == &obj) return *this;
	
	swap(*this, obj);
	
	return *this;
}