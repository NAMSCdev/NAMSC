#pragma once
#include "Novel/Event/Event.h"

/// Waits some time
class EventWait final : public Event
{
public:
	EventWait(Scene* const parentScene) noexcept;
	/// \exception One of the Actions contains an Error
	EventWait(Scene* const parentScene, const QString& label, uint waitTime);
	/// \exception One of the Actions contains an Error
	EventWait(Scene* const parentScene, const QString& label, uint waitTime, std::vector<std::unique_ptr<Action>>&& actions);
	EventWait(const EventWait& obj)             = delete;
	EventWait& operator=(const EventWait& obj) noexcept;
	bool operator==(const EventWait& obj) const noexcept;
	bool operator!=(const EventWait& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error invalid Action in `actions_`
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the EventWait's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, uint waitTime)> onRun) noexcept;

	void acceptVisitor(EventVisitor* visitor) override;

	/// In milliseconds
	uint waitTime = 1000;

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventWait's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, uint waitTime)> onRun_ = nullptr;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};