#pragma once
#include "Global.h"

#include "Story/Event/Event.h"

///Redirects the flow to an another Scene
class EventJump final : public Event
{
public:
	EventJump() = default;
	EventJump(unsigned sceneID, unsigned executionOrder, unsigned jumpSceneId, unsigned jumpExecutionOrder, QString &&condition, QString &&label = "") :
		Event(sceneID, executionOrder, move(label)), jumpSceneId(jumpSceneId), jumpExecutionOrder(jumpExecutionOrder), condition(move(condition)) {}

	///Executes Event's logic
	void			run			() override;

	///Accepts EventVisitor
	void			accept		(EventVisitor* visitor) override	{ visitor->visitEventJump(this); }

protected:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID			getType		() const override			{ return SerializationID::EventJump; }

	///The jump needs to define to which Scene it jumps and from which Action in that Scene it should start ([offset])
	unsigned		jumpSceneId,
			jumpExecutionOrder;

	///A jump might contain a logical expression, so the jump happens only if the [condition] is met
	QString			condition;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override
	{
		Event::serializableLoad(dataStream);

		dataStream >> jumpSceneId >> jumpExecutionOrder >> condition;
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override
	{
		Event::serializableSave(dataStream);

		dataStream << jumpSceneId << jumpExecutionOrder << condition;
	}
};