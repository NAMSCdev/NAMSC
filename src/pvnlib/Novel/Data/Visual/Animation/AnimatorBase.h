#pragma once

#include <vector>

#include "pvnLib/Novel/Data/Asset/AssetAnim.h"
#include "pvnLib/Novel/Data/Visual/Animation/AnimatorInterface.h"

/// \todo Add AssetAnim name
/// Controls an Animation output that will be assigned to change something that is being animated
template<typename AnimNode>
class AnimatorBase : public AnimatorInterface
{
public:
	/// \param assetAnim Points to the list of AnimNodes from an AssetAnim, which contain sequential changes that happen during the Animation
	/// \param priority Allows animation queueing
	/// \param startDelay Delay in milliseconds before the Animation will be played after the last Animator ended playing
	/// \param speed Cannot be negative
	/// \param timesPlayed If set to -1, it will be looped infinitely
	/// \param bFinishAnimationAtEventEnd Incompatible with `timesPlayed = -1`, but it is possible to place same Animator in subsequent Events and continue Animation without an interruption
	AnimatorBase(AssetAnim<AnimNode>* const assetAnim = nullptr, uint priority = 0, uint startDelay = 0, double speed = 1.0, int timesPlayed = 1, bool bFinishAnimationAtEventEnd = false) noexcept
		: AnimatorInterface(priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd),
		assetAnim_(assetAnim)
	{
	}

	AnimatorBase(const AnimatorBase<AnimNode>& obj)                       noexcept = delete;
	AnimatorBase(AnimatorBase<AnimNode>&& obj)                            noexcept = delete;
	AnimatorBase<AnimNode>& operator=(const AnimatorBase<AnimNode>& obj)  noexcept = delete;
	bool operator==(const AnimatorBase<AnimNode>& obj) const              noexcept
	{
		if (this == &obj)
			return true;

		return AnimatorInterface::operator==(obj);
	}

	bool operator!=(const AnimatorBase<AnimNode>& obj) const              noexcept = default;
	virtual ~AnimatorBase() = 0;

	/// Calculates interpolated state
	virtual AnimNode currentAnimState(uint elapsedTime) = 0;

	uint getDuration()
	{
		if (adjustedNodes_.size() != 0)
			return adjustedNodes_.back().timeStamp;

		return 0;
	}

	void swapPrivate(AnimatorBase<AnimNode>& second)
	{
		using std::swap;
		swap(this->adjustedNodes_, second.adjustedNodes_);
		swap(this->currentNode_, second.currentNode_);
		swap(this->nextNode_, second.nextNode_);
	}

protected:
	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Points to the list of AnimNodes from an AssetAnim, which contain sequential changes that happen during the Animation
	/// These nodes are premultiplied by the Animation speed, so we don't need to waste CPU clocks every `AnimNode currentAnimState()`
	/// The initial state is added as the first Node, unless there is an AnimNode with `startDelay = 0` 
	/// \todo check if the first Node is necessary to be added
	std::vector<AnimNode> adjustedNodes_;

	AssetAnim<AnimNode>* const assetAnim_;

	/// Nodes containing current state and next state that we interpolate into
	std::vector<AnimNode>::const_iterator currentNode_,
										  nextNode_;
};

template<typename AnimNode>
AnimatorBase<AnimNode>::~AnimatorBase() = default;

template<typename AnimNode>
void swap(AnimatorBase<AnimNode>& first, AnimatorBase<AnimNode>& second) noexcept
{
	using std::swap;
	swap(static_cast<AnimatorInterface&>(first), static_cast<AnimatorInterface&>(second));
	first.swapPrivate(second);
}