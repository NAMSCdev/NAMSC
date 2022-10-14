#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

#include "Story/Event/EventVisitor.h"

///Events, containing the flow changes in a Scene
class Event
{
	///Good Friends who Visit us (Actions) often :>
	friend class EventVisitorChangeID;
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Event&);
	friend QDataStream& operator<<(QDataStream&, const Event&);
public:
	Event() = default;
	Event(unsigned sceneID, unsigned executionOrder, QString &&label) :
		sceneID(sceneID), executionOrder(executionOrder), label(move(label)) {}
	Event(const Event& asset)				= default;
	///Derived classes will create default assigment operator as well, if it is defined here
	Event& operator=(const Event& asset)	= default;
	///The destructor needs to be virtual, so the proper destructor will always be called when destroying an Action pointer
	virtual ~Event() = 0;

	///Execution of an Event
	virtual void		run		()		= 0;

	///Accept EventVisitor
	virtual void		accept			(EventVisitor *visitor)			= 0;

	///Add an Action to this Event
	void		addAction(Action *action)		{ actions.emplace_back(action); };

	///TODO: implementation is not just removal, we need to use ActionVisitorDecrementID
	void		remove(unsigned actionExecutionOrder) {};
protected:
	///Needed for serialization, to know the class of an object before the loading performed
	virtual SerializationID		getType			() const		= 0;

	///Label for quicker identification in the Editor
	QString	 label;

	///Event execution order position with sceneID identifies the Event precisely
	unsigned sceneID,
		executionOrder;

	///All actions 
	QVector<uPtr<Action>>	actions;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream)
	{

		dataStream >> label >> sceneID >> executionOrder;
		unsigned actionsSize;
		dataStream >> actionsSize;
		/*for (unsigned i = 0u; i != actionsSize; ++i)
		{
			SerializationID Type;
			ActionFilterBlur action;
			dataStream >> action;
			///Make serialization based on Type
			///actions.push_back(action);
		}*/
	}
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const
	{

		dataStream << getType() << label << sceneID << executionOrder;
		///for (Action *action : actions)
		///	action.serializableSave(dataStream);
	}
};

Event::~Event() = default;