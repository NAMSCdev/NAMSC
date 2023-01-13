#include "Novel/Data/Visual/Animation/AnimatorBase.h"

template<typename AnimNode>
AnimatorBase<AnimNode>::~AnimatorBase() = default;

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

template<typename AnimNode>
void AnimatorBase<AnimNode>::swapPrivate(AnimatorBase<AnimNode>& second)
{
    using std::swap;
    swap(this->adjustedNodes_, second.adjustedNodes_);
    swap(this->currentNode_,   second.currentNode_);
    swap(this->nextNode_,      second.nextNode_);
}

template<typename AnimNode>
void swap(AnimatorBase<AnimNode>& first, AnimatorBase<AnimNode>& second) noexcept
{
    using std::swap;
    swap(static_cast<AnimatorInterface&>(first), static_cast<AnimatorInterface&>(second));
    first.swapPrivate(second);
}

template<typename AnimNode>
AnimatorBase<AnimNode>::AnimatorBase(AssetAnim<AnimNode>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bFinishAnimationAtEventEnd) noexcept
    : AnimatorInterface(priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd),
    assetAnim_(assetAnim)
{
}

template<typename AnimNode>
bool AnimatorBase<AnimNode>::operator==(const AnimatorBase<AnimNode>& obj) const noexcept
{
    if (this == &obj) 
        return true;

    return AnimatorInterface::operator==(obj);// &&
    //       assetAnimName_ == assetAnimName_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

template<typename AnimNode>
uint AnimatorBase<AnimNode>::getDuration()
{
    if (adjustedNodes_.size() != 0)
        return adjustedNodes_.back().timeStamp;

    return 0;
}

#include "Novel/Data/Visual/Animation/AnimatorBaseInstances.h"