#pragma once
#include "Global.h"
#include "Story/Event/Event.h"

//[optional] Contains a RenPy script that will be ignored, but written when convertering the Story to the RenPy Script
class EventRenPyScript final : public Event
{
public:
	EventRenPyScript() = default;
	EventRenPyScript(unsigned sceneID, unsigned executionOrder, QString &&script, QString &&label = "") :
		Event(sceneID, executionOrder, move(label)), script(move(script)) {}

	//Executes Event's logic
	void					run		() override;

	//Accepts EventVisitor
	void					accept	(EventVisitor* visitor) override		{ visitor->visitEventRenPy(this); }

protected:
	//Needed for serialization, to know the class of an object before the loading performed
	SerializationID			getType	() const override						{ return SerializationID::EventRenPyScript; }

	//RenPy script that will be ignored, but written when convertering this story to an RenPy Script
	QString					script;
};