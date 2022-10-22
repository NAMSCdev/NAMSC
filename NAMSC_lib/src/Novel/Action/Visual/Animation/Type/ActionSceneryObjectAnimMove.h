#pragma once
#include "Global.h"

#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnim.h"
#include "Novel/Data/Visual/Animation/AnimNode.h"

class ActionVisitorCorrectAssetAnimMove;

/// Uses an Animator to perform a **move** Animation on a SceneryObject 
class ActionSceneryObjectAnimMove final : public ActionSceneryObjectAnim<AnimNodeDouble2D>
{
	friend ActionVisitorCorrectAssetAnimMove;
public:
	ActionSceneryObjectAnimMove() noexcept = default;
	ActionSceneryObjectAnimMove(QString&& sceneryObjectName, QString&& assetAnimName, double speed, bool bLoop);
	ActionSceneryObjectAnimMove(const ActionSceneryObjectAnimMove& obj) noexcept { *this = obj; }
	ActionSceneryObjectAnimMove& operator=(const ActionSceneryObjectAnimMove& obj) noexcept;

	/// Creates AnimatorSceneryObjectMove and adds it to the Scenery
	void run() override;

	/// Removes the AnimatorSceneryObjectMove from the Scenery
	void end() override;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionSceneryObjectAnimMove; }
};




inline ActionSceneryObjectAnimMove::ActionSceneryObjectAnimMove(QString&& sceneryObjectName, QString&& assetAnimName, double speed, bool bLoop) :
	ActionSceneryObjectAnim<AnimNodeDouble2D>(move(sceneryObjectName), move(assetAnimName), speed, bLoop)
{
	assetAnim = AssetManager::getInstance().findAssetAnimMove(this->assetAnimName);
}

inline ActionSceneryObjectAnimMove& ActionSceneryObjectAnimMove::operator=(const ActionSceneryObjectAnimMove& obj)
{
	if (this == &obj) return *this;

	ActionSceneryObjectAnim<AnimNodeDouble2D>::operator=(obj);

	return *this;
}