#pragma once
#include "Novel/Action/Stat/ActionStat.h"

/// Assigns a new `value` to a Stat evaluated from `expression`
class ActionStatSetValue final : public ActionStat
{
public:
	ActionStatSetValue(Event* const parentEvent, Scene* const parentScene) noexcept;
	/// \exception Error Couldn't find the Stat named `statName_` in the current NovelState (`Novel::save`) or the `expression` has invalid syntax
	ActionStatSetValue(Event* const parentEvent, Scene* const parentScene, const QString& statName, const QString& expression);
	ActionStatSetValue(const ActionStatSetValue& obj) = delete;
	ActionStatSetValue& operator=(const ActionStatSetValue& obj) noexcept;
	bool operator==(const ActionStatSetValue& obj) const noexcept;
	bool operator!=(const ActionStatSetValue& obj) const = default; //{ return !(*this == obj); }

	/// \todo Implement `expression` checking
	/// \exception Error 'stat_' / `expression` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionStatSetValue's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, Stat* stat, QString expression)> onRun) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

	/// New value of the Stat is calculated from this expression
	QString	expression = "";

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the ActionStatSetValue's `void run()` allowing for data read
	/// \param stat The Stat that had its `value_` changed
	/// \param expression Contains formula for calculating a new value for the Stat. It could refer to other Stats and perfrom arithmetic operations on them
	std::function<void(Event* const parentEvent, Scene* const parentScene, Stat* stat, QString expression)> onRun_ = nullptr;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};