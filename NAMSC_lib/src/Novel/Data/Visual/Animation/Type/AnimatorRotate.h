#pragma once
#include "Global.h"

#include "Novel/Data/Visual/Animation/AnimatorSceneryObject.h"

/// Does the maths behind Rotate Animation
class AnimatorRotate final : public AnimatorSceneryObject<AnimNodeDouble1D>
{
public:
	AnimatorRotate() = default;
	AnimatorRotate(QTime startTime, double speed, int timesPlayed, 
				   QString&& animAssetName, QString&& sceneryObjectName);
	AnimatorRotate(const AnimatorRotate& obj) { *this = obj; }
	AnimatorRotate& operator=(const AnimatorRotate& obj);

	/// Changes colors of the SceneryObject
	void update() override
	{
		sceneryObject->rotation = currentAnimState().state[0];
	}

private:
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
};




inline AnimatorRotate::AnimatorRotate(QTime startTime, double speed, int timesPlayed, 
									  QString&& animAssetName, QString&& sceneryObjectName) :
	AnimatorSceneryObject<AnimNodeDouble1D>(startTime, speed, timesPlayed, move(sceneryObjectName), move(animAssetName))
{
	animAsset = AssetManager::getInstance().findAssetAnimRotate(this->animAssetName);
}

inline AnimatorRotate& AnimatorRotate::operator=(const AnimatorRotate& obj)
{
	if (this == &obj) return *this;

	AnimatorSceneryObject<AnimNodeDouble1D>::operator=(obj);

	return *this;
}
