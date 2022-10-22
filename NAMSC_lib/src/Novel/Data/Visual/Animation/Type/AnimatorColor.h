#pragma once
#include "Global.h"

#include "Novel/Data/Visual/Animation/AnimatorSceneryObject.h"

//Performs a Color Animation on a SceneryObject
class AnimatorColor final : public AnimatorSceneryObject<AnimNodeDouble4D>
{
public:
	AnimatorColor() = default;
	AnimatorColor(QTime startTime, double speed, int timesPlayed,
				  QString&& sceneryObjectName, QString&& animAssetName);
	AnimatorColor(const AnimatorColor& obj) { *this = obj; }
	AnimatorColor& operator=(const AnimatorColor& obj);

	/// Changes colors of the SceneryObject
	void update() override 
	{ 
		AnimNodeDouble4D node = currentAnimState();
#pragma unroll
		for (int i = 0; i != 4; ++i)
			sceneryObject->color[i] = node.state[i];
	}

private:
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
};




inline AnimatorColor::AnimatorColor(QTime startTime, double speed, int timesPlayed,
									QString&& sceneryObjectName, QString&& animAssetName) : 
	AnimatorSceneryObject<AnimNodeDouble4D>(startTime, speed, timesPlayed, move(sceneryObjectName), move(animAssetName))
{
	animAsset = AssetManager::getInstance().findAssetAnimColor(this->animAssetName);
}

inline AnimatorColor& AnimatorColor::operator=(const AnimatorColor& obj)
{
	if (this == &obj) return *this;

	AnimatorSceneryObject<AnimNodeDouble4D>::operator=(obj);

	return *this;
}
