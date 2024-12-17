#pragma once
#include "pvnLib/Novel/Event/Event.h"

/// [optional] Contains a RenPy script that will be ignored, but written when convertering the Novel to the RenPy Script
class EventRenPyScript final : public Event
{
public:
	EventRenPyScript() noexcept = default;
	EventRenPyScript(uint executionOrder, QString&& label, QString&& script) :
		Event(executionOrder, move(label)), script(move(script)) {}
	EventRenPyScript(const EventRenPyScript& obj) { *this = obj; }
	EventRenPyScript& operator=(const EventRenPyScript& obj)
	{
		if (this == &obj) return *this;

		Event::operator=(obj);
		script = obj.script;

		return *this;
	}
	/// Executes this Event's logic
	void run() override;

	/// Accepts an EventVisitor
	void accept(EventVisitor* visitor) override		{ visitor->visitEventRenPy(this); }

signals:
	/// A Qt signal emitted after the Event's `void run()` allowing for data read
	void onRun(QString* script);

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	SerializationID getType() const override		{ return SerializationID::EventRenPyScript; }

	/// RenPy script that will be ignored, but written when convertering this story to an RenPy Script
	QString			script;
};