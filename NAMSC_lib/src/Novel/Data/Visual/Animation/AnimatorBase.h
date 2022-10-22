#pragma once
#include "Global.h"

#include "Novel/Data/Visual/Animation/AnimatorInterface.h"

/// Controls an Animation output that will be assigned to change something that is being animated
template<typename AnimNode>
class AnimatorBase
{
public:
	/// The destructor needs to be virtual, so the proper destructor will always be called when destroying an Animator pointer
	/// Well actually it is already virtual, since it inherits from AnimatorInterface, but this will make this class an abstract one nonetheless
	virtual ~AnimatorBase() = 0;
	AnimatorBase<AnimNode>& operator=(const AnimatorBase<AnimNode>& obj);

	/// Calculates interpolated state in time that passed from `void run()`
	AnimNode currentAnimState();

protected:
	/// Points to the AnimNodes of some AssetAnim, that contain sequential changes
	QVector<AnimNode>* nodes;

	/// AssetAnim containing all the AnimNodes
	AssetAnim<AnimNode>* assetAnim;

	/// Nodes containing current state and next state that we interpolate into
	QVector<AnimNode>::const_iterator currentNode,
									  nextNode;
};




template<typename AnimNode>
inline AnimatorBase<AnimNode>::~Animator() = default;

template<typename AnimNode>
inline AnimatorBase<AnimNode>& AnimatorBase<AnimNode>::operator=(const AnimatorBase<AnimNode>& obj)
{
	if (this == &obj) return *this;

	nodes         = obj.nodes;
	animAsset     = obj.animAsset;
	currentNode   = nodes->cbegin() + (obj.currentNode - obj.nodes->cbegin());
	nextNode      = currentNode + 1;

	return *this;
}