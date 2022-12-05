#pragma once
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

/// Does the maths behind Move Animation
class AnimatorSceneryObjectMove final : public AnimatorSceneryObjectInterface<AnimNodeDouble2D>
{
public:
	AnimatorSceneryObjectMove()                                                = delete;
	AnimatorSceneryObjectMove(SceneryObject* const parentSceneryObject, AssetAnim<AnimNodeDouble2D>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd);
	AnimatorSceneryObjectMove(const AnimatorSceneryObjectMove& obj)            = delete;
	AnimatorSceneryObjectMove(AnimatorSceneryObjectMove&& obj)                 = default;
	AnimatorSceneryObjectMove& operator=(const AnimatorSceneryObjectMove& obj) = delete;
	bool operator==(const AnimatorSceneryObjectMove& obj) const                = delete;
	bool operator!=(const AnimatorSceneryObjectMove& obj) const                = delete;

	void run() override;
	/// Changes position of the SceneryObject
	bool update(uint elapsedTime) override;
};
