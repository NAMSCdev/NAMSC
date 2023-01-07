#pragma once
#include "Novel/Event/Event.h"

/// Ends an EventIf previous instance
class EventEndIf final : public Event
{
public:
	EventEndIf(Scene* const parentScene) noexcept;
	/// \exception One of the Actions contains an Error or there is no matching EventIf or its index is after this EventEndIf
	EventEndIf(Scene* const parentScene, const QString& label, Event* const partner, std::vector<std::unique_ptr<Action>>&& actions = std::vector<std::unique_ptr<Action>>());
	EventEndIf(const EventEndIf& obj) noexcept;
	EventEndIf& operator=(const EventEndIf& obj) noexcept;
	bool operator==(const EventEndIf& obj) const noexcept;
	bool operator!=(const EventEndIf& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error Invalid Action in `actions_` / invalid `partner_`
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const override;

	virtual Event* clone() const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the EventEndIf's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, Event* partner)> onRun) noexcept;

	void acceptVisitor(EventVisitor* visitor) override;

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventEndIf's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, Event* partner)> onRun_ = nullptr;

	Event* partner_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};