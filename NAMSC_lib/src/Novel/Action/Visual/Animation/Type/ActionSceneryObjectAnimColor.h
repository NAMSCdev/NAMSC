#pragma once
#include "Global.h"

#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnim.h"
#include "Novel/Data/Visual/Animation/AnimNode.h"

class ActionVisitorCorrectAssetAnimColor;

/// Uses an Animator to perform a **color** Animation on a SceneryObject 
class ActionSceneryObjectAnimColor final : public ActionSceneryObjectAnim<AnimNodeDouble4D>
{
	friend ActionVisitorCorrectAssetAnimColor;
public:
	ActionSceneryObjectAnimColor() noexcept = default;
	ActionSceneryObjectAnimColor(QString&& sceneryObjectName, QString&& assetAnimName, double speed, bool bLoop);
	ActionSceneryObjectAnimColor(const ActionSceneryObjectAnimColor& obj) noexcept { *this = obj; }
	ActionSceneryObjectAnimColor& operator=(const ActionSceneryObjectAnimColor& obj) noexcept;

	/// Creates AnimatorSceneryObjectColor and adds it to the Scenery
	void run() override;

	/// Removes the AnimatorSceneryObjectColor from Scenery
	void end() override;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionSceneryObjectAnimColor; }
};




inline ActionSceneryObjectAnimColor::ActionSceneryObjectAnimColor(QString&& sceneryObjectName, QString&& assetAnimName, double speed, bool bLoop) :
	ActionSceneryObjectAnim<AnimNodeDouble4D>(move(sceneryObjectName), move(assetAnimName), speed, bLoop)
{
	assetAnim = AssetManager::getInstance().findAssetAnimColor(this->assetAnimName);
}

inline ActionSceneryObjectAnimColor& ActionSceneryObjectAnimColor::operator=(const ActionSceneryObjectAnimColor& obj)
{
	if (this == &obj) return *this;

	ActionSceneryObjectAnim<AnimNodeDouble4D>::operator=(obj);

	return *this;
}