#pragma once
#include "Global.h"

#include "Novel/Data/Stat/Stat.h"

/// A Stat with the string value
class StatString final : public Stat
{
public:
	StatString() = default;
	StatString(QString&& name, QString&& displayName, bool bShow, uint priority,
			   ShowNotification showNotification, QString&& value, uint maxChars);
	StatString(const StatString& obj) { *this = obj; }
	StatString& operator=(const StatString& obj);

	/// Assigns value to the Stat from a QString value
	/// Makes Assigment from EventInput and Evaluators very easy
	void setValueFromString(const QString &str) override
	{
		value = str;
	}

	/// Every Stat has [value] field, but not all must have [max] and/or [min]
	/// This one does not
	QString value;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::StatString; }

	/// Max characters displayed
	uint maxChars = 0;

	//---SERIALIZATION---
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};




inline StatString::StatString(QString&& name, QString&& displayName, bool bShow, uint priority,
							  ShowNotification showNotification, QString&& value, uint maxChars) :
	Stat(move(name), move(displayName), bShow, priority, showNotification), value(move(value)), maxChars(maxChars)
{ 
}

inline StatString& StatString::operator=(const StatString& obj)
{
	if (this == &obj) return *this;

	Stat::operator=(obj);
	value    = obj.value;
	maxChars = obj.maxChars;

	return *this;
}