#pragma once
#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnim.h"

#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectFade.h"

/// Creates AnimatorSceneryObjectFade and adds it to the Scenery, which will perform an **appear** or **disappear** Animation on a SceneryObject 
/// \todo create special Animator for it 
class ActionSceneryObjectAnimFade : public ActionSceneryObjectAnim<AnimNodeDouble1D>
{
public:
	ActionSceneryObjectAnimFade(Event* const parentEvent, Scene* const parentScene) noexcept;
	/// \exception Error Couldn't find the SceneryObject named `sceneryObjectName`
	ActionSceneryObjectAnimFade(Event* const parentEvent, Scene* const parentScene, const QString& sceneryObjectName, uint priority, uint startDelay, bool bStopAnimationAtEventEnd, uint duration, bool bAppear);
	ActionSceneryObjectAnimFade(const ActionSceneryObjectAnimFade& obj) = delete;
	ActionSceneryObjectAnimFade& operator=(const ActionSceneryObjectAnimFade& obj) noexcept;
	bool operator==(const ActionSceneryObjectAnimFade& obj) const noexcept;
	bool operator!=(const ActionSceneryObjectAnimFade& obj) const       = default; //{ return !(*this == obj); }

	/// \exception Error `sceneryObject_` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the AnimatorSceneryObjectVisibility's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, SceneryObject* sceneryObject, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd, uint duration, bool bAppear)> onRun) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

	/// In milliseconds
	uint duration = 100;

	/// Whether to appear or disappear
	bool bAppear  = true;

protected:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the ActionSceneryObjectAnimFade's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, SceneryObject* sceneryObject, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd, uint duration, bool bAppear)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};