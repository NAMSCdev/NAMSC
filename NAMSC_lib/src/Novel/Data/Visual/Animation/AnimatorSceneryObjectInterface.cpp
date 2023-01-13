#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

template<typename AnimNode>
AnimatorSceneryObjectInterface<AnimNode>::~AnimatorSceneryObjectInterface() = default;

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

template<typename AnimNode>
void swap(AnimatorSceneryObjectInterface<AnimNode>& first, AnimatorSceneryObjectInterface<AnimNode>& second) noexcept
{
    using std::swap;
    swap(static_cast<AnimatorBase<AnimNode>&>(first), static_cast<AnimatorBase<AnimNode>&>(second));
}

template<typename AnimNode>
AnimatorSceneryObjectInterface<AnimNode>::AnimatorSceneryObjectInterface(SceneryObject* const parentSceneryObject, AssetAnim<AnimNode>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bFinishAnimationAtEventEnd)
	: AnimatorBase<AnimNode>(assetAnim, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd), 
    parentSceneryObject_(parentSceneryObject)
{
}

template<typename AnimNode>
bool AnimatorSceneryObjectInterface<AnimNode>::operator==(const AnimatorSceneryObjectInterface& obj) const noexcept
{
    if (this == &obj)
        return true;

    return AnimatorBase<AnimNode>::operator==(obj)      &&
           parentSceneryObject_ == parentSceneryObject_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

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

#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterfaceInstances.h"