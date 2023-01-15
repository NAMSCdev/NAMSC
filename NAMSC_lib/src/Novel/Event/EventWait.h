#pragma once
#include "Novel/Event/Event.h"

/// Waits some time
class EventWait final : public Event
{
	/// Swap trick
	friend void swap(EventWait& first, EventWait& second) noexcept;
public:
	explicit EventWait(Scene* const parentScene) noexcept;
	/// \param label Displayed in the Editor to distinquish important Events
	/// \param waitTime In milliseconds
	/// \exception One of the Actions contains an Error
	EventWait(Scene* const parentScene, const QString& label, uint waitTime = 1000, std::vector<std::unique_ptr<Action>>&& actions = std::move(std::vector<std::unique_ptr<Action>>()));
	EventWait(const EventWait& obj)             noexcept = delete;
	EventWait(EventWait&& obj)                  noexcept;
	EventWait& operator=(const EventWait& obj)  noexcept = delete;
	bool operator==(const EventWait& obj) const noexcept = delete;
	bool operator!=(const EventWait& obj) const noexcept = delete;

	/// \exception Error invalid Action in `actions_`
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the EventWait's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const uint& waitTime)> onRun) noexcept;

	void acceptVisitor(EventVisitor* visitor) override;

	/// In milliseconds
	uint waitTime = 1000;

    // methods for events tree
    virtual QString getSubTypeName() { return "Wait"; }
    virtual EventSubType getEventType() { return EventSubType::EVENT_WAIT; }

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventWait's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Scene* const parentScene, const QString& label, const uint& waitTime)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};