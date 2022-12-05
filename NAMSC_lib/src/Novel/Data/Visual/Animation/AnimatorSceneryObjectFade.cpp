#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectFade.h"

AnimatorSceneryObjectFade::AnimatorSceneryObjectFade(SceneryObject* const parentSceneryObject, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: AnimatorSceneryObjectInterface<AnimNodeDouble1D>(parentSceneryObject, nullptr, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd)
{
}

void AnimatorSceneryObjectFade::run()
{
}

bool AnimatorSceneryObjectFade::update(uint elapsedTime)
{
	return false;
}
