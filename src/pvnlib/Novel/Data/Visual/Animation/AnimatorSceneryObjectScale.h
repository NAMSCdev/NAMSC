#pragma once	
#include "pvnLib/Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

/// Does the maths behind Scale Animation
class AnimatorSceneryObjectScale final : public AnimatorSceneryObjectInterface<AnimNodeDouble2D>
{
	/// Swap trick
	friend void swap(AnimatorSceneryObjectScale& first, AnimatorSceneryObjectScale& second) noexcept;
public:
	/// \param assetAnim Points to the list of AnimNodes from an AssetAnim, which contain sequential changes that happen during the Animation
	/// \param priority Allows animation queueing
	/// \param startDelay Delay in milliseconds before the Animation will be played after the last Animator ended playing
	/// \param speed Cannot be negative
	/// \param timesPlayed If set to -1, it will be looped infinitely
	/// \param bFinishAnimationAtEventEnd Incompatible with `timesPlayed = -1`, but it is possible to place same Animator in subsequent Events and continue Animation without an interruption
	explicit AnimatorSceneryObjectScale(SceneryObject* const parentSceneryObject, AssetAnimScale* const assetAnim = nullptr, uint priority = 0, uint startDelay = 0, double speed = 1.0, int timesPlayed = 1, bool bFinishAnimationAtEventEnd = false);
	AnimatorSceneryObjectScale(const AnimatorSceneryObjectScale& obj)     noexcept;
	AnimatorSceneryObjectScale(AnimatorSceneryObjectScale&& obj)          noexcept;
	AnimatorSceneryObjectScale& operator=(AnimatorSceneryObjectScale obj) noexcept;
	bool operator==(const AnimatorSceneryObjectScale& obj) const          noexcept;
	bool operator!=(const AnimatorSceneryObjectScale& obj) const          noexcept = default;

	void run() override;
	/// Changes scale of the SceneryObject
	bool update(uint elapsedTime) override;
};