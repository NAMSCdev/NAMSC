#pragma once
#include "Global.h"

#include "Story/Data/Visual/Animation/Animator.h"

///Does the maths behind Move Animation
class AnimatorMove final : public AnimatorSceneryObject<AnimNodeDouble2D>
{
public:
	AnimatorMove() = default;
	AnimatorMove(QString&& animAssetName, double speed, bool bLoop, QString&& sceneryObjectName) :
		AnimatorSceneryObject<AnimNodeDouble4D>(move(animAssetName), speed, bLoop, move(sceneryObjectName))
	{
		animAsset = AssetManager::getInstance().findAssetAnimMove(animAssetName);
	}
	AnimatorMove(const AnimatorMove& obj) { *this = obj; }
	AnimatorMove& operator=(const AnimatorMove& obj)
	{
		if (this == &obj) return *this;

		Animator<AnimNodeDouble2D>::operator=(obj);

		return *this;
	}

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
	AnimatorScale(QString&& animAssetName, double speed, bool bLoop, QString&& sceneryObjectName) :
		AnimatorSceneryObject<AnimNodeDouble4D>(move(animAssetName), speed, bLoop, move(sceneryObjectName))
	{
		animAsset = AssetManager::getInstance().findAssetAnimScale(animAssetName);
	}
	AnimatorScale(const AnimatorScale& obj) { *this = obj; }
	AnimatorScale& operator=(const AnimatorScale& obj)
	{
		if (this == &obj) return *this;

		AnimatorSceneryObject<AnimNodeDouble2D>::operator=(obj);

		return *this;
	}

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
	AnimatorRotate(QString&& animAssetName, double speed, bool bLoop, QString&& sceneryObjectName) :
		AnimatorSceneryObject<AnimNodeDouble4D>(move(animAssetName), speed, bLoop, move(sceneryObjectName))
	{
		animAsset = AssetManager::getInstance().findAssetAnimRotate(animAssetName);
	}
	AnimatorRotate(const AnimatorRotate& obj) { *this = obj; }
	AnimatorRotate& operator=(const AnimatorRotate& obj)
	{
		if (this == &obj) return *this;

		AnimatorSceneryObject<AnimNodeDouble1D>::operator=(obj);

		return *this;
	}

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
	AnimatorColor(QString&& animAssetName, double speed, bool bLoop, QString&& sceneryObjectName) :
		AnimatorSceneryObject<AnimNodeDouble4D>(move(animAssetName), speed, bLoop, move(sceneryObjectName)) 
	{
		animAsset = AssetManager::getInstance().findAssetAnimColor(animAssetName);
	}
	AnimatorColor(const AnimatorColor& obj) { *this = obj; }
	AnimatorColor& operator=(const AnimatorColor& obj)
	{
		if (this == &obj) return *this;

		AnimatorSceneryObject<AnimNodeDouble4D>::operator=(obj);

		return *this;
	}

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