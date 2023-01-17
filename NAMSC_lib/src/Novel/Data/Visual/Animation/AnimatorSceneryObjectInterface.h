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
	explicit AnimatorSceneryObjectInterface(SceneryObject* const parentSceneryObject, AssetAnim<AnimNode>* const assetAnim = nullptr, uint priority = 0, uint startDelay = 0, double speed = 1.0, int timesPlayed = 1, bool bFinishAnimationAtEventEnd = false)
		: AnimatorBase<AnimNode>(assetAnim, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd),
		parentSceneryObject_(parentSceneryObject)
	{
	}
	AnimatorSceneryObjectInterface(const AnimatorSceneryObjectInterface<AnimNode>& obj)  noexcept = delete;
	AnimatorSceneryObjectInterface(AnimatorSceneryObjectInterface<AnimNode>&& obj)       noexcept = delete;
	AnimatorSceneryObjectInterface& operator=(const AnimatorSceneryObjectInterface& obj) noexcept = delete;
	bool operator==(const AnimatorSceneryObjectInterface& obj) const                     noexcept
	{
		if (this == &obj)
			return true;

		return AnimatorBase<AnimNode>::operator==(obj) &&
			parentSceneryObject_ == parentSceneryObject_;
	}

	bool operator!=(const AnimatorSceneryObjectInterface& obj) const                     noexcept = default;
	virtual ~AnimatorSceneryObjectInterface() = 0;

	void adjustNodes(uint offset)
	{
		//todo: add a virtual fuction that gets default animState (timeStamp = 0)
		//if (AnimatorBase<AnimNode>::animNodes_.front().timeStamp != 0)
		//    AnimatorBase<AnimNode>::adjustedNodes_.emplace_Back(0, AnimInterpolationMethod::Linear, parentSceneryObject_->);

		for (const AnimNode& node : *(AnimatorBase<AnimNode>::assetAnim_->getAnimNodes()))
		{
			AnimatorBase<AnimNode>::adjustedNodes_.emplace_back(node);
			AnimatorBase<AnimNode>::adjustedNodes_.back().timeStamp = qRound(AnimatorBase<AnimNode>::adjustedNodes_.back().timeStamp * AnimatorInterface::speed) + offset;
		}
		AnimatorBase<AnimNode>::currentNode_ = AnimatorBase<AnimNode>::adjustedNodes_.cbegin();
		AnimatorBase<AnimNode>::nextNode_ = AnimatorBase<AnimNode>::currentNode_ + 1;
	}

	AnimNode currentAnimState(uint elapsedTime)
	{
		if (AnimatorBase<AnimNode>::adjustedNodes_.size() == 0)
			return AnimNode();

		if (AnimatorInterface::timesPlayed == 0)
			return AnimatorBase<AnimNode>::adjustedNodes_.back();

		if (elapsedTime > AnimatorBase<AnimNode>::adjustedNodes_.back().timeStamp)
		{
			//Return the final state, if we are not asked to play the Animation again
			if (--AnimatorInterface::timesPlayed == 0)
				return AnimatorBase<AnimNode>::adjustedNodes_.back();

			//Reset the animation
			for (AnimNode& node : AnimatorBase<AnimNode>::adjustedNodes_)
				node.timeStamp += AnimatorBase<AnimNode>::getDuration();

			AnimatorBase<AnimNode>::currentNode_ = AnimatorBase<AnimNode>::adjustedNodes_.cbegin();
			AnimatorBase<AnimNode>::nextNode_ = AnimatorBase<AnimNode>::currentNode_ + 1;
		}
		AnimNode ret = *AnimatorBase<AnimNode>::currentNode_;

		if (AnimatorBase<AnimNode>::nextNode_ == AnimatorBase<AnimNode>::adjustedNodes_.cend())
			return ret;

		double	deltaTime = elapsedTime - AnimatorBase<AnimNode>::currentNode_->timeStamp,
			duration = AnimatorBase<AnimNode>::nextNode_->timeStamp - AnimatorBase<AnimNode>::currentNode_->timeStamp;
		switch (AnimatorBase<AnimNode>::nextNode_->interpolationMethod)
		{
		case AnimNode::AnimInterpolationMethod::Linear:
		default:
			for (uint i = 0; i != (sizeof(ret.state_) / sizeof(ret.state_[0])); ++i)
				ret.state_[i] += (AnimatorBase<AnimNode>::nextNode_->state_[i] - ret.state_[i]) * (deltaTime / duration);
			break;
		}
		return ret;
	}

protected:
	SceneryObject* const parentSceneryObject_;
};

template<typename AnimNode>
AnimatorSceneryObjectInterface<AnimNode>::~AnimatorSceneryObjectInterface() = default;

template<typename AnimNode>
void swap(AnimatorSceneryObjectInterface<AnimNode>& first, AnimatorSceneryObjectInterface<AnimNode>& second) noexcept
{
	using std::swap;
	swap(static_cast<AnimatorBase<AnimNode>&>(first), static_cast<AnimatorBase<AnimNode>&>(second));
}