#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

template class AnimatorSceneryObjectInterface<AnimNodeDouble1D>;
template class AnimatorSceneryObjectInterface<AnimNodeDouble2D>;
template class AnimatorSceneryObjectInterface<AnimNodeDouble3D>;
template class AnimatorSceneryObjectInterface<AnimNodeDouble4D>;

template class AnimatorSceneryObjectInterface<AnimNodeLongLong1D>;
template class AnimatorSceneryObjectInterface<AnimNodeLongLong2D>;
template class AnimatorSceneryObjectInterface<AnimNodeLongLong3D>;
template class AnimatorSceneryObjectInterface<AnimNodeLongLong4D>;

template<typename AnimNode>
AnimatorSceneryObjectInterface<AnimNode>::AnimatorSceneryObjectInterface(SceneryObject* const parentSceneryObject, AssetAnim<AnimNode>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: AnimatorBase<AnimNode>(assetAnim, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd), parentSceneryObject_(parentSceneryObject)
{
}

//template<typename AnimNode>
//AnimatorSceneryObjectInterface<AnimNode>& AnimatorSceneryObjectInterface<AnimNode>::operator=(const AnimatorSceneryObjectInterface<AnimNode> &obj)
//{
//	if (this == &obj) return *this;
//
//	assetAnim                = obj.assetAnim_;
//	startDelay               = obj.startDelay;
//	speed                    = obj.speed;
//	timesPlayed              = obj.timesPlayed;
//	bStopAnimationAtEventEnd = obj.bStopAnimationAtEventEnd;
//
//	return *this;
//}

template<typename AnimNode>
void AnimatorSceneryObjectInterface<AnimNode>::adjustNodes(uint offset)
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

template<typename AnimNode>
AnimNode AnimatorSceneryObjectInterface<AnimNode>::currentAnimState(uint elapsedTime)
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