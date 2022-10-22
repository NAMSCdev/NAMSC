#pragma once
#include "Global.h"

#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnim.h"
#include "Novel/Data/Visual/Animation/AnimNode.h"

class ActionVisitorCorrectAssetAnimScale;

/// Uses an Animator to perform a **scale** Animation on a SceneryObject 
class ActionSceneryObjectAnimScale final : public ActionSceneryObjectAnim<AnimNodeDouble2D>
{
	friend ActionVisitorCorrectAssetAnimScale;
public:
	ActionSceneryObjectAnimScale() noexcept = default;
	ActionSceneryObjectAnimScale(QString&& sceneryObjectName, QString&& assetAnimName, double speed, bool bLoop);
	ActionSceneryObjectAnimScale(const ActionSceneryObjectAnimScale& obj) noexcept { *this = obj; }
	ActionSceneryObjectAnimScale& operator=(const ActionSceneryObjectAnimScale&) noexcept;

	/// Creates AnimatorSceneryObjectScale and adds it to the Scenery
	void run() override;

	/// Removes the AnimatorSceneryObjectScale from the Scenery
	void end() override;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionSceneryObjectAnimScale; }
};




inline ActionSceneryObjectAnimScale::ActionSceneryObjectAnimScale(QString&& sceneryObjectName, QString&& assetAnimName, double speed, bool bLoop) :
	ActionSceneryObjectAnim<AnimNodeDouble2D>(move(sceneryObjectName), move(assetAnimName), speed, bLoop)
{
	assetAnim = AssetManager::getInstance().findAssetAnimScale(this->assetAnimName);
}

inline ActionSceneryObjectAnimScale& ActionSceneryObjectAnimScale::operator=(const ActionSceneryObjectAnimScale& obj)
{
	if (this == &obj) return *this;

	ActionSceneryObjectAnim<AnimNodeDouble2D>::operator=(obj);

	return *this;
}