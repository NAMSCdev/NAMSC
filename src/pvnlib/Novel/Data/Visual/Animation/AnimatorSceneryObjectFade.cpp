#include "pvnLib/Novel/Data/Visual/Animation/AnimatorSceneryObjectFade.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(AnimatorSceneryObjectFade& first, AnimatorSceneryObjectFade& second) noexcept
{
	using std::swap;
	swap(static_cast<AnimatorSceneryObjectInterface<AnimNodeDouble1D>&>(first), static_cast<AnimatorSceneryObjectInterface<AnimNodeDouble1D>&>(second));
}

AnimatorSceneryObjectFade::AnimatorSceneryObjectFade(SceneryObject* const parentSceneryObject, uint priority, uint startDelay, double speed, int timesPlayed, bool bFinishAnimationAtEventEnd)
	: AnimatorSceneryObjectInterface<AnimNodeDouble1D>(parentSceneryObject, nullptr, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd)
{
}

AnimatorSceneryObjectFade::AnimatorSceneryObjectFade(const AnimatorSceneryObjectFade& obj) noexcept
	: AnimatorSceneryObjectInterface<AnimNodeDouble1D>(obj.parentSceneryObject_, nullptr, obj.priority, obj.startDelay, obj.speed, obj.timesPlayed, obj.bFinishAnimationAtEventEnd)
{
}

bool AnimatorSceneryObjectFade::operator==(const AnimatorSceneryObjectFade& obj) const noexcept
{
	if (this == &obj)
		return true;

	return AnimatorSceneryObjectInterface<AnimNodeDouble1D>::operator==(obj) &&
		   parentSceneryObject_ == parentSceneryObject_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

AnimatorSceneryObjectFade::AnimatorSceneryObjectFade(AnimatorSceneryObjectFade&& obj) noexcept
	: AnimatorSceneryObjectFade(obj.parentSceneryObject_)
{
	swap(*this, obj);
}

AnimatorSceneryObjectFade& AnimatorSceneryObjectFade::operator=(AnimatorSceneryObjectFade obj) noexcept
{
	if (this == &obj) return *this;

	swap(*this, obj);

	return *this;
}