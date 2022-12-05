#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

template<typename AnimNode>
AnimatorSceneryObjectInterface<AnimNode>::AnimatorSceneryObjectInterface(SceneryObject* const parentSceneryObject, AssetAnim<AnimNode>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: AnimatorInterface(assetAnim, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd)
{
}

//template<typename AnimNode>
//AnimatorSceneryObjectInterface<AnimNode>& AnimatorSceneryObjectInterface<AnimNode>::operator=(const AnimatorSceneryObjectInterface<AnimNode> &obj)
//{
//	if (this == &obj) return *this;
//
//	assetAnim                = obj.assetAnim_;
//	startDelay               = obj.startDelay;
//	speed                    = obj.speed;
//	timesPlayed              = obj.timesPlayed;
//	bStopAnimationAtEventEnd = obj.bStopAnimationAtEventEnd;
//
//	return *this;
//}
