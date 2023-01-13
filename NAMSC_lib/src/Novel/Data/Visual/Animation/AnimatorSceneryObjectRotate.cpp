#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectRotate.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(AnimatorSceneryObjectRotate& first, AnimatorSceneryObjectRotate& second) noexcept
{
	using std::swap;
	swap(static_cast<AnimatorSceneryObjectInterface<AnimNodeDouble1D>&>(first), static_cast<AnimatorSceneryObjectInterface<AnimNodeDouble1D>&>(second));
}

AnimatorSceneryObjectRotate::AnimatorSceneryObjectRotate(SceneryObject* const parentSceneryObject, AssetAnim<AnimNodeDouble1D>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bFinishAnimationAtEventEnd)
	: AnimatorSceneryObjectInterface<AnimNodeDouble1D>(parentSceneryObject, assetAnim, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd)
{
}

AnimatorSceneryObjectRotate::AnimatorSceneryObjectRotate(const AnimatorSceneryObjectRotate& obj) noexcept
	: AnimatorSceneryObjectInterface<AnimNodeDouble1D>(obj.parentSceneryObject_, obj.assetAnim_, obj.priority, obj.startDelay, obj.speed, obj.timesPlayed, obj.bFinishAnimationAtEventEnd)
{
}

bool AnimatorSceneryObjectRotate::operator==(const AnimatorSceneryObjectRotate& obj) const noexcept
{
	if (this == &obj)
		return true;

	return AnimatorSceneryObjectInterface<AnimNodeDouble1D>::operator==(obj) &&
		   parentSceneryObject_ == parentSceneryObject_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

AnimatorSceneryObjectRotate::AnimatorSceneryObjectRotate(AnimatorSceneryObjectRotate&& obj) noexcept
	: AnimatorSceneryObjectRotate(obj.parentSceneryObject_)
{
	swap(*this, obj);
}

AnimatorSceneryObjectRotate& AnimatorSceneryObjectRotate::operator=(AnimatorSceneryObjectRotate obj) noexcept
{
	if (this == &obj) return *this;

	swap(*this, obj);

	return *this;
}