#pragma once
#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnim.h"

#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectMove.h"

class ActionVisitorCorrectAssetAnimMove;

/// Creates AnimatorSceneryObjectMove and adds it to the Scenery, which will perform a **move** Animation on a SceneryObject
class ActionSceneryObjectAnimMove final : public ActionSceneryObjectAnim<AnimNodeDouble2D>
{
	friend ActionVisitorCorrectAssetAnimMove;
public:
	ActionSceneryObjectAnimMove(Event* const parentEvent, Scene* const parentScene) noexcept;
	/// \exception Error Couldn't find the SceneryObject named `sceneryObjectName` or couldn't find the **move** AssetAnim named `assetAnimName`
	ActionSceneryObjectAnimMove(Event* const parentEvent, Scene* const parentScene, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd);
	ActionSceneryObjectAnimMove(const ActionSceneryObjectAnimMove& obj) = delete;
	ActionSceneryObjectAnimMove& operator=(const ActionSceneryObjectAnimMove& obj) noexcept;
	bool operator==(const ActionSceneryObjectAnimMove& obj) const noexcept;
	bool operator!=(const ActionSceneryObjectAnimMove& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error `sceneryObject_`/`assetAnim_` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionSceneryObjectAnimMove's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, SceneryObject* parentSceneryObject, AssetAnimMove* assetAnimMove, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)> onRun) noexcept;

	void setAssetAnim(const QString& assetAnimName) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the ActionSceneryObjectAnimMove's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, SceneryObject* parentSceneryObject, AssetAnimMove* assetAnimMove, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};