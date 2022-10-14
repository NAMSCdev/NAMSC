#pragma once
#include "Global.h"

#include "Story/Data/Visual/Animation/Animator.h"

///Does the maths behind Move Animation
class AnimatorMove final : public AnimatorSceneryObject<AnimNodeDouble2D>
{
public:
	AnimatorMove() = default;
	AnimatorMove(QString&& animAssetName, bool bLoop, QString&& sceneryObjectName) :
		AnimatorSceneryObject<AnimNodeDouble4D>(move(animAssetName), bLoop, move(sceneryObjectName))
	{
		animAsset = AssetManager::getInstance().findAnimAssetMove(animAssetName);
	}
	AnimatorMove(const AnimatorMove&) = default;
	AnimatorMove& operator=(const AnimatorMove&) = default;

	///Changes colors of the SceneryObject
	void update() override
	{
		AnimNodeDouble2D node = currentAnimState();
#pragma unroll
		for (int i = 0; i != 2; ++i)
			sceneryObject->pos[i] = node.state[i];
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
	AnimatorScale(QString&& animAssetName, bool bLoop, QString&& sceneryObjectName) :
		AnimatorSceneryObject<AnimNodeDouble4D>(move(animAssetName), bLoop, move(sceneryObjectName))
	{
		animAsset = AssetManager::getInstance().findAnimAssetScale(animAssetName);
	}
	AnimatorScale(const AnimatorScale&) = default;
	AnimatorScale& operator=(const AnimatorScale&) = default;

	///Changes colors of the SceneryObject
	void update() override
	{
		AnimNodeDouble2D node = currentAnimState();
#pragma unroll
		for (int i = 0; i != 2; ++i)
			sceneryObject->scale[i] = node.state[i];
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
	AnimatorRotate(QString&& animAssetName, bool bLoop, QString&& sceneryObjectName) :
		AnimatorSceneryObject<AnimNodeDouble4D>(move(animAssetName), bLoop, move(sceneryObjectName))
	{
		animAsset = AssetManager::getInstance().findAnimAssetRotate(animAssetName);
	}
	AnimatorRotate(const AnimatorRotate&) = default;
	AnimatorRotate& operator=(const AnimatorRotate&) = default;

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
	AnimatorColor(QString&& animAssetName, bool bLoop, QString&& sceneryObjectName) :
		AnimatorSceneryObject<AnimNodeDouble4D>(animAssetName, bLoop, move(sceneryObjectName)) 
	{
		animAsset = AssetManager::getInstance().findAnimAssetColor(animAssetName);
	}
	AnimatorColor(const AnimatorColor&) = default;
	AnimatorColor& operator=(const AnimatorColor&) = default;

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