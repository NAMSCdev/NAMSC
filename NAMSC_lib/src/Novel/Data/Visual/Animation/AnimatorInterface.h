#pragma once
#include "Global.h"

#include "Novel/Data/NovelFlowInterface.h"

#include "Novel/Data/Visual/Animation/AnimNode.h"
#include "Novel/Data/Visual/Scenery/SceneryObject.h"

#include "Novel/Data/Asset/AssetManager.h"
#include "Novel/Data/Asset/Type/AssetAnim.h"

/// More abstract interface that allows to call start() and update() regardless of the template arguments
class AnimatorInterface : public NovelFlowInterface
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream& dataStream, AnimatorInterface&);
	friend QDataStream& operator<<(QDataStream& dataStream, const AnimatorInterface&);
public:
	AnimatorInterface() = default;
	AnimatorInterface(QTime startTime, double speed, int timesPlayed, QString&& animAssetName);
	AnimatorInterface(const AnimatorInterface& obj) { *this = obj; }
	AnimatorInterface& operator=(const AnimatorInterface& obj);
	
	/// The destructor needs to be virtual, so the proper destructor will always be called when destroying an AnimatorInterface pointer
	virtual ~AnimatorInterface() = default;

	//Starts the Animation
	virtual void run() override { ensureResourcesAreLoaded(); }

	/// An Animator might need to access the data, that is a part of the Save
	/// Must be called after the Save is loaded
	virtual void syncWithSave() override {}

	/// Checks if the Animator doesn't have any errors, which would halt the Novel execution
	virtual bool checkForErrors() override {}

	/// Cleanup of the Animator
	virtual void end() override {}

protected:
	/// Ensures that the AnimAsset has its resources loaded
	virtual void ensureResourcesAreLoaded() = 0;

	/// Beginning of the Animation, so we can calculate the elapsed time
	QTime startTime;

	/// How fast the Animation will be played
	double speed = 1.0;

	/// How many times it will be played
	/// Can be set to -1, so it will be looped infinitely
	int	timesPlayed = 1;

	/// Name of the AssetAnim, so they can be loaded when needed
	QString animAssetName;

	//---SERIALIZATION---
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const;
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