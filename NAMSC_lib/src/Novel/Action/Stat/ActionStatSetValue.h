#pragma once
#include "Novel/Action/Stat/ActionStat.h"

/// Assigns a new `value` to a Stat evaluated from `expression`
class ActionStatSetValue final : public ActionStat
{
	/// Swap trick
	friend void swap(ActionStatSetValue& first, ActionStatSetValue& second) noexcept;
public:
	explicit ActionStatSetValue(Event* const parentEvent) noexcept;
	/// \param stat Copies the Stat pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization 
	/// \param expression New value of the Stat is calculated from this expression
	/// \exception Error Couldn't find the Stat named `statName_` in the current NovelState (`Novel::save`) or the `expression` has invalid syntax
	ActionStatSetValue(Event* const parentEvent, const QString& statName, const QString& expression = "", std::shared_ptr<Stat> stat = nullptr);
	ActionStatSetValue(const ActionStatSetValue& obj)     noexcept;
	ActionStatSetValue(ActionStatSetValue&& obj)          noexcept;
	ActionStatSetValue& operator=(ActionStatSetValue obj) noexcept;
	bool operator==(const ActionStatSetValue& obj) const  noexcept;
	bool operator!=(const ActionStatSetValue& obj) const  noexcept = default;

	/// \todo Implement `expression` checking
	/// \exception Error 'stat_' / `expression` is invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionStatSetValue's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Event* const parentEvent, const std::shared_ptr<Stat> stat, const QString& expression)> onRun) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// New value of the Stat is calculated from this expression
	QString	expression = "";

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the ActionStatSetValue's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	/// \param stat The Stat that had its `value_` changed
	/// \param expression Contains formula for calculating a new value for the Stat. It could refer to other Stats and perfrom arithmetic operations on them
	std::function<void(const Event* const parentEvent, const std::shared_ptr<Stat> stat, const QString& expression)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};