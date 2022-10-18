#pragma once
#include "Global.h"

#include "Novel/Event/Event.h"

///Ends an EventIf previous instance
///[optional todo] make checks and prevent placing umatched EndIf in editor
class EventIf final : public Event
{
public:
	EventIf() = default;
	EventIf(uint executionOrder, QString&& label, QString &&condition) :
		Event(executionOrder, move(label)), condition(move(condition))	{ }
	EventIf(const EventIf& obj) { *this = obj; }
	EventIf& operator=(const EventIf& obj);

	///Executes this Event's logic
	void run() override		{}

	///AcceptsEventVisitor
	void accept(EventVisitor* visitor) override	{ visitor->visitEventIf(this); }

private:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID	getType() const override	{ return SerializationID::EventIf; }

	///A jump might contain a logical expression, so the jump happens only if the [condition] is met
	QString condition;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};

inline EventIf& EventIf::operator=(const EventIf& obj)
{
	if (this == &obj) return *this;

	Event::operator=(obj);
	condition = obj.condition;

	return *this;
}