#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectMove.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(AnimatorSceneryObjectMove& first, AnimatorSceneryObjectMove& second) noexcept
{
	using std::swap;
	swap(static_cast<AnimatorSceneryObjectInterface<AnimNodeDouble2D>&>(first), static_cast<AnimatorSceneryObjectInterface<AnimNodeDouble2D>&>(second));
}

AnimatorSceneryObjectMove::AnimatorSceneryObjectMove(SceneryObject* const parentSceneryObject, AssetAnim<AnimNodeDouble2D>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bFinishAnimationAtEventEnd)
	: AnimatorSceneryObjectInterface<AnimNodeDouble2D>(parentSceneryObject, assetAnim, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd)
{
}

AnimatorSceneryObjectMove::AnimatorSceneryObjectMove(const AnimatorSceneryObjectMove& obj) noexcept
	: AnimatorSceneryObjectInterface<AnimNodeDouble2D>(obj.parentSceneryObject_, obj.assetAnim_, obj.priority, obj.startDelay, obj.speed, obj.timesPlayed, obj.bFinishAnimationAtEventEnd)
{
}

bool AnimatorSceneryObjectMove::operator==(const AnimatorSceneryObjectMove& obj) const noexcept
{
	if (this == &obj)
		return true;

	return AnimatorSceneryObjectInterface<AnimNodeDouble2D>::operator==(obj) &&
		   parentSceneryObject_ == parentSceneryObject_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

AnimatorSceneryObjectMove::AnimatorSceneryObjectMove(AnimatorSceneryObjectMove&& obj) noexcept
	: AnimatorSceneryObjectMove(obj.parentSceneryObject_)
{
	swap(*this, obj);
}

AnimatorSceneryObjectMove& AnimatorSceneryObjectMove::operator=(AnimatorSceneryObjectMove obj) noexcept
{
	if (this == &obj) return *this;

	swap(*this, obj);

	return *this;
}
