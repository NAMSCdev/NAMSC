#include "Novel/Data/Visual/Scenery/Scenery.h"

void SceneryObject::update(uint elapsedTime)
{
	if (playedAnimatorColorIndex_ != -1)
		if (animatorsColor_[playedAnimatorColorIndex_].update(elapsedTime))
			if (++playedAnimatorColorIndex_ > animatorsColor_.size())
				playedAnimatorColorIndex_ = -1;

	if (playedAnimatorFadeIndex_ != -1)
		if (animatorsFade_[playedAnimatorFadeIndex_].update(elapsedTime))
			if (++playedAnimatorFadeIndex_ > animatorsFade_.size())
				playedAnimatorFadeIndex_ = -1;

	if (playedAnimatorMoveIndex_ != -1)
		if (animatorsMove_[playedAnimatorMoveIndex_].update(elapsedTime))
			if (++playedAnimatorMoveIndex_ > animatorsMove_.size())
				playedAnimatorMoveIndex_ = -1;

	if (playedAnimatorRotateIndex_ != -1)
		if (animatorsRotate_[playedAnimatorRotateIndex_].update(elapsedTime))
			if (++playedAnimatorRotateIndex_ > animatorsRotate_.size())
				playedAnimatorRotateIndex_ = -1;

	if (playedAnimatorScaleIndex_ != -1)
		if (animatorsScale_[playedAnimatorScaleIndex_].update(elapsedTime))
			if (++playedAnimatorScaleIndex_ > animatorsScale_.size())
				playedAnimatorScaleIndex_ = -1;
}

void Scenery::update(uint elapsedTime)
{
	for (Character&     character     : displayedCharacters_)
		character.update(elapsedTime);

	for (SceneryObject& sceneryObject : displayedSceneryObjects_)
		sceneryObject.update(elapsedTime);
}