#pragma once
#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnim.h"

#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectRotate.h"

class ActionVisitorCorrectAssetAnimRotate;

/// Creates AnimatorSceneryObjectRotate and adds it to the Scenery, which will perform a **rotate** Animation on a SceneryObject
class ActionSceneryObjectAnimRotate final : public ActionSceneryObjectAnim<AnimNodeDouble1D>
{
	friend ActionVisitorCorrectAssetAnimRotate;
public:
	ActionSceneryObjectAnimRotate(Event* const parentEvent, Scene* const parentScene) noexcept;
	/// \exception Error Couldn't find the SceneryObject named `sceneryObjectName` or couldn't find the **rotate** AssetAnim named `assetAnimName`
	ActionSceneryObjectAnimRotate(Event* const parentEvent, Scene* const parentScene, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd);
	ActionSceneryObjectAnimRotate(const ActionSceneryObjectAnimRotate& obj) = delete;
	ActionSceneryObjectAnimRotate& operator=(const ActionSceneryObjectAnimRotate& obj) noexcept;
	bool operator==(const ActionSceneryObjectAnimRotate& obj) const noexcept;
	bool operator!=(const ActionSceneryObjectAnimRotate& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error `sceneryObject_`/`assetAnim_` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionSceneryObjectAnimRotate's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, SceneryObject* parentSceneryObject, AssetAnimRotate* assetAnimRotate, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)> onRun) noexcept;

	void setAssetAnim(const QString& assetAnimName) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the ActionSceneryObjectAnimRotate's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, SceneryObject* parentSceneryObject, AssetAnimRotate* assetAnimRotate, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)> onRun_ = nullptr;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
}; 