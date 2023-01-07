#pragma once
#include "Novel/Event/Event.h"

/// Starts a conditional region. Events between EventIf and EventEndIf will be executed only if the `condition` is satisfied
class EventIf final : public Event
{
public:
	EventIf(Scene* const parentScene) noexcept;
	/// \exception One of the Actions contains an Error or the `condition` couldn't be parsed
	EventIf(Scene* const parentScene, const QString& label, const QString& condition, std::vector<std::unique_ptr<Action>>&& actions = std::vector<std::unique_ptr<Action>>());
	EventIf(const EventIf& obj) noexcept;
	EventIf& operator=(const EventIf& obj) noexcept;
	bool operator==(const EventIf& obj) const noexcept;
	bool operator!=(const EventIf& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error One of the Actions is invalid / `condition` is invalid
	/// \return Whether an Error has occurred
	/// \todo implement this
	bool checkForErrors(bool bComprehensive = false) const override;

	virtual Event* clone() const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the EventIf's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QString condition)> onRun) noexcept;

	void acceptVisitor(EventVisitor* visitor) override;

	QString condition = "";

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventIf's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, QString condition)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};