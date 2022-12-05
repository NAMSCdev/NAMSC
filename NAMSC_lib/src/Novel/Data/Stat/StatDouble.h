#pragma once
#include "Novel/Data/Stat/Stat.h"

/// A Stat with a floating-point value
class StatDouble final : public Stat
{
public:
	StatDouble()                                 = default;
	/// \exception Error `min` is higher than `max` or the `value` is out of bounds
	StatDouble(const QString& name, const QString& displayName, bool bShow, uint priority, 
			   const ShowNotification showNotification, double value, double min, double max);
	StatDouble(const StatDouble& obj)            = default;
	StatDouble& operator=(StatDouble obj) noexcept;
	bool operator==(const StatDouble& obj) const = default;
	bool operator!=(const StatDouble& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error `min`/`max`/`value` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const;

	/// Makes Assigment from EventInput and Evaluators very easy
	/// \exception Error Could not perform conversation to the desired Stat's type
	void setValueFromString(const QString& str) override;

	/// Every Stat has `value` field, but not all must have `max` and/or `min`
	/// This one does
	double	value = 0.0, 
			min   = std::numeric_limits<double>::min(),
			max   = std::numeric_limits<double>::max();

	///[optional] Label for the opposite Stat, used for a nicer display
	//QString oppositeStatLabel;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};