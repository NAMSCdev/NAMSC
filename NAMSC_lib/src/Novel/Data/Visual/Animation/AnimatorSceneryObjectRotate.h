#pragma once
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

/// Does the maths behind Rotate Animation
class AnimatorSceneryObjectRotate final : public AnimatorSceneryObjectInterface<AnimNodeDouble1D>
{
public:
	AnimatorSceneryObjectRotate()                                                  = delete;
	AnimatorSceneryObjectRotate(SceneryObject* const parentSceneryObject, AssetAnim<AnimNodeDouble1D>* const assetAnim, uint priority, uint startTime, double speed, int timesPlayed, bool bStopAnimationAtEventEnd);
	AnimatorSceneryObjectRotate(const AnimatorSceneryObjectRotate& obj)            = delete;
	AnimatorSceneryObjectRotate& operator=(const AnimatorSceneryObjectRotate& obj) = delete;
	bool operator==(const AnimatorSceneryObjectRotate& obj) const                  = delete;
	bool operator!=(const AnimatorSceneryObjectRotate& obj) const                  = delete;

	void run() override;
	/// Changes rotation of the SceneryObject
	bool update(uint elapsedTime) override;
};