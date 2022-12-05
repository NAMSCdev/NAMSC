#pragma once	
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

/// Does the maths behind Fade Animation
class AnimatorSceneryObjectFade final : public AnimatorSceneryObjectInterface<AnimNodeDouble1D>
{
public:
	AnimatorSceneryObjectFade()                                                = delete;
	AnimatorSceneryObjectFade(SceneryObject* const parentSceneryObject, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd);
	AnimatorSceneryObjectFade(const AnimatorSceneryObjectFade& obj)            = delete;
	AnimatorSceneryObjectFade& operator=(const AnimatorSceneryObjectFade& obj) = delete;
	bool operator==(const AnimatorSceneryObjectFade& obj) const                = delete;
	bool operator!=(const AnimatorSceneryObjectFade& obj) const                = delete;

	void run() override;
	/// Changes transparency of the SceneryObject
	bool update(uint elapsedTime) override;
};