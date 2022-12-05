#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectScale.h"

AnimatorSceneryObjectScale::AnimatorSceneryObjectScale(SceneryObject* const parentSceneryObject, AssetAnimScale* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: AnimatorSceneryObjectInterface<AnimNodeDouble2D>(parentSceneryObject, assetAnim, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd)
{
}