#pragma once
#include "Global.h"
#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnim.h"

#include "Novel/Data/Visual/Animation/AnimNode.h"

class ActionVisitorCorrectAnimMoveAsset;

///Animates a SceneryObject with an Animator, which moves a SceneryObject
class ActionSceneryObjectAnimMove final : public ActionSceneryObjectAnim<AnimNodeDouble2D>
{
	friend ActionVisitorCorrectAnimMoveAsset;
public:
	ActionSceneryObjectAnimMove() = default;
	ActionSceneryObjectAnimMove(QString&& sceneryObjectName, QString&& animName, double speed, bool bLoop);
	ActionSceneryObjectAnimMove(const ActionSceneryObjectAnimMove& obj) { *this = obj; }
	ActionSceneryObjectAnimMove& operator=(const ActionSceneryObjectAnimMove& obj) = default;

	///Creates AnimatorSceneryObjectMove and adds it to the Scenery
	void run() override;

	///Updates the AnimatorSceneryObjectMove
	void update() override;

	///Removes the AnimatorSceneryObjectMove from Scenery
	void end() override;

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionSceneryObjectAnimMove; }
};

///Animates a SceneryObject with an Animator, which moves a SceneryObject
class ActionSceneryObjectAnimScale final : public ActionSceneryObjectAnim<AnimNodeDouble2D>
{
public:
	ActionSceneryObjectAnimScale() = default;
	ActionSceneryObjectAnimScale(QString&& label, QString&& sceneryObjectName,
								 QString&& animName, double speed, bool bLoop) :
		ActionSceneryObjectAnim<AnimNodeDouble2D>(move(label), move(sceneryObjectName),
		move(animName), speed, bLoop) 
			{ animAsset = AssetManager::getInstance().findAssetAnimMove(this->animName); }
	ActionSceneryObjectAnimScale(const ActionSceneryObjectAnimScale&) = default;
	ActionSceneryObjectAnimScale& operator=(const ActionSceneryObjectAnimScale&) = default;

	///Updates Animation
	void update() override;

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionSceneryObjectAnimScale; }
};


///Animates a SceneryObject with an Animator, which moves a SceneryObject
class ActionSceneryObjectAnimRotate final : public ActionSceneryObjectAnim<AnimNodeDouble1D>
{
public:
	ActionSceneryObjectAnimRotate() = default;
	ActionSceneryObjectAnimRotate(QString&& label, QString&& sceneryObjectName,
								  QString&& animName, double speed, bool bLoop) :
		ActionSceneryObjectAnim<AnimNodeDouble1D>(move(label), move(sceneryObjectName),
		move(animName), speed, bLoop)
			{ animAsset = AssetManager::getInstance().findAssetAnimMove(this->animName); }
	ActionSceneryObjectAnimRotate(const ActionSceneryObjectAnimRotate&) = default;
	ActionSceneryObjectAnimRotate& operator=(const ActionSceneryObjectAnimRotate&) = default;

	///Updates Animation
	void update() override;

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionSceneryObjectAnimRotate; }
};


///Animates a SceneryObject with an Animator, which changes color of a SceneryObject
class ActionSceneryObjectAnimColor final : public ActionSceneryObjectAnim<AnimNodeDouble4D>
{
public:
	ActionSceneryObjectAnimColor() = default;
	ActionSceneryObjectAnimColor(QString&& label, QString&& sceneryObjectName,
								 QString&& animName, double speed, bool bLoop) :
		ActionSceneryObjectAnim<AnimNodeDouble4D>(move(label), move(sceneryObjectName),
		move(animName), speed, bLoop) 
			{ animAsset = AssetManager::getInstance().findAssetAnimColor(this->animName); }
	ActionSceneryObjectAnimColor(const ActionSceneryObjectAnimColor&) = default;
	ActionSceneryObjectAnimColor& operator=(const ActionSceneryObjectAnimColor&) = default;

	///Updates Animation
	void update() override;

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionSceneryObjectAnimColor; }
};




inline ActionSceneryObjectAnimMove::ActionSceneryObjectAnimMove(QString&& sceneryObjectName, QString&& animName, double speed, bool bLoop) :
	ActionSceneryObjectAnim<AnimNodeDouble2D>(move(sceneryObjectName), move(animName), speed, bLoop)
{
	animAsset = AssetManager::getInstance().findAssetAnimMove(this->animAssetName);
}

inline ActionSceneryObjectAnimScale::ActionSceneryObjectAnimScale(QString&& sceneryObjectName, QString&& animName, double speed, bool bLoop) :
	ActionSceneryObjectAnim<AnimNodeDouble2D>(move(label), move(sceneryObjectName), move(animName), speed, bLoop)
{
	animAsset = AssetManager::getInstance().findAssetAnimScale(this->animAssetName);
}