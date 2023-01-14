#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectColor.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectMove.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectRotate.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectScale.h"

#include "Novel/Data/Visual/Scenery/SceneryObject.h"

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

bool AnimatorSceneryObjectColor::update(uint elapsedTime)
{
    AnimNodeDouble4D node = currentAnimState(elapsedTime);
    for (int i = 0; i != 4; ++i)
        parentSceneryObject_->colorMultiplier[i] = node.state_[i];

    return elapsedTime >= getDuration();
}

bool AnimatorSceneryObjectFade::update(uint elapsedTime)
{
    return false;
}

bool AnimatorSceneryObjectMove::update(uint elapsedTime)
{
    AnimNodeDouble2D node = currentAnimState(elapsedTime);
    parentSceneryObject_->pos = QPoint(node.state_[0], node.state_[1]);

    return elapsedTime >= getDuration();
}

bool AnimatorSceneryObjectRotate::update(uint elapsedTime)
{
    AnimNodeDouble1D node = currentAnimState(elapsedTime);
    parentSceneryObject_->rotationDegree = node.state_[0];

    return elapsedTime >= getDuration();
}

bool AnimatorSceneryObjectScale::update(uint elapsedTime)
{
    AnimNodeDouble2D node = currentAnimState(elapsedTime);
    parentSceneryObject_->scale = QSize(node.state_[0], node.state_[1]);

    return elapsedTime >= getDuration();
}

#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterfaceInstances.h"