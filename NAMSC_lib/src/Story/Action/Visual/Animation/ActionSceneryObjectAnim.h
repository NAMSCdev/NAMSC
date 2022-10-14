#pragma once
#include "Global.h"

#include "Story/Action/Visual/ActionSceneryObject.h"

#include "Story/Data/Visual/Animation/AnimNode.h"

///Animates a SceneryObject with an Animator, which changes some properties of the SceneryObject over time
template<typename AnimNode>
class ActionSceneryObjectAnim : public ActionSceneryObject
{
public:
	ActionSceneryObjectAnim() = default;
	ActionSceneryObjectAnim(Event *parent, unsigned actionID, QString &&label, QString &&sceneryObjectName, 
							QString &&animName, double speed, bool bLoop) :
		ActionSceneryObject(parent, actionID, move(label), move(sceneryObjectName)), 
		animName(move(animName)), speed(speed), bLoop(bLoop) {}
	ActionSceneryObjectAnim(const ActionSceneryObjectAnim& asset)				= default;
	ActionSceneryObjectAnim& operator=(const ActionSceneryObjectAnim& asset)	= default;

	///Executes Action's logic
	void run() override;
	
	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override	{ visitor->visitActionSceneryObjectAnim(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, double speed, bool bLoop, QVector<AnimNode> *animNodes);

protected:
	///Name of the AnimAsset, so it can be loaded (if needed) and played
	QString animName;
	///AnimAsset containing all the AnimNodes
	AnimAsset<AnimNode>* animAsset;

	///How fast the animation will be played
	double speed = 1.0;

	///Whether the animation is looped
	bool bLoop = false;

private:
	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;

	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};
