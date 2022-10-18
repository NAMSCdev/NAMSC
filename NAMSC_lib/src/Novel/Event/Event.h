#pragma once
#include "Global.h"

#include "Novel/Action/Action.h"

#include "Novel/Event/EventVisitor.h"

///Events, containing the flow changes in a Scene
class Event
{
	///Good Friends who Visit us (Actions) often :>
	friend class EventVisitorChangeID;
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Event&);
	friend QDataStream& operator<<(QDataStream&, const Event&);
public:
	Event() = default;
	Event(uint executionOrder, QString&& label) :
		  executionOrder(executionOrder), label(move(label)) {}
	Event(const Event& obj) { *this = obj; }
	Event& operator=(const Event& obj)
	{
		if (this == &obj) return *this;

		label          = obj.label;
		executionOrder = obj.executionOrder;
		actions        = obj.actions;

		return *this;
	}
	///The destructor needs to be virtual, so the proper destructor will always be called when destroying an Action pointer
	virtual ~Event() = 0;

	///Execution of an Event's logic
	virtual void run() = 0;

	///Some of the Event's Actions might be designed to update things and should be called frequently until the end of the Event
	virtual void update() {}

	///Some of the Event's Actions might need to access the data, that is a part of the Save
	///Must be called after the Save is loaded
	virtual void syncWithSave() {}

	///Checks if the Event's Actions don't have any errors, which would halt the Novel execution
	virtual bool checkForErrors() {}

	///Accept an EventVisitor
	virtual void accept	(EventVisitor *visitor)	= 0;


protected:
	///Needed for serialization, to know the class of an object before the loading performed
	virtual SerializationID getType() const		= 0;

	///Label for quicker identification in the Editor
	QString	 label;

	///Event execution order position with sceneID identifies the Event precisely
	uint executionOrder;

	///All actions 
	QVector<uPtr<Action>> actions;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream& dataStream);
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream& dataStream) const;
};

Event::~Event() = default;