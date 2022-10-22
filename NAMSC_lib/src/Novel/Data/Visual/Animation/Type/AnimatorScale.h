#pragma once
#include "Global.h"

#include "Novel/Data/Visual/Animation/AnimatorSceneryObject.h"

/// Does the maths behind Scale Animation
class AnimatorScale	final : public AnimatorSceneryObject<AnimNodeDouble2D>
{
public:
	AnimatorScale() = default;
	AnimatorScale(QTime startTime, double speed, int timesPlayed, QString&& sceneryObjectName, QString&& animAssetName);
	AnimatorScale(const AnimatorScale& obj) { *this = obj; }
	AnimatorScale& operator=(const AnimatorScale& obj);

	/// Changes colors of the SceneryObject
	void update() override
	{
		AnimNodeDouble2D node = currentAnimState();
		sceneryObject->scale = QSize(node.state[0], node.state[1]);
	}

private:
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
};




inline AnimatorScale::AnimatorScale(QTime startTime, double speed, int timesPlayed, QString&& sceneryObjectName, QString&& animAssetName) :
	AnimatorSceneryObject<AnimNodeDouble2D>(startTime, speed, timesPlayed, move(sceneryObjectName), move(animAssetName))
{
	animAsset = AssetManager::getInstance().findAssetAnimScale(this->animAssetName);
}

inline AnimatorScale& AnimatorScale::operator=(const AnimatorScale& obj)
{
	if (this == &obj) return *this;

	AnimatorSceneryObject<AnimNodeDouble2D>::operator=(obj);

	return *this;
}