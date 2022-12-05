#include "Novel/Data/Visual/Animation/AnimatorBase.h"

//template<typename AnimNode>
//AnimatorBase<AnimNode>::AnimatorBase(const AnimatorBase<AnimNode>& obj)
//    : adjustedNodes_(obj.adjustedNodes_),
//      assetAnim(obj.assetAnim)
//{
//    currentNode_ = nodes->cbegin() + (obj.currentNode_ - obj.nodes->cbegin());
//    nextNode_    = currentNode_ + 1;
//}

template<typename AnimNode>
AnimatorBase<AnimNode>::AnimatorBase(AssetAnim<AnimNode>* const assetAnim) noexcept
    : assetAnim_(assetAnim)
{
}

template<typename AnimNode>
uint AnimatorBase<AnimNode>::getDuration()
{
    if (adjustedNodes_->size() != 0)
        return adjustedNodes_.back().timeStamp;

    return 0;
}
