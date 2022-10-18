#pragma once
#include "Global.h"

#include "Novel/Data/Visual/Animation/AnimatorSceneryObject.h"

///Does the maths behind Move Animation
class AnimatorMove final : public AnimatorSceneryObject<AnimNodeDouble2D>
{
public:
	AnimatorMove() = default;
	AnimatorMove(QTime startTime, double speed, int timesPlayed, QString&& sceneryObjectName, QString&& animAssetName);
	AnimatorMove(const AnimatorMove& obj) { *this = obj; }
	AnimatorMove& operator=(const AnimatorMove& obj);

	///Changes colors of the SceneryObject
	void update() override
	{
		AnimNodeDouble2D node = currentAnimState();
		sceneryObject->pos = QPoint(node.state[0], node.state[1]);
	}

private:
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
};

///Does the maths behind Scale Animation
class AnimatorScale	final : public AnimatorSceneryObject<AnimNodeDouble2D>
{
public:
	AnimatorScale() = default;
	AnimatorScale(QTime startTime, double speed, int timesPlayed, QString&& sceneryObjectName, QString&& animAssetName);
	AnimatorScale(const AnimatorScale& obj) { *this = obj; }
	AnimatorScale& operator=(const AnimatorScale& obj);

	///Changes colors of the SceneryObject
	void update() override
	{
		AnimNodeDouble2D node = currentAnimState();
		sceneryObject->scale = QSize(node.state[0], node.state[1]);
	}

private:
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
};

///Does the maths behind Rotate Animation
class AnimatorRotate final : public AnimatorSceneryObject<AnimNodeDouble1D>
{
public:
	AnimatorRotate() = default;
	AnimatorRotate(QTime startTime, double speed, int timesPlayed, QString&& sceneryObjectName, QString&& animAssetName);
	AnimatorRotate(const AnimatorRotate& obj) { *this = obj; }
	AnimatorRotate& operator=(const AnimatorRotate& obj);

	///Changes colors of the SceneryObject
	void update() override
	{
		sceneryObject->rotation = currentAnimState().state[0];
	}

private:
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
};

///Does the maths behind Color Animation
class AnimatorColor final : public AnimatorSceneryObject<AnimNodeDouble4D>
{
public:
	AnimatorColor() = default;
	AnimatorColor(QTime startTime, double speed, int timesPlayed, QString&& sceneryObjectName, QString&& animAssetName);
	AnimatorColor(const AnimatorColor& obj) { *this = obj; }
	AnimatorColor& operator=(const AnimatorColor& obj);

	///Changes colors of the SceneryObject
	void update() override 
	{ 
		AnimNodeDouble4D node = currentAnimState();
#pragma unroll
		for (int i = 0; i != 4; ++i)
			sceneryObject->color[i] = node.state[i];
	}

private:
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
};





inline AnimatorMove::AnimatorMove(QTime startTime, double speed, int timesPlayed, QString&& sceneryObjectName, QString&& animAssetName) : 
	AnimatorSceneryObject<AnimNodeDouble2D>(startTime, speed, timesPlayed, move(sceneryObjectName), move(animAssetName))
{
	animAsset = AssetManager::getInstance().findAssetAnimMove(this->animAssetName);
}

inline AnimatorScale::AnimatorScale(QTime startTime, double speed, int timesPlayed, QString&& sceneryObjectName, QString&& animAssetName) :
	AnimatorSceneryObject<AnimNodeDouble2D>(startTime, speed, timesPlayed, move(sceneryObjectName), move(animAssetName))
{
	animAsset = AssetManager::getInstance().findAssetAnimScale(this->animAssetName);
}

inline AnimatorMove& AnimatorMove::operator=(const AnimatorMove& obj)
{
	if (this == &obj) return *this;

	AnimatorSceneryObject<AnimNodeDouble2D>::operator=(obj);

	return *this;
}

inline AnimatorRotate& AnimatorRotate::operator=(const AnimatorRotate& obj)
{
	if (this == &obj) return *this;

	AnimatorSceneryObject<AnimNodeDouble1D>::operator=(obj);

	return *this;
}

inline AnimatorScale& AnimatorScale::operator=(const AnimatorScale& obj)
{
	if (this == &obj) return *this;

	AnimatorSceneryObject<AnimNodeDouble2D>::operator=(obj);

	return *this;
}

inline AnimatorColor& AnimatorColor::operator=(const AnimatorColor& obj)
{
	if (this == &obj) return *this;

	AnimatorSceneryObject<AnimNodeDouble4D>::operator=(obj);

	return *this;
}
