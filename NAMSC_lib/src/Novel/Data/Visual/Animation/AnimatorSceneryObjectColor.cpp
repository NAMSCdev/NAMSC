#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectColor.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(AnimatorSceneryObjectColor& first, AnimatorSceneryObjectColor& second) noexcept
{
	using std::swap;
	swap(static_cast<AnimatorSceneryObjectInterface<AnimNodeDouble4D>&>(first), static_cast<AnimatorSceneryObjectInterface<AnimNodeDouble4D>&>(second));
}

AnimatorSceneryObjectColor::AnimatorSceneryObjectColor(SceneryObject* const parentSceneryObject, AssetAnim<AnimNodeDouble4D>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bFinishAnimationAtEventEnd)
	: AnimatorSceneryObjectInterface<AnimNodeDouble4D>(parentSceneryObject, assetAnim, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd)
{
}

AnimatorSceneryObjectColor::AnimatorSceneryObjectColor(const AnimatorSceneryObjectColor& obj) noexcept
	: AnimatorSceneryObjectColor(obj.parentSceneryObject_)
{
}

bool AnimatorSceneryObjectColor::operator==(const AnimatorSceneryObjectColor& obj) const noexcept
{
	if (this == &obj)
		return true;

	return AnimatorSceneryObjectInterface<AnimNodeDouble4D>::operator==(obj) &&
		   parentSceneryObject_ == parentSceneryObject_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

AnimatorSceneryObjectColor::AnimatorSceneryObjectColor(AnimatorSceneryObjectColor&& obj) noexcept
	: AnimatorSceneryObjectColor(obj.parentSceneryObject_)
{
	swap(*this, obj);
}

AnimatorSceneryObjectColor& AnimatorSceneryObjectColor::operator=(AnimatorSceneryObjectColor obj) noexcept
{
	if (this == &obj) return *this;

	swap(*this, obj);

	return *this;
}