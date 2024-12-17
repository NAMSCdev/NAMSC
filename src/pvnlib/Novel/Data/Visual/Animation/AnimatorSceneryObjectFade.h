#pragma once	
#include "pvnLib/Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

/// Does the maths behind Fade Animation
class AnimatorSceneryObjectFade final : public AnimatorSceneryObjectInterface<AnimNodeDouble1D>
{
	/// Swap trick
	friend void swap(AnimatorSceneryObjectFade& first, AnimatorSceneryObjectFade& second) noexcept;
public:
	/// \param assetAnim Points to the list of AnimNodes from an AssetAnim, which contain sequential changes that happen during the Animation
	/// \param priority Allows animation queueing
	/// \param startDelay Delay in milliseconds before the Animation will be played after the last Animator ended playing
	/// \param speed Cannot be negative
	/// \param timesPlayed If set to -1, it will be looped infinitely
	/// \param bFinishAnimationAtEventEnd Incompatible with `timesPlayed = -1`, but it is possible to place same Animator in subsequent Events and continue Animation without an interruption
	explicit AnimatorSceneryObjectFade(SceneryObject* const parentSceneryObject, uint priority = 0, uint startDelay = 0, double speed = 1.0, int timesPlayed = 1, bool bFinishAnimationAtEventEnd = false);
	AnimatorSceneryObjectFade(const AnimatorSceneryObjectFade& obj)     noexcept;
	AnimatorSceneryObjectFade(AnimatorSceneryObjectFade&& obj)          noexcept;
	AnimatorSceneryObjectFade& operator=(AnimatorSceneryObjectFade obj) noexcept;
	bool operator==(const AnimatorSceneryObjectFade& obj) const         noexcept;
	bool operator!=(const AnimatorSceneryObjectFade& obj) const         noexcept = default;

	void run() override;
	/// Changes transparency of the SceneryObject
	bool update(uint elapsedTime) override;
};