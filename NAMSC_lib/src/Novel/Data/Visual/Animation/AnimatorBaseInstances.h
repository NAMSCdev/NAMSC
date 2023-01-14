template class AnimatorBase<AnimNodeDouble<1>>;
template class AnimatorBase<AnimNodeDouble<2>>;
template class AnimatorBase<AnimNodeDouble<3>>;
template class AnimatorBase<AnimNodeDouble<4>>;

template class AnimatorBase<AnimNodeLongLong<1>>;
template class AnimatorBase<AnimNodeLongLong<2>>;
template class AnimatorBase<AnimNodeLongLong<3>>;
template class AnimatorBase<AnimNodeLongLong<4>>;

template void swap<AnimNodeDouble<1>>(AnimatorBase<AnimNodeDouble<1>>& first, AnimatorBase<AnimNodeDouble<1>>& second) noexcept;
template void swap<AnimNodeDouble<2>>(AnimatorBase<AnimNodeDouble<2>>& first, AnimatorBase<AnimNodeDouble<2>>& second) noexcept;
template void swap<AnimNodeDouble<3>>(AnimatorBase<AnimNodeDouble<3>>& first, AnimatorBase<AnimNodeDouble<3>>& second) noexcept;
template void swap<AnimNodeDouble<4>>(AnimatorBase<AnimNodeDouble<4>>& first, AnimatorBase<AnimNodeDouble<4>>& second) noexcept;

template void swap<AnimNodeLongLong<1>>(AnimatorBase<AnimNodeLongLong<1>>& first, AnimatorBase<AnimNodeLongLong<1>>& second) noexcept;
template void swap<AnimNodeLongLong<2>>(AnimatorBase<AnimNodeLongLong<2>>& first, AnimatorBase<AnimNodeLongLong<2>>& second) noexcept;
template void swap<AnimNodeLongLong<3>>(AnimatorBase<AnimNodeLongLong<3>>& first, AnimatorBase<AnimNodeLongLong<3>>& second) noexcept;
template void swap<AnimNodeLongLong<4>>(AnimatorBase<AnimNodeLongLong<4>>& first, AnimatorBase<AnimNodeLongLong<4>>& second) noexcept;