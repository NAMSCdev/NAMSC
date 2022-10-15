#pragma once
#include "Global.h"

#include "Story/Action/Stat/ActionStat.h"

///[optional] Makes a Stat displayed in a special Stat Display Menu 
class ActionStatShow final : public ActionStat
{
public:
	ActionStatShow() = default;
	ActionStatShow(unsigned actionID, QString &&statName, QString &&label) :
		ActionStat(actionID, move(statName), move(label)) {}
	ActionStatShow(const ActionStatShow& obj) { *this = obj; }
	ActionStatShow& operator=(const ActionStatShow& obj)
	{
		if (this == &obj) return *this;

		ActionStat::operator=(obj);
		
		return *this;
	}

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor *visitor) override	{ visitor->visitActionStatShow(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(Stat	*stat);
	
private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override		{ return SerializationID::ActionStatShow; }

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};
