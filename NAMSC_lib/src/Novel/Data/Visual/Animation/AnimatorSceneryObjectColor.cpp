#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectColor.h"

AnimatorSceneryObjectColor::AnimatorSceneryObjectColor(SceneryObject* const parentSceneryObject, AssetAnim<AnimNodeDouble4D>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: AnimatorSceneryObjectInterface<AnimNodeDouble4D>(parentSceneryObject, assetAnim, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd)
{
}