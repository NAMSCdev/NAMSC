#pragma once
#include "Global.h"

#include "Novel/Event/Event.h"

///Waits some time
class EventWait final : public Event
{
public:
	EventWait() = default;
	EventWait(uint executionOrder, double waitTime, QString &&label) :
		Event(executionOrder, move(label)), waitTime(waitTime) {}
	EventWait(const EventWait& obj) { *this = obj; }
	EventWait& operator=(const EventWait& obj)
	{
		if (this == &obj) return *this;

		Event::operator=(obj);
		waitTime = obj.waitTime;

		return *this;
	}

	///Executes this Event's logic
	void run() override;

	///Accepts an EventVisitor
	void accept(EventVisitor* visitor) override { visitor->visitEventWait(this); }



private:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID getType() const override { return SerializationID::EventWait; }

	///How much time we will wait in milliseconds
	uint waitTime;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};