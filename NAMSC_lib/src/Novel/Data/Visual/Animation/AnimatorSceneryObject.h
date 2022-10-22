#pragma once
#include "Global.h"

#include "Novel/Data/Visual/Animation/AnimatorBase.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

//Performs an Animation on a SceneryObject
template<typename AnimNode>
class AnimatorSceneryObject : public AnimatorBase<AnimNode>, public AnimatorSceneryObjectInterface
{
public:
	AnimatorSceneryObject() = default;
	AnimatorSceneryObject(QTime startTime, double speed, int timesPlayed, QString&& animAssetName, QString&& sceneryObjectName);
	AnimatorSceneryObject(const AnimatorSceneryObject<AnimNode>& obj) { *this = obj; }
	AnimatorSceneryObject<AnimNode>& operator=(const AnimatorSceneryObject<AnimNode>& obj);

	/// Checks if the AnimatorSceneryObject doesn't have any errors, which would halt the Novel execution
	virtual bool checkForErrors() override;

protected:
	virtual void ensureResourcesAreLoaded() override;
};




template<typename AnimNode>
inline AnimatorSceneryObject<AnimNode>::AnimatorSceneryObject(QTime startTime, double speed, int timesPlayed, QString&& animAssetName, QString&& sceneryObjectName) :
	AnimatorSceneryObjectInterface(startTime, speed, timesPlayed, move(sceneryObjectName), move(animAssetName))
{
}

template<typename AnimNode>
inline AnimatorSceneryObject<AnimNode>& AnimatorSceneryObject<AnimNode>::operator=(const AnimatorSceneryObject<AnimNode>& obj)
{
	if (this == &obj) return *this;

	AnimatorSceneryObjectInterface::operator=(obj);
	AnimatorBase<AnimNode>::operator=(obj);

	return *this;
}

template<typename AnimNode>
inline void AnimatorSceneryObject<AnimNode>::ensureResourcesAreLoaded() 
{ 
	if (!AnimatorSceneryObject<AnimNode>::animAsset->isLoaded())
		AnimatorSceneryObject<AnimNode>::animAsset->load();

	AnimatorSceneryObject<AnimNode>::nodes = AnimatorSceneryObject<AnimNode>::animAsset->getAnimNodes();
}