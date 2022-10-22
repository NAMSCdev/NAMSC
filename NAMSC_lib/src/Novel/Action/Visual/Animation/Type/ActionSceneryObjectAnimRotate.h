#pragma once
#include "Global.h"

#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnim.h"
#include "Novel/Data/Visual/Animation/AnimNode.h"

class ActionVisitorCorrectAssetAnimRotate;

/// Uses an Animator to perform a **rotate** Animation on a SceneryObject 
class ActionSceneryObjectAnimRotate final : public ActionSceneryObjectAnim<AnimNodeDouble1D>
{
	friend ActionVisitorCorrectAssetAnimRotate;
public:
	ActionSceneryObjectAnimRotate() noexcept = default;
	ActionSceneryObjectAnimRotate(QString&& sceneryObjectName, QString&& assetAnimName, double speed, bool bLoop);
	ActionSceneryObjectAnimRotate(const ActionSceneryObjectAnimRotate& obj) noexcept { *this = obj; }
	ActionSceneryObjectAnimRotate& operator=(const ActionSceneryObjectAnimRotate& obj) noexcept;

	/// Creates AnimatorSceneryObjectRotate and adds it to the Scenery
	void run() override;

	/// Removes the AnimatorSceneryObjectRotate from the Scenery
	void end() override;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionSceneryObjectAnimRotate; }
};




inline ActionSceneryObjectAnimRotate::ActionSceneryObjectAnimRotate(QString&& sceneryObjectName, QString&& assetAnimName, double speed, bool bLoop) :
	ActionSceneryObjectAnim<AnimNodeDouble1D>(move(sceneryObjectName), move(assetAnimName), speed, bLoop)
{
	assetAnim = AssetManager::getInstance().findAssetAnimRotate(this->assetAnimName);
}

inline ActionSceneryObjectAnimRotate& ActionSceneryObjectAnimRotate::operator=(const ActionSceneryObjectAnimRotate& obj)
{
	if (this == &obj) return *this;

	ActionSceneryObjectAnim<AnimNodeDouble1D>::operator=(obj);

	return *this;
}