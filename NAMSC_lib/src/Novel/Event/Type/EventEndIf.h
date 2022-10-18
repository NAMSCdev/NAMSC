#pragma once
#include "Global.h"

#include "Novel/Event/Event.h"

///Ends an EventIf previous instance
///[optional todo] make checks and prevent placing umatched EndIf in editor
class EventEndIf final : public Event
{
public:
	EventEndIf() = default;
	EventEndIf(uint executionOrder, QString&& label) :
		Event(executionOrder, move(label)) { }
	EventEndIf(const EventEndIf& obj) { *this = obj; }
	EventEndIf& operator=(const EventEndIf& obj);
	///Executes this Event's logic
	void run() override;

	///Accepts an EventVisitor
	void accept(EventVisitor* visitor) override	{ visitor->visitEventEndIf(this); }

private:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID	getType() const override	{ return SerializationID::EventEndIf; }

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};

inline EventEndIf& EventEndIf::operator=(const EventEndIf& obj)
{
	if (this == &obj) return *this;

	Event::operator=(obj);

	return *this;
}