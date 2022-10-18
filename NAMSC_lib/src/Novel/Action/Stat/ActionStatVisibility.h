#pragma once
#include "Global.h"

#include "Novel/Action/Stat/ActionStat.h"

///[optional] Makes a Stat displayed in a special Stat Display Menu 
class ActionStatVisibility final : public ActionStat
{
public:
	ActionStatVisibility() = default;
	ActionStatVisibility(QString&& statName, bool visibility);
	ActionStatVisibility(const ActionStatVisibility& obj) { *this = obj; }
	ActionStatVisibility& operator=(const ActionStatVisibility& obj);

	///Executes this Action's logic
	void run() override;

	///Accepts an ActionVisitor
	void accept(ActionVisitor *visitor) override { visitor->visitActionStatVisibility(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(Stat	*stat);
	
private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionStatVisibility; }

	///Whether the Stat is set to visible or not
	bool visibility;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};




inline ActionStatVisibility::ActionStatVisibility(QString&& statName, bool visibility) :
	ActionStat(move(statName)), visibility(visibility)
{
}

inline ActionStatVisibility& ActionStatVisibility::operator=(const ActionStatVisibility& obj)
{
	if (this == &obj) return *this;

	ActionStat::operator=(obj);
	visibility = obj.visibility;

	return *this;
}