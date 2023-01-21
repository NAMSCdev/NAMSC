#pragma once
#include "Novel/Action/Action.h"

#include "Novel/Data/Stat/Stat.h"

/// Contains common properties of Actions that manage Stats
class ActionStat : public Action
{
	/// Swap trick
	friend void swap(ActionStat& first, ActionStat& second) noexcept;
public:
	/// \exception Error Couldn't find the Stat named `statName`
	explicit ActionStat(Event* const parentEvent, const QString& statName = "", std::shared_ptr<Stat> stat = std::shared_ptr<Stat>());
	bool operator==(const ActionStat& obj) const noexcept;
	bool operator!=(const ActionStat& obj) const noexcept = default;
	//Makes it abstract
	virtual ~ActionStat() = 0;

	/// \exception Error `stat_` is invalid
	/// \return Whether an Error has occurred
	virtual bool errorCheck(bool bComprehensive = false) const override;

	/// Connects the Stat pointer to the actual Stat in the NovelState
	/// Must be called after the Save is loaded
	/// \exception Error Couldn't find the Stat named `statName_` in the current NovelState (`Novel::save`)
	void syncWithSave() override;

	QString getStatName() const noexcept;
	const std::shared_ptr<Stat> getStat() const noexcept;
	std::shared_ptr<Stat>       getStat()       noexcept;
	void setStat(const QString& statName, std::shared_ptr<Stat> stat = std::shared_ptr<Stat>()) noexcept;

protected:
	QString statName_ = "";
	std::shared_ptr<Stat> stat_;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const override;
};