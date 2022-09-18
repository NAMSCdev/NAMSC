#pragma once
#include "Global.h"

#include "Story/Event/Event.h"

//Ends an EventIf previous instance
//[optional todo] make checks and prevent placing umatched EndIf in editor
class EventIf final : public Event
{
public:
	EventIf() = default;
	EventIf(unsigned sceneID, unsigned executionOrder, QString &&condition, QString label = "") :
		Event(sceneID, executionOrder, move(label)), condition(move(condition))	{}

	//Executes Event's logic
	void				run		() override										{}

	//Accepts EventVisitor
	void				accept	(EventVisitor* visitor) override				{ visitor->visitEventIf(this); }

protected:
	//Needed for serialization, to know the class of an object before the loading performed
	SerializationID		getType	() const override								{ return SerializationID::EventIf; }

	//A jump might contain a logical expression, so the jump happens only if the [condition] is met
	QString				condition;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Event::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> condition;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Event::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << condition;
	}
};