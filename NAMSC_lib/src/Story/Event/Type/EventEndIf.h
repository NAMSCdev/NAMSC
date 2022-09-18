#pragma once
#include "Global.h"

#include "Story/Event/Event.h"

//Ends an EventIf previous instance
//[optional todo] make checks and prevent placing umatched EndIf in editor
class EventEndIf final : public Event
{
public:
	EventEndIf(unsigned sceneID, unsigned executionOrder, QString &&label = "") :
		Event(sceneID, executionOrder, move(label)) {}

	//Executes Event's logic
	void				run		() override;

	//Accepts EventVisitor
	void				accept	(EventVisitor* visitor) override			{ visitor->visitEventEndIf(this); }

protected:
	//Needed for serialization, to know the class of an object before the loading performed
	SerializationID		getType	() const override							{ return SerializationID::EventEndIf; }

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Event::serializableLoad(ar);
		QDataStream dataStream(&ar);
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Event::serializableSave(ar);
		QDataStream dataStream(&ar);
	}
};