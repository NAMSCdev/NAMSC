#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

#include "Story/Event/EventVisitor.h"

//Events, containing the flow changes in a Scene
class Event
{
	//Good Friends who Visit us (Actions) often :>
	friend class EventVisitorChangeID;
	//Friends for serialization
	friend QIODevice &operator>>(QIODevice &device, Event &t);
	friend QIODevice &operator<<(QIODevice &device, const Event &t);
public:
	Event(unsigned sceneID, unsigned executionOrder, QString &&label = "") :
		sceneID(sceneID), executionOrder(executionOrder), label(move(label)) {}

	//The destructor needs to be virtual, so the proper destructor will always be called when destroying an Action pointer
	virtual ~Event() = 0;

	//Execution of an Event
	virtual void				run				()								= 0;

	//Accept EventVisitor
	virtual void				accept			(EventVisitor *visitor)			= 0;

	//Add an Action to this Event
	void						addAction		(Action *action)				{ actions.emplace_back(action); };

	//TODO: implementation is not just removal, we need to use ActionVisitorDecrementID
	void						remove			(unsigned actionExecutionOrder) {};
protected:
	//Needed for serialization, to know the class of an object before the loading performed
	virtual SerializationID		getType			() const						= 0;

	//Label for quicker identification in the Editor
	QString						label;

	//Event execution order position with sceneID identifies the Event precisely
	unsigned					sceneID,
								executionOrder;

	//All actions 
	std::vector<uPtr<Action>>	actions;

	//---SERIALIZATION---
	//Loading an object from a binary file
	virtual void serializableLoad(QIODevice &ar)
	{
		QDataStream dataStream(&ar);
		dataStream >> label >> sceneID >> executionOrder;
		unsigned actionsSize;
		dataStream >> actionsSize;
		/*for (unsigned i = 0u; i != actionsSize; ++i)
		{
			SerializationID Type;
			ActionFilterBlur action;
			dataStream >> action;
			//Make serialization based on Type
			//actions.push_back(action);
		}*/
	}
	//Saving an object to a binary file
	virtual void serializableSave(QIODevice &ar) const
	{
		QDataStream dataStream(&ar);
		dataStream << getType() << label << sceneID << executionOrder;
		//for (Action *action : actions)
		//	action.serializableSave(ar);
	}
};

