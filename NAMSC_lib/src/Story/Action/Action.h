#pragma once
#include "Global.h"

#include "Story/Action/ActionVisitor.h"

//Action is an additional work added to an Event
class Action
{
	//Good Friends who Visit us (Actions) often :>
	friend class ActionVisitorChangeID;
	//Friends for serialization
	friend QIODevice &operator>>(QIODevice &device, Action &t);
	friend QIODevice &operator<<(QIODevice &device, const Action &t);
public:
	Action() = default;
	Action(unsigned sceneID, unsigned eventExecutionOrder, QString &&label = "") :
		sceneID(sceneID), eventExecutionOrder(eventExecutionOrder), label(move(label)) {}
	//The destructor needs to be virtual, so the proper destructor will always be called when destroying an Action pointer
	virtual ~Action() = 0;

	//Execution of an Action
	virtual void					run						()							= 0;

	//Executes the Action, previously esnuring that every Asset is already loaded
	void							safeRun					()							{ ensureAssetsAreLoaded(); run(); }

	//Accept ActionVisitor, which will be run repending on the object's class
	virtual void					accept					(ActionVisitor* visitor)	= 0;

protected:
	//Needed for serialization, to know the class of an object before the loading performed
	virtual SerializationID			getType					() const					= 0;
	
	virtual void					ensureAssetsAreLoaded	()							{}

	//Label for quicker identification in the Editor
	QString							label;

	//Event execution order position with sceneID identifies the Event precisely and all Actions are contained within Events
	//TODO: since Actions are contained, do we need to store the IDs at all?
	unsigned						sceneID,
									eventExecutionOrder;

	//ID and position of the Action in the action list
	unsigned						actionID;

	//---SERIALIZATION---
	//Loading an object from a binary file
	virtual void serializableLoad(QIODevice &ar)
	{
		QDataStream dataStream(&ar);
		dataStream >> label >> sceneID >> eventExecutionOrder;
	}
	//Saving an object to a binary file
	virtual void serializableSave(QIODevice &ar) const
	{
		QDataStream dataStream(&ar);
		dataStream << getType() << label << sceneID << eventExecutionOrder;
	}
};

