#include "Novel/Data/Visual/Animation/AnimatorBase.h"

template class AnimatorBase<AnimNodeDouble1D>;
template class AnimatorBase<AnimNodeDouble2D>;
template class AnimatorBase<AnimNodeDouble3D>;
template class AnimatorBase<AnimNodeDouble4D>;

template class AnimatorBase<AnimNodeLongLong1D>;
template class AnimatorBase<AnimNodeLongLong2D>;
template class AnimatorBase<AnimNodeLongLong3D>;
template class AnimatorBase<AnimNodeLongLong4D>;

//template<typename AnimNode>
//AnimatorBase<AnimNode>::AnimatorBase(const AnimatorBase<AnimNode>& obj)
//    : adjustedNodes_(obj.adjustedNodes_),
//      assetAnim(obj.assetAnim)
//{
//    currentNode_ = nodes->cbegin() + (obj.currentNode_ - obj.nodes->cbegin());
//    nextNode_    = currentNode_ + 1;
//}

template<typename AnimNode>
AnimatorBase<AnimNode>::AnimatorBase(AssetAnim<AnimNode>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd) noexcept
    : AnimatorInterface(priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd), assetAnim_(assetAnim)
{
}

template<typename AnimNode>
uint AnimatorBase<AnimNode>::getDuration()
{
    if (adjustedNodes_.size() != 0)
        return adjustedNodes_.back().timeStamp;

    return 0;
}
