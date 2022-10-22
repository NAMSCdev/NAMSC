#pragma once
#include "Global.h"

#include "Novel/Data/Visual/Animation/AnimatorInterface.h"

class AnimatorSceneryObjectInterface : public AnimatorInterface
{
public:
	AnimatorSceneryObjectInterface() noexcept = default;
	AnimatorSceneryObjectInterface(QTime startTime, double speed, int timesPlayed, QString&& assetAnimName, QString&& sceneryObjectName) noexcept;
	AnimatorSceneryObjectInterface(const AnimatorSceneryObjectInterface& obj) noexcept { *this = obj; }
	AnimatorSceneryObjectInterface& operator=(const AnimatorSceneryObjectInterface& obj) noexcept;

	/// Checks if the AnimatorSceneryObjectInterface doesn't have any errors, which would halt the Novel execution
	virtual bool checkForErrors() noexcept override;

protected:
	/// Name to the Scenery Object, so it can be loaded (if needed)
	QString		   sceneryObjectName;
	/// Scenery Object that will be affected by this Animator
	SceneryObject* sceneryObject;

	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const override;
};




inline AnimatorSceneryObjectInterface::AnimatorSceneryObjectInterface(QTime startTime, double speed, int timesPlayed, QString&& animAssetName, QString&& sceneryObjectName) :
	AnimatorInterface(startTime, speed, timesPlayed, animAssetName), sceneryObjectName(move(sceneryObjectName))
{
}

inline AnimatorSceneryObjectInterface& AnimatorSceneryObjectInterface::operator=(const AnimatorSceneryObjectInterface& obj)
{
	if (this == &obj) return *this;

	AnimatorInterface::operator=(obj);
	sceneryObjectName = obj.sceneryObjectName;
	sceneryObject     = obj.sceneryObject;

	return *this;
}