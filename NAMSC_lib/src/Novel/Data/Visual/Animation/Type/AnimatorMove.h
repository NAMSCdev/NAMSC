#pragma once
#include "Global.h"

#include "Novel/Data/Visual/Animation/AnimatorSceneryObject.h"

/// Does the maths behind Move Animation
class AnimatorMove final : public AnimatorSceneryObject<AnimNodeDouble2D>
{
public:
	AnimatorMove() = default;
	AnimatorMove(QTime startTime, double speed, int timesPlayed, QString&& animAssetName, QString&& sceneryObjectName);
	AnimatorMove(const AnimatorMove& obj) { *this = obj; }
	AnimatorMove& operator=(const AnimatorMove& obj);

	/// Changes colors of the SceneryObject
	void update() override
	{
		AnimNodeDouble2D node = currentAnimState();
		sceneryObject->pos = QPoint(node.state[0], node.state[1]);
	}

private:
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
};




inline AnimatorMove::AnimatorMove(QTime startTime, double speed, int timesPlayed,
								  QString&& animAssetName, QString&& sceneryObjectName) : 
	AnimatorSceneryObject<AnimNodeDouble2D>(startTime, speed, timesPlayed, move(sceneryObjectName), move(animAssetName))
{
	animAsset = AssetManager::getInstance().findAssetAnimMove(this->animAssetName);
}

inline AnimatorMove& AnimatorMove::operator=(const AnimatorMove& obj)
{
	if (this == &obj) return *this;

	AnimatorSceneryObject<AnimNodeDouble2D>::operator=(obj);

	return *this;
}
