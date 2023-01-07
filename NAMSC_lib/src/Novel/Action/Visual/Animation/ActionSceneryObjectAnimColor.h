#pragma once
#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnim.h"

#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectColor.h"
#include "Novel/Data/Save/NovelState.h"

/// Creates AnimatorSceneryObjectColor and adds it to the Scenery, which will perform a **color** Animation on a SceneryObject
class ActionSceneryObjectAnimColor final : public ActionSceneryObjectAnim<AnimNodeDouble4D>
{
	friend class ActionVisitorCorrectAssetAnimColor;
public:
	ActionSceneryObjectAnimColor(Event* const parentEvent) noexcept;
	/// \exception Error Couldn't find the SceneryObject named `sceneryObjectName` or couldn't find/load the **color** AssetAnim named `assetAnimName`
	ActionSceneryObjectAnimColor(Event* const parentEvent, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd);
	ActionSceneryObjectAnimColor(const ActionSceneryObjectAnimColor& obj) noexcept;
	ActionSceneryObjectAnimColor& operator=(const ActionSceneryObjectAnimColor& obj) noexcept;
	bool operator==(const ActionSceneryObjectAnimColor& obj) const noexcept;
	bool operator!=(const ActionSceneryObjectAnimColor& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error `sceneryObject_`/`assetAnim_` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const override;

	Action* clone() const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionSceneryObjectAnimColor's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, SceneryObject* parentSceneryObject, AssetAnimColor* assetAnimColor, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)> onRun) noexcept;

	void setAssetAnim(const QString& assetAnimName) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the ActionSceneryObjectAnimColor's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, SceneryObject* parentSceneryObject, AssetAnimColor* assetAnimColor, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};