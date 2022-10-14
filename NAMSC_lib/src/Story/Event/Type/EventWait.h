#pragma once
#include "Global.h"

#include "Story/Event/Event.h"

///Waits some time
class EventWait final : public Event
{
public:
	EventWait(unsigned sceneID, unsigned executionOrder, double waitTime = 0.35, QString &&label = "") :
		Event(sceneID, executionOrder, move(label)), waitTime(waitTime) {}

	///Executes Event's logic
	void		run		() override;

	///Accepts EventVisitor
	void		accept	(EventVisitor* visitor) override	{ visitor->visitEventWait(this); }

protected:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID		getType	() const override			{ return SerializationID::EventWait; }

	///How much time we will wait in seconds
	double		waitTime			= 0.35;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override
	{
		Event::serializableLoad(dataStream);

		dataStream >> waitTime;
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override
	{
		Event::serializableSave(dataStream);

		dataStream << waitTime;
	}
};