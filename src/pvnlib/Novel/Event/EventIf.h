#pragma once
#include "pvnLib/Novel/Event/Event.h"

/// Starts a conditional region. Events between EventIf and EventEndIf will be executed only if the `condition` is satisfied
class EventIf final : public Event
{
	/// Swap trick
	friend void swap(EventIf& first, EventIf& second) noexcept;
public:
	explicit EventIf(Scene* const parentScene) noexcept;
	/// \param label Displayed in the Editor to distinquish important Events
	/// \exception One of the Actions contains an Error or the `condition` couldn't be parsed
	EventIf(Scene* const parentScene, const QString& label, const QString& condition = "");
	EventIf(const EventIf& obj)                noexcept;
	EventIf(EventIf&& obj)                     noexcept;
	EventIf& operator=(EventIf obj)            noexcept;
	bool operator==(const EventIf& obj) const  noexcept;
	bool operator!=(const EventIf& obj) const  noexcept = default;

	/// \exception Error One of the Actions is invalid / `condition` is invalid
	/// \return Whether an Error has occurred
	/// \todo implement this
	bool errorCheck(bool bComprehensive = false) const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the EventIf's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const QString& condition)> onRun) noexcept;

	void acceptVisitor(EventVisitor* visitor) override;

	QString condition = "";

	//todo: do not botch
    QString getComponentSubTypeName()    const noexcept override { return "If"; }
    EventSubType getComponentEventType() const noexcept override { return EventSubType::EVENT_IF; }

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventIf's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Scene* const parentScene, const QString& label, const QString& condition)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};