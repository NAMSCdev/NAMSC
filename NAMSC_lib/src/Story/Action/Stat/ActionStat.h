#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

#include "Story/Data/Stat/Stat.h"
#include "Story/Data/Story.h"

///Contains common properties of Actions that manage Stats
class ActionStat : public Action
{
public:
	ActionStat() = default;
	ActionStat(Event *parent, unsigned actionID, QString &&statName, QString &&label) :
		Action(parent, actionID, move(label)), statName(move(statName)) 
	{ 
		stat = Story::getInstance().getStoryState()->getStat(this->statName); 
	}
	ActionStat(const ActionStat& obj) {	*this = obj; }
	ActionStat& operator=(const ActionStat& obj) 
	{
		if (this == &obj) return *this;

		Action::operator=(obj);
		statName = obj.statName;
		stat     = obj.stat;

		return *this;
	}

protected:
	///Name of the Stat that is affected by this Action
	QString	statName;	
	///Stat that is affected by this Action
	Stat	*stat		= nullptr;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const override;
};
