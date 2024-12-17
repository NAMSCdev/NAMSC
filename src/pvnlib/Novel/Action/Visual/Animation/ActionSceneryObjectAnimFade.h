#pragma once
#include "pvnLib/Novel/Action/Visual/Animation/ActionSceneryObjectAnim.h"

#include "pvnLib/Novel/Data/Visual/Animation/AnimatorSceneryObjectFade.h"

/// Creates AnimatorSceneryObjectFade and adds it to the Scenery, which will perform an **appear** or **disappear** Animation on a SceneryObject 
/// \todo create special Animator for it 
class ActionSceneryObjectAnimFade : public ActionSceneryObjectAnim<AnimNodeDouble1D>
{
	/// Swap trick
	friend void swap(ActionSceneryObjectAnimFade& first, ActionSceneryObjectAnimFade& second) noexcept;
public:
	explicit ActionSceneryObjectAnimFade(Event* const parentEvent) noexcept;
	/// \param sceneryObject Copies the SceneryObject pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization 
	/// \param assetAnim Copies the AssetAnim pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization 
	/// \param priority Animations can be queued, this is the priority in the queue (lower number equals higher priority)
	/// \param startDelay In milliseconds
	/// \param speed Animation speed multiplier
	/// \param Remember to copy the description to the constructor parameter description as well, if it changes
	/// \param timesPlayed `-1` means infinite times
	/// \param duration In milliseconds
	/// \param bAppear Whether to appear or disappear
	/// \exception Error Couldn't find the SceneryObject named `sceneryObjectName`
	ActionSceneryObjectAnimFade(Event* const parentEvent, const QString& sceneryObjectName, uint priority = 0, uint startDelay = 0, bool bFinishAnimationAtEventEnd = false, uint duration = 100, bool bAppear = true, SceneryObject* sceneryObject = nullptr, AssetAnim<AnimNodeDouble1D>* assetAnim = nullptr);
	ActionSceneryObjectAnimFade(const ActionSceneryObjectAnimFade& obj)     noexcept;
	ActionSceneryObjectAnimFade(ActionSceneryObjectAnimFade&& obj)          noexcept;
	ActionSceneryObjectAnimFade& operator=(ActionSceneryObjectAnimFade obj) noexcept;
	bool operator==(const ActionSceneryObjectAnimFade& obj) const           noexcept;
	bool operator!=(const ActionSceneryObjectAnimFade& obj) const           noexcept = default;

	/// \exception Error `sceneryObject_` is invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the AnimatorSceneryObjectVisibility's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Event* const parentEvent, const SceneryObject* const sceneryObject, const uint& priority, const uint& startDelay, const bool& bFinishAnimationAtEventEnd, uint duration, bool bAppear)> onRun) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

	/// Inherited vian ActionSceneryObjectAnim, but not needed at all, as this type of Animation is special and does not need any AssetAnim
	void setAssetAnim(const QString& assetAnimName, AssetAnim<AnimNodeDouble1D>* assetAnim = nullptr) noexcept override;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// In milliseconds
	uint duration = 100;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Whether to appear or disappear
	bool bAppear  = true;

protected:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the ActionSceneryObjectAnimFade's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Event* const parentEvent, const SceneryObject* const sceneryObject, const uint& priority, const uint& startDelay, const bool& bFinishAnimationAtEventEnd, uint duration, bool bAppear)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};