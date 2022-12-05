#pragma once
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

/// Performs a Color Animation on a SceneryObject
class AnimatorSceneryObjectColor final : public AnimatorSceneryObjectInterface<AnimNodeDouble4D>
{
public:
	AnimatorSceneryObjectColor()                                                 = delete;
	AnimatorSceneryObjectColor(SceneryObject* const parentSceneryObject, AssetAnim<AnimNodeDouble4D>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd);
	AnimatorSceneryObjectColor(const AnimatorSceneryObjectColor& obj)            = delete;
	AnimatorSceneryObjectColor& operator=(const AnimatorSceneryObjectColor& obj) = delete;
	bool operator==(const AnimatorSceneryObjectColor& obj) const                 = delete;
	bool operator!=(const AnimatorSceneryObjectColor& obj) const                 = delete;

	void run() override;
	/// Changes colors of the SceneryObject
	bool update(uint elapsedTime) override;
};