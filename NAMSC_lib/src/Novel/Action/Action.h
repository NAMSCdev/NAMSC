#pragma once
#include "Global.h"

#include "Novel/Action/ActionVisitor.h"
#include "Novel/Data/NovelFlowInterface.h"

class Event;
///Action is an additional work added to an Event
class Action : public QObject, public NovelFlowInterface
{
	Q_OBJECT
	//Good Friends who Visit us (Actions) often :>
	friend class ActionVisitorChangeID;
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream &dataStream, Action&);
	friend QDataStream& operator<<(QDataStream &dataStream, const Action&);
	//Other friends
	friend Event;
public:
	Action() = default;
	Action(const Action& obj) { *this = obj; }
	Action& operator=(const Action& obj);
	///The destructor needs to be virtual, so the proper destructor will always be called when destroying an Action pointer
	virtual ~Action() = 0;

	///Execution of an Action
	virtual void run() override { ensureResourcesAreLoaded(); }

	///Some Actions are designed to update things and should be called frequently until the end of the Event
	virtual void update() override { NovelFlowInterface::update(); }

	///Some Actions need to access the data, that is a part of the Save
	///Must be called after the Save is loaded
	virtual void syncWithSave()	override {}

	///Checks if the Action doesn't have any errors, which would halt the Novel execution
	virtual bool checkForErrors() override {}

	///Cleanup of an Action
	virtual void end() override;

	///Accept ActionVisitor, which will be run repending on the object's class
	virtual void accept(ActionVisitor *visitor)	= 0;

protected:
	///Needed for serialization, to know the class of an object before the loading performed
	virtual SerializationID getType() const = 0;

	///Ensures that all Assets have their resources loaded
	virtual void ensureResourcesAreLoaded() {}

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream);
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const;
};




Action::~Action() = default;