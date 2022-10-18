#pragma once
#include "Global.h"

#include "Novel/Action/Visual/ActionSceneryObject.h"

#include "Novel/Data/Visual/Animation/AnimatorInterface.h"

#include "Novel/Data/Asset/Type/AssetAnim.h"

///Animates a SceneryObject with an Animator, which changes some properties of the SceneryObject over time
///@todo [optional]Animations should be able to be queued, so instead of changing one animation, there should be a more robust struct for holding data about it and every SceneryObject should store currently played LIST of animations 
//Maybe list of AnimAssets with offsets?
template<typename AnimNode>
class ActionSceneryObjectAnim : public ActionSceneryObject
{
public:
	ActionSceneryObjectAnim() = default;
	ActionSceneryObjectAnim(QString&& sceneryObjectName, QString&& animName, double speed, bool bLoop) :
		ActionSceneryObject(move(sceneryObjectName)), animName(move(animName)), speed(speed), bLoop(bLoop) {}
	ActionSceneryObjectAnim(const ActionSceneryObjectAnim& obj) { *this = obj; }
	//todo: can this be moved outside the class without breaking InteliSense?
	ActionSceneryObjectAnim<AnimNode>& operator=(const ActionSceneryObjectAnim<AnimNode>& obj)
	{
		if (this == &obj)
			return *this;

		ActionSceneryObject::operator=(obj);
		animAssetName = obj.animAssetName;
		animAsset     = obj.animAsset;
		speed         = obj.speed;
		bLoop         = obj.bLoop;

		return (*this)
	}

	///Executes this Action's logic
	void run() override;

	///Accepts an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionSceneryObjectAnimMove(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject* sceneryObject, double speed, bool bLoop, QVector<AnimNode>* animNodes);

protected:
	///Name of the AnimAsset, so it can be loaded (if needed) and played
	QString				 animAssetName;
	///AnimAsset containing all the AnimNodes
	AssetAnim<AnimNode>* animAsset;

	///Animator's `update()` performs the animation on the SceneryObject
	AnimatorSceneryObjectInterface animator;

	///How fast the animation will be played
	double speed = 1.0;

	///Whether the animation is looped
	bool bLoop = false;

private:
	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;

	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};