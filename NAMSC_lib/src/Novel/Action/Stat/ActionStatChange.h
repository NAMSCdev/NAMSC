#pragma once
#include "Global.h"

#include "Novel/Action/Stat/ActionStat.h"

///Assigns a new value to a Stat
class ActionStatChange final : public ActionStat
{
public:
	ActionStatChange() = default;
	ActionStatChange(QString&& statName, QString&& expression);
	ActionStatChange(const ActionStatChange& obj) { *this = obj; }
	ActionStatChange& operator=(const ActionStatChange& obj);

	///Executes this Action's logic
	void run() override;

	///Checks if there are no errors in `statName` or `expression`
	bool checkForErrors() override;

	///Accepts an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionStatChange(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(Stat	*stat, QString expression);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionStatChange; }

	///New value of the Stat is calculated from this expression
	QString	expression;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};


inline ActionStatChange::ActionStatChange(QString&& statName, QString&& expression) :
	ActionStat(move(statName)), expression(move(expression)) 
{
}

inline ActionStatChange& ActionStatChange::operator=(const ActionStatChange& obj)
{
	if (this == &obj) return *this;

	ActionStat::operator=(obj);
	expression = obj.expression;

	return *this;
}