#pragma once
#include "Global.h"

#include "Story/Event/Event.h"

///Ends an EventIf previous instance
///[optional todo] make checks and prevent placing umatched EndIf in editor
class EventEndIf final : public Event
{
public:
	EventEndIf(unsigned sceneID, unsigned executionOrder, QString &&label = "") :
		Event(sceneID, executionOrder, move(label)) {}

	///Executes Event's logic
	void		run		() override;

	///Accepts EventVisitor
	void		accept	(EventVisitor* visitor) override			{ visitor->visitEventEndIf(this); }

protected:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID		getType	() const override			{ return SerializationID::EventEndIf; }

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override
	{
		Event::serializableLoad(dataStream);

	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override
	{
		Event::serializableSave(dataStream);

	}
};