#pragma once
#include "Global.h"
#include "Story\Action\Visual\ActionSceneryObject.h"

///Animates a SceneryObject with an Animator, which changes some properties of the SceneryObject over time
class ActionSceneryObjectAnim final : public ActionSceneryObject
{
public:
	ActionSceneryObjectAnim() = default;
	ActionSceneryObjectAnim(Event *parent, unsigned actionID, QString &&label, QString &&sceneryObjectName, 
							QString &&animAssetName, double duration) :
		ActionSceneryObject(parent, actionID, move(label), move(sceneryObjectName)), 
		animAssetName(move(animAssetName)), duration(duration) {}
	ActionSceneryObjectAnim(const ActionSceneryObjectAnim& asset)				= default;
	ActionSceneryObjectAnim& operator=(const ActionSceneryObjectAnim& asset)	= default;

	///Executes Action's logic
	void run() override;
	
	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override	{ visitor->visitActionSceneryObjectAnim(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, QString animName, double duration);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override		{ return SerializationID::ActionSceneryObjectAnim; }

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;

	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};
