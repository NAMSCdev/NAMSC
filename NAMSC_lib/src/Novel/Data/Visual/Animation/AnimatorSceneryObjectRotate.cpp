#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectRotate.h"

AnimatorSceneryObjectRotate::AnimatorSceneryObjectRotate(SceneryObject* const parentSceneryObject, AssetAnim<AnimNodeDouble1D>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: AnimatorSceneryObjectInterface<AnimNodeDouble1D>(parentSceneryObject, assetAnim, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd)
{
}