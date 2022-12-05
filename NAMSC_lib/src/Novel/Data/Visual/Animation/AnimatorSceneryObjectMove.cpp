#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectMove.h"

AnimatorSceneryObjectMove::AnimatorSceneryObjectMove(SceneryObject* const parentSceneryObject, AssetAnim<AnimNodeDouble2D>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: AnimatorSceneryObjectInterface<AnimNodeDouble2D>(parentSceneryObject, assetAnim, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd)
{
}