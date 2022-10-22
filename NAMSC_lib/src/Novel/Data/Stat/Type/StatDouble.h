#pragma once
#include "Global.h"

#include "Novel/Data/Stat/Stat.h"

/// A Stat with the floating-point value
class StatDouble final : public Stat
{
public:
	StatDouble() = default;
	StatDouble(QString&& name, QString&& displayName, bool bShow, uint priority, 
			   ShowNotification showNotification, double value, double min, double max);
	StatDouble(const StatDouble& obj) { *this = obj; }
	StatDouble& operator=(const StatDouble& obj);

	/// Assigns value to the Stat from a QString value
	/// Makes Assigment from EventInput and Evaluators very easy
	void setValueFromString(const QString& str) override
	{
		bool ok = true;
		double doubleValue = str.toDouble(&ok);
		if (!ok)
			;//todo: throw exception
		value = doubleValue;
	}

	/// Every Stat has [value] field, but not all must have [max] and/or [min]
	/// This one does
	double value, min, max;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::StatDouble; }

	//[optional] Label for the opposite Stat, used for a nicer display
	//QString oppositeStatLabel;

	//---SERIALIZATION---
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};




inline StatDouble::StatDouble(QString&& name, QString&& displayName, bool bShow, uint priority, 
							  ShowNotification showNotification, double value, double min, double max) : 
	Stat(move(name), move(displayName), bShow, priority, showNotification), value(value), min(min), max(max)
{
}

inline StatDouble& StatDouble::operator=(const StatDouble& obj)
{
	if (this == &obj) return *this;

	Stat::operator=(obj);
	value = obj.value;
	min   = obj.min;
	max   = obj.max;

	return *this;
}