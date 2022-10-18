#pragma once
#include "Global.h"

#include "Novel/Action/Action.h"

#include "Novel/Data/Stat/Stat.h"

///Contains common properties of Actions that manage Stats
class ActionStat : public Action
{
public:
	ActionStat() = default;
	ActionStat(QString&& statName);
	ActionStat(const ActionStat& obj) {	*this = obj; }
	ActionStat& operator=(const ActionStat& obj);

	///Connects Stat pointer to the actual Stat in the NovelState
	///Must be called after the Save is loaded
	void syncWithSave();

	///Checks if the Action can find the Stat
	bool checkForErrors() override;

protected:
	///Name of the Stat that is affected by this Action
	QString	statName;
	///Stat that is affected by this Action
	Stat*   stat;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const override;
};




inline ActionStat::ActionStat(QString&& statName) :
	Action(), statName(move(statName))
{
}

inline ActionStat& ActionStat::operator=(const ActionStat& obj)
{
	if (this == &obj) return *this;

	Action::operator=(obj);
	statName = obj.statName;
	stat = obj.stat;

	return *this;
}