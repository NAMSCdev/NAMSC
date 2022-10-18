#pragma once
#include "Global.h"

#include "Novel/Event/Event.h"

///Redirects the flow to an another Scene
class EventJump final : public Event
{
public:
	EventJump() = default;
	EventJump(uint executionOrder, QString&& label, uint jumpSceneId, uint jumpExecutionOrder, QString &&condition) :
		Event(executionOrder, move(label)), jumpSceneId(jumpSceneId), jumpExecutionOrder(jumpExecutionOrder), condition(move(condition)) { }
	EventJump(const EventJump& obj) { *this = obj; }
	EventJump& operator=(const EventJump& obj);

	///Executes this Event's logic
	void run() override;

	///Accepts an EventVisitor
	void accept(EventVisitor* visitor) override { visitor->visitEventJump(this); }

signals:
	///A Qt signal executing after the Event's `run()` allowing for data read (and write if it is a pointer)
	void onRun(uint jumpSceneId, uint jumpExecutionOrder, QString condition);

private:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID getType() const override	{ return SerializationID::EventJump; }

	///The jump needs to define to which Scene it jumps and from which Action in that Scene it should start ([offset])
	int	jumpSceneId,
		jumpExecutionOrder;

	///A jump might contain a logical expression, so the jump happens only if the [condition] is met
	QString  condition;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};

inline EventJump& EventJump::operator=(const EventJump& obj)
{
	if (this == &obj) return *this;

	Event::operator=(obj);
	jumpSceneId = obj.jumpSceneId;
	jumpExecutionOrder = obj.jumpExecutionOrder;
	condition = obj.condition;

	return *this;
}