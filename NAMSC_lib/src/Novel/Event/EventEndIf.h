#pragma once
#include "Novel/Event/Event.h"

/// Ends an EventIf previous instance
class EventEndIf final : public Event
{
	/// Swap trick
	friend void swap(EventEndIf& first, EventEndIf& second) noexcept;
public:
	explicit EventEndIf(Scene* const parentScene) noexcept;
	/// \param label Displayed in the Editor to distinquish important Events
	/// \exception One of the Actions contains an Error or there is no matching EventIf or its index is after this EventEndIf
	EventEndIf(Scene* const parentScene, const QString& label, EventIf* const partner = nullptr, std::vector<std::unique_ptr<Action>>&& actions = std::move(std::vector<std::unique_ptr<Action>>()));
	EventEndIf(const EventEndIf& obj)             noexcept = delete;
	EventEndIf(EventEndIf&& obj)                  noexcept;
	EventEndIf& operator=(const EventEndIf& obj)  noexcept = delete;
	bool operator==(const EventEndIf& obj) const  noexcept = delete;
	bool operator!=(const EventEndIf& obj) const  noexcept = delete;

	/// \exception Error Invalid Action in `actions_` / invalid `partner_`
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the EventEndIf's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const EventIf* const partner)> onRun) noexcept;

	void acceptVisitor(EventVisitor* visitor) override;

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventEndIf's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Scene* const parentScene, const QString& label, const EventIf* const partner)> onRun_ = nullptr;
	
	EventIf* partner_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};