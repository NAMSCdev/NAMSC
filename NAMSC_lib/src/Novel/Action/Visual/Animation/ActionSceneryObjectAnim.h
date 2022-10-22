#pragma once
#include "Global.h"

#include "Novel/Action/Visual/ActionSceneryObject.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"
#include "Novel/Data/Asset/Type/AssetAnim.h"

/// Animates a SceneryObject with an Animator, which changes some properties of the SceneryObject over time
/// @todo [optional] Animations should be able to be queued, so instead of changing one Animation, there should be a more robust struct for holding data about it and every SceneryObject should store currently played LIST of Animations 
//Maybe list of AnimAssets with offsets?
template<typename AnimNode>
class ActionSceneryObjectAnim : public ActionSceneryObject
{
public:
	ActionSceneryObjectAnim() noexcept = default;
	ActionSceneryObjectAnim(QString&& sceneryObjectName, QString&& assetAnimName, double speed, bool bLoop);
	ActionSceneryObjectAnim(const ActionSceneryObjectAnim& obj) noexcept { *this = obj; }
	ActionSceneryObjectAnim<AnimNode>& operator=(const ActionSceneryObjectAnim<AnimNode>& obj) noexcept;

signals:
	/// A Qt signal emitted after the ActionSceneryObjectAnim's `void run()` allowing for data read
	/// \param sceneryObject The SceneryObject that is being animated
	/// \param animNodes List of states of the Animation at a given time
	/// \param speed Available effects for the appearing Animation
	/// \param bLoop Whether the Animation is looped
	void onRun(const SceneryObject* sceneryObject, const QVector<AnimNode>* animNodes, double speed, bool bLoop) const;

protected:
	/// Name of the AnimAsset, so they can be loaded when needed
	QString				 assetAnimName;
	/// AnimAsset containing all the AnimNodes - states of the Animation at a given time
	AssetAnim<AnimNode>* assetAnim;

	/// How fast the Animation will be played
	double speed = 1.0;

	/// Whether the Animation is looped
	bool bLoop = false;

private:
	//---SERIALIZATION---
	/// Loading an object from a binary file/
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;

	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};




template <class AnimNode>
inline ActionSceneryObjectAnim<AnimNode>::ActionSceneryObjectAnim(QString&& sceneryObjectName, QString&& assetAnimName, double speed, bool bLoop) :
	ActionSceneryObject(move(sceneryObjectName)), assetAnimName(move(assetAnimName)), speed(speed), bLoop(bLoop)
{
}

template <class AnimNode> 
inline ActionSceneryObjectAnim<AnimNode>& ActionSceneryObjectAnim<AnimNode>::operator=(const ActionSceneryObjectAnim<AnimNode>&obj)
{
	if (this == &obj)
		return *this;

	ActionSceneryObject::operator=(obj);
	assetAnimName = obj.assetAnimName;
	assetAnim     = obj.assetAnim;
	speed         = obj.speed;
	bLoop         = obj.bLoop;

	return (*this)
}