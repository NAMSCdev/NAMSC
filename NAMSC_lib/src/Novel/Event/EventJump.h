#pragma once
#include "Novel/Event/Event.h"

class Scene;

/// Redirects the flow to an another Scene
class EventJump final : public Event
{
	/// Swap trick
	friend void swap(EventJump& first, EventJump& second) noexcept;
public:
	explicit EventJump(Scene* const parentScene) noexcept;
	/// \param label Displayed in the Editor to distinquish important Events
	/// \exception One of the Actions contains an Error or the `jumpToSceneName` points to a deleted Scene or the `condition` is not structured properly
	EventJump(Scene* const parentScene, const QString& label, const QString& jumpToSceneName = "", const QString& condition = "");
	EventJump(const EventJump& obj)              noexcept;
	EventJump(EventJump&& obj)                   noexcept;
	EventJump& operator=(EventJump obj)          noexcept;
	bool operator==(const EventJump& obj)  const noexcept;
	bool operator!=(const EventJump& obj)  const noexcept = default;

	/// \exception Error invalid Action in `actions_` / invalid `regex` / invalid `Stat` / invalid `logicalExpression`
	/// \return Whether an Error has occurred
	/// \todo implement this
	bool errorCheck(bool bComprehensive = false) const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the EventJump's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const QString& jumpToSceneName, const QString& condition)> onRun) noexcept;

	//todo: do not botch
	QString      getComponentSubTypeName() const noexcept override { return "Jump"; };
	EventSubType getComponentEventType()   const noexcept override { return EventSubType::EVENT_JUMP; };

	void acceptVisitor(EventVisitor* visitor) override;

	QString jumpToSceneName = "";

	/// A jump might contain a logical expression, so the jump happens only if the `condition` is met
	QString condition       = "";

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventJump's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Scene* const parentScene, const QString& label, const QString& jumpToSceneName, const QString& condition)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};