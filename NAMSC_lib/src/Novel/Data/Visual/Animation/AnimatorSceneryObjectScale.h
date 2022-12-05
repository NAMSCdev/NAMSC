#pragma once	
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

/// Does the maths behind Scale Animation
class AnimatorSceneryObjectScale final : public AnimatorSceneryObjectInterface<AnimNodeDouble2D>
{
public:
	AnimatorSceneryObjectScale()                                                 = delete;
	AnimatorSceneryObjectScale(SceneryObject* const parentSceneryObject, AssetAnimScale* const assetAnim, uint priority, uint startTime, double speed, int timesPlayed, bool bStopAnimationAtEventEnd);
	AnimatorSceneryObjectScale(const AnimatorSceneryObjectScale& obj)            = delete;
	AnimatorSceneryObjectScale& operator=(const AnimatorSceneryObjectScale& obj) = delete;
	bool operator==(const AnimatorSceneryObjectScale& obj) const                 = delete;
	bool operator!=(const AnimatorSceneryObjectScale& obj) const                 = delete;

	void run() override;
	/// Changes scale of the SceneryObject
	bool update(uint elapsedTime) override;
};