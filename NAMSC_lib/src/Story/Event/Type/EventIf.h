#pragma once
#include "Global.h"

#include "Story/Event/Event.h"

///Ends an EventIf previous instance
///[optional todo] make checks and prevent placing umatched EndIf in editor
class EventIf final : public Event
{
public:
	EventIf() = default;
	EventIf(unsigned sceneID, unsigned executionOrder, QString &&condition, QString label = "") :
		Event(sceneID, executionOrder, move(label)), condition(move(condition))	{}

	///Executes Event's logic
	void		run		() override		{}

	///Accepts EventVisitor
	void		accept	(EventVisitor* visitor) override		{ visitor->visitEventIf(this); }

protected:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID		getType	() const override		{ typeid(EventIf).hash_code(); return SerializationID::EventIf; }

	///A jump might contain a logical expression, so the jump happens only if the [condition] is met
	QString		condition;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override
	{
		Event::serializableLoad(dataStream);

		dataStream >> condition;
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override
	{
		Event::serializableSave(dataStream);

		dataStream << condition;
	}
};