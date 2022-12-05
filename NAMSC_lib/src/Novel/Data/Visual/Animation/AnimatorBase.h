#pragma once

#include <QList>

#include "Novel/Data/Asset/AssetAnim.h"
#include "Novel/Data/Visual/Animation/AnimatorInterface.h"

/// Controls an Animation output that will be assigned to change something that is being animated
template<typename AnimNode>
class AnimatorBase : public AnimatorInterface
{
public:
	AnimatorBase()                                                 = delete;
	AnimatorBase(AssetAnim<AnimNode>* const assetAnim) noexcept;
	AnimatorBase(const AnimatorBase<AnimNode>& obj)                = delete;
	AnimatorBase<AnimNode>& operator=(AnimatorBase<AnimNode> obj)  = delete;
	bool operator==(const AnimatorBase<AnimNode>& obj) const       = delete;
	bool operator!=(const AnimatorBase<AnimNode>& obj) const       = delete;
	virtual ~AnimatorBase()                                        = default;

	/// Calculates interpolated state
	virtual AnimNode currentAnimState(uint elapsedTime)       = 0;

	uint getDuration();

protected:
	/// Points to the list of AnimNodes from an AssetAnim, which contain sequential changes that happen during the Animation
	/// These nodes are premultiplied by the Animation speed, so we don't need to waste CPU clocks every `AnimNode currentAnimState()`
	/// The initial state is added as the first Node, unless there is an AnimNode with `startDelay = 0` 
	/// \todo check if the first Node is necessary to be added
	QList<AnimNode> adjustedNodes_;

	AssetAnim<AnimNode>* const assetAnim_;

	/// Nodes containing current state and next state that we interpolate into
	QList<AnimNode>::const_iterator currentNode_,
									nextNode_;
};