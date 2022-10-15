#pragma once
#include "Global.h"
#include "Story/Action/Visual/ActionSceneryObject.h"

#include "Story/Action/Visual/Animation/ActionSceneryObjectAnim.h"

///Animates a SceneryObject with an Animator, which moves a SceneryObject
class ActionSceneryObjectAnimMove final : public ActionSceneryObjectAnim<AnimNodeDouble2D>
{
public:
	ActionSceneryObjectAnimMove() = default;
	ActionSceneryObjectAnimMove(unsigned actionID, QString&& label, QString&& sceneryObjectName,
								QString&& animName, double speed, bool bLoop) :
		ActionSceneryObjectAnim<AnimNodeDouble2D>(parent, actionID, move(label), move(sceneryObjectName),
		move(animName), speed, bLoop)
			{ animAsset = AssetManager::getInstance().findAnimAssetMove(this->animName); }
	ActionSceneryObjectAnimMove(const ActionSceneryObjectAnimMove&) = default;
	ActionSceneryObjectAnimMove& operator=(const ActionSceneryObjectAnimMove&) = default;

	///Updates Animation
	void update() override;

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionSceneryObjectAnimMove; }
};

///Animates a SceneryObject with an Animator, which moves a SceneryObject
class ActionSceneryObjectAnimScale final : public ActionSceneryObjectAnim<AnimNodeDouble2D>
{
public:
	ActionSceneryObjectAnimScale() = default;
	ActionSceneryObjectAnimScale(unsigned actionID, QString&& label, QString&& sceneryObjectName,
								 QString&& animName, double speed, bool bLoop) :
		ActionSceneryObjectAnim<AnimNodeDouble2D>(parent, actionID, move(label), move(sceneryObjectName),
		move(animName), speed, bLoop) 
			{ animAsset = AssetManager::getInstance().findAnimAssetMove(this->animName); }
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
	ActionSceneryObjectAnimRotate(unsigned actionID, QString&& label, QString&& sceneryObjectName,
								  QString&& animName, double speed, bool bLoop) :
		ActionSceneryObjectAnim<AnimNodeDouble1D>(parent, actionID, move(label), move(sceneryObjectName),
		move(animName), speed, bLoop)
			{ animAsset = AssetManager::getInstance().findAnimAssetMove(this->animName); }
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
	ActionSceneryObjectAnimColor(unsigned actionID, QString&& label, QString&& sceneryObjectName,
								 QString&& animName, double speed, bool bLoop) :
		ActionSceneryObjectAnim<AnimNodeDouble4D>(parent, actionID, move(label), move(sceneryObjectName),
		move(animName), speed, bLoop) 
			{ animAsset = AssetManager::getInstance().findAnimAssetColor(this->animName); }
	ActionSceneryObjectAnimColor(const ActionSceneryObjectAnimColor&) = default;
	ActionSceneryObjectAnimColor& operator=(const ActionSceneryObjectAnimColor&) = default;

	///Updates Animation
	void update() override;

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionSceneryObjectAnimColor; }
};
