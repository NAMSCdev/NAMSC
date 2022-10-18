#pragma once
#include "Global.h"

#include "Novel/Data/Visual/Animation/AnimatorInterface.h"

class AnimatorSceneryObjectInterface : public AnimatorInterface
{
public:
	AnimatorSceneryObjectInterface() = default;
	AnimatorSceneryObjectInterface(QTime startTime, double speed, int timesPlayed, QString&& animAssetName, QString&& sceneryObjectName);
	AnimatorSceneryObjectInterface(const AnimatorSceneryObjectInterface& obj) { *this = obj; }
	AnimatorSceneryObjectInterface& operator=(const AnimatorSceneryObjectInterface& obj);

	///Checks if the AnimatorSceneryObjectInterface doesn't have any errors, which would halt the Novel execution
	virtual bool checkForErrors() override;

protected:
	///Ensures that all the Resources are loaded
	virtual void ensureResourcesAreLoaded();

	///Name to the Scenery Object, so it can be loaded (if needed)
	QString		   sceneryObjectName;
	///Scenery Object that will be affected by this Animator
	SceneryObject* sceneryObject;

	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream& dataStream) const override;
};




inline AnimatorInterface::AnimatorInterface(QTime startTime, double speed, int timesPlayed, QString&& animAssetName) :
	startTime(startTime), speed(speed), timesPlayed(timesPlayed), animAssetName(move(animAssetName))
{
}

inline AnimatorInterface& AnimatorInterface::operator=(const AnimatorInterface& obj)
{
	if (this == &obj) return *this;

	startTime     = obj.startTime;
	speed         = obj.speed;
	timesPlayed   = obj.timesPlayed;
	animAssetName = obj.animAssetName;

	return *this;
}