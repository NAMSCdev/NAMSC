#pragma once
#include "pvnLib/Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

/// Does the maths behind Move Animation
class AnimatorSceneryObjectMove final : public AnimatorSceneryObjectInterface<AnimNodeDouble2D>
{
	/// Swap trick
	friend void swap(AnimatorSceneryObjectMove& first, AnimatorSceneryObjectMove& second) noexcept;
public:
	/// \param assetAnim Points to the list of AnimNodes from an AssetAnim, which contain sequential changes that happen during the Animation
	/// \param priority Allows animation queueing
	/// \param startDelay Delay in milliseconds before the Animation will be played after the last Animator ended playing
	/// \param speed Cannot be negative
	/// \param timesPlayed If set to -1, it will be looped infinitely
	/// \param bFinishAnimationAtEventEnd Incompatible with `timesPlayed = -1`, but it is possible to place same Animator in subsequent Events and continue Animation without an interruption
	explicit AnimatorSceneryObjectMove(SceneryObject* const parentSceneryObject, AssetAnim<AnimNodeDouble2D>* const assetAnim = nullptr, uint priority = 0, uint startDelay = 0, double speed = 1.0, int timesPlayed = 1, bool bFinishAnimationAtEventEnd = false);
	AnimatorSceneryObjectMove(const AnimatorSceneryObjectMove& obj)     noexcept;
	AnimatorSceneryObjectMove(AnimatorSceneryObjectMove&& obj)          noexcept;
	AnimatorSceneryObjectMove& operator=(AnimatorSceneryObjectMove obj) noexcept;
	bool operator==(const AnimatorSceneryObjectMove& obj) const         noexcept;
	bool operator!=(const AnimatorSceneryObjectMove& obj) const         noexcept = default;

	void run() override;
	/// Changes position of the SceneryObject
	bool update(uint elapsedTime) override;
};
