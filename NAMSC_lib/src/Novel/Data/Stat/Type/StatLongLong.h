#pragma once
#include "Global.h"

#include "Novel/Data/Stat/Stat.h"

/// A Stat with an integer value
class StatLongLong final : public Stat
{
public:
	StatLongLong() = default;
	StatLongLong(QString&& name, QString&& displayName, bool bShow, uint priority, 
				 ShowNotification showNotification, int value, int min, int max);
	StatLongLong(const StatLongLong& obj) { *this = obj; }
	StatLongLong& operator=(const StatLongLong& obj);

	/// Assigns value to the Stat from a QString value
	/// Makes Assigment from EventInput and Evaluators very easy
	void setValueFromString(const QString& str) override
	{
		bool ok = true;
		int longlongValue = str.toLongLong(&ok);
		if (!ok)
		{
			double doubleValue = str.toDouble(&ok);
			if (!ok)
				;//todo: throw exception
			if (doubleValue > 0)
				doubleValue -= 0.5;
			else doubleValue += 0.5;

			longlongValue = qRound(doubleValue);
		}
		value = longlongValue;
	}

	/// Every Stat has [value] field, but not all must have [max] and/or [min]
	/// This one does
	long long value, min, max;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::StatLongLong; }

	//[optional] Label for the opposite Stat, used for a nicer display
	//QString oppositeStatLabel;

	//---SERIALIZATION---
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};




inline StatLongLong::StatLongLong(QString&& name, QString&& displayName, bool bShow, uint priority, 
								  ShowNotification showNotification, int value, int min, int max) : 
	Stat(move(name), move(displayName), bShow, priority, showNotification), value(value), min(min), max(max) 
{
}

inline StatLongLong& StatLongLong::operator=(const StatLongLong& obj)
{
	if (this == &obj) return *this;

	Stat::operator=(obj);
	value = obj.value;
	min   = obj.min;
	max   = obj.max;

	return *this;
}