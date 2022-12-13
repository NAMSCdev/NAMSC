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
	AnimatorSceneryObjectInterface()                                                     = delete;
	AnimatorSceneryObjectInterface(SceneryObject* const parentSceneryObject, AssetAnim<AnimNode>* const assetAnim, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd);
	AnimatorSceneryObjectInterface(const AnimatorSceneryObjectInterface<AnimNode>& obj)  = delete;
	AnimatorSceneryObjectInterface(AnimatorSceneryObjectInterface<AnimNode>&& obj)       = default;
	AnimatorSceneryObjectInterface& operator=(const AnimatorSceneryObjectInterface& obj) = delete;
	bool operator==(const AnimatorSceneryObjectInterface& obj)                           = delete;
	bool operator!=(const AnimatorSceneryObjectInterface& obj)                           = delete;

	virtual ~AnimatorSceneryObjectInterface() = default;

	void adjustNodes(uint offset);

    AnimNode currentAnimState(uint elapsedTime);

protected:
	SceneryObject* const parentSceneryObject_;
};
