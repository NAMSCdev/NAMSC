#pragma once
#include "Novel/Data/Visual/Animation/AnimatorBase.h"
#include "Novel/Data/Visual/Animation/AnimatorInterface.h"

class SceneryObject;

/// Performs an Animation on a SceneryObject
template<typename AnimNode>
class AnimatorSceneryObjectInterface : public AnimatorBase<AnimNode>
{
	friend class Scenery;
public:
	/// \param assetAnim Points to the list of AnimNodes from an AssetAnim, which contain sequential changes that happen during the Animation
	/// \param priority Allows animation queueing
	/// \param startDelay Delay in milliseconds before the Animation will be played after the last Animator ended playing
	/// \param speed Cannot be negative
	/// \param timesPlayed If set to -1, it will be looped infinitely
	/// \param bFinishAnimationAtEventEnd Incompatible with `timesPlayed = -1`, but it is possible to place same Animator in subsequent Events and continue Animation without an interruption
	explicit AnimatorSceneryObjectInterface(SceneryObject* const parentSceneryObject, AssetAnim<AnimNode>* const assetAnim = nullptr, uint priority = 0, uint startDelay = 0, double speed = 1.0, int timesPlayed = 1, bool bFinishAnimationAtEventEnd = false);
	AnimatorSceneryObjectInterface(const AnimatorSceneryObjectInterface<AnimNode>& obj)  noexcept = delete;
	AnimatorSceneryObjectInterface(AnimatorSceneryObjectInterface<AnimNode>&& obj)       noexcept = delete;
	AnimatorSceneryObjectInterface& operator=(const AnimatorSceneryObjectInterface& obj) noexcept = delete;
	bool operator==(const AnimatorSceneryObjectInterface& obj) const                     noexcept;
	bool operator!=(const AnimatorSceneryObjectInterface& obj) const                     noexcept = default;
	virtual ~AnimatorSceneryObjectInterface() = 0;

	void adjustNodes(uint offset);

    AnimNode currentAnimState(uint elapsedTime);

protected:
	SceneryObject* const parentSceneryObject_;
};
