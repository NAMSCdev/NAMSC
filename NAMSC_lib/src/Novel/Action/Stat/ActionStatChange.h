#pragma once
#include "Global.h"

#include "Novel/Action/Stat/ActionStat.h"

/// Assigns a new value to a Stat
class ActionStatChange final : public ActionStat
{
public:
	ActionStatChange() noexcept = default;
	ActionStatChange(QString&& statName, QString&& expression);
	ActionStatChange(const ActionStatChange& obj) noexcept { *this = obj; }
	ActionStatChange& operator=(const ActionStatChange& obj) noexcept;

	/// Executes the ActionStatChange's logic
	void run() override;

	/// Checks if there are no errors in `statName` or `expression`
	/// \todo Implement `expression` checking
	bool checkForErrors() const noexcept override;

	/// Accepts an ActionVisitor
	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionStatChange(this); }

signals:
	/// A Qt signal emitted after the ActionStatChange's `void run()` allowing for data read
	/// \param stat The Stat that had its `value` changed
	/// \param expression Contains formula for calculating a new value for the Stat. It could refer to other Stats and perfrom arithmetic operations on them
	void onRun(const Stat* stat, const QString& expression) const;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionStatChange; }

	/// New value of the Stat is calculated from this expression
	QString	expression;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
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

inline bool ActionStatChange::checkForErrors() const
{
	bool bFailed = ActionStat::checkForErrors();
	if (bFailed)
		return true;

	try
	{

	}
	catch (...)
	{

	}
	return false;
}
