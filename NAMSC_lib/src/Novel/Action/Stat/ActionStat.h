#pragma once
#include "Global.h"

#include "Novel/Action/Action.h"
#include "Novel/Data/Stat/Stat.h"

/// Contains common properties of Actions that manage Stats
class ActionStat : public Action
{
public:
	ActionStat() noexcept = default;
	ActionStat(QString&& statName);
	ActionStat(const ActionStat& obj) noexcept { *this = obj; }
	ActionStat& operator=(const ActionStat& obj) noexcept;

	/// Connects Stat pointer to the actual Stat in the NovelState
	/// Must be called after the Save is loaded
	void syncWithSave();

	/// Checks if the ActionStat can find the Stat
	virtual bool checkForErrors() const noexcept override;

protected:
	/// Name of the Stat that is affected by the Action
	QString	statName;
	/// Stat that is affected by the Action
	Stat*   stat;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const override;
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
	stat     = obj.stat;

	return *this;
}