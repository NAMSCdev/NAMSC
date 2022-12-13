#pragma once
#include "Novel/Action/Action.h"

#include "Novel/Data/Stat/Stat.h"

/// Contains common properties of Actions that manage Stats
class ActionStat : public Action
{
public:
	ActionStat(Event* const parentEvent, Scene* const parentScene) noexcept;
	/// \exception Error Couldn't find the Stat named `statName`
	ActionStat(Event* const parentEvent, Scene* const parentScene, const QString& statName);
	ActionStat(const ActionStat& obj) = delete;
	ActionStat& operator=(const ActionStat& obj) noexcept;
	bool operator==(const ActionStat& obj) const noexcept;
	bool operator!=(const ActionStat& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error `stat_` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const override;

	/// Connects the Stat pointer to the actual Stat in the NovelState
	/// Must be called after the Save is loaded
	/// \exception Error Couldn't find the Stat named `statName_` in the current NovelState (`Novel::save`)
	void syncWithSave() noexcept override;

	const Stat* getStat() const noexcept;
	Stat* getStat() noexcept;
	QString getStatName() const noexcept;
	void setStat(const QString& statName) noexcept;

protected:
	QString statName_ = "";
	Stat*   stat_     = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const override;
};