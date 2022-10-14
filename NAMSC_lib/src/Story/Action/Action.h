#pragma once
#include "Global.h"

#include "Story/Action/ActionVisitor.h"

class Event;
///Action is an additional work added to an Event
class Action : public QObject
{
	Q_OBJECT
	///Good Friends who Visit us (Actions) often :>
	friend class ActionVisitorChangeID;
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream &dataStream, Action &t);
	friend QDataStream& operator<<(QDataStream &dataStream, const Action &t);
	///Other friends
	friend bool operator==(const Action &lhs, const QString &rhs);
public:
	Action() = default;
	Action(Event *parent, unsigned actionID, QString &&label) :
		parent(parent), actionID(actionID), label(move(label))	{ assignLabel(); }
	Action(const Action& obj) {
		*this = obj;
	}
	Action& operator=(const Action& obj) {
		if (this == &obj) return *this;

		parent = obj.parent;
		label = obj.label;
		actionID = obj.actionID;

		return *this;
	}
	///The destructor needs to be virtual, so the proper destructor will always be called when destroying an Action pointer
	virtual ~Action() = 0;

	///Execution of an Action
	virtual void run()											{ ensureAssetsAreLoaded(); }

	///Some Actions are designed to update things and should be called frequently until the end of the Event
	virtual void update()										{}

	///Accept ActionVisitor, which will be run repending on the object's class
	virtual void accept(ActionVisitor *visitor)	= 0;

protected:
	///Needed for serialization, to know the class of an object before the loading performed
	virtual SerializationID getType() const		= 0;
	
	///Assigns an unique `label`, if it was not assigned by the Editor User
	///@todo implement this
	void assignLabel();

	///Ensures that all Assets have their resources loaded
	virtual void ensureAssetsAreLoaded()						{}

	///Event that contains this Action
	///Needed to access other Actions, so we can assing an unique label in `assignLabel()`
	Event *parent;

	///Label for quicker identification in the Editor
	QString label;

	///ID and position of the Action in the action list
	unsigned actionID;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream);
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const;
};

Action::~Action() = default;

bool operator==(const Action &lhs, const QString &rhs)
{
	return lhs.label == rhs;
}
