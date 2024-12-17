#pragma once
#include "pvnLib/Novel/Data/Stat/Stat.h"

/// A Stat with a floating-point value
class StatDouble final : public Stat
{
	/// Swap trick
	friend void swap(StatDouble& first, StatDouble& second) noexcept;
public:
	StatDouble()                                 noexcept = default;
	/// \param name The Stat is identified by this unique name
	/// \param displayName The name shown in a Stat Screen
	/// \param bShow Whether this Stat is shown in Stat Screen
	/// \param priority Priority is used to order Stats when they are being displayed
	/// \param showNotification If there should be displayed some sort of notification once this Stat changes
	/// \exception Error `min` is higher than `max` or the `value` is out of bounds
	explicit StatDouble(const QString& name, const QString& displayName = "", bool bShow = true, uint priority = 0, const ShowNotification showNotification = ShowNotification::Default, double value = 0.0, double min = std::numeric_limits<double>::min(), double max = std::numeric_limits<double>::max());
	StatDouble(const StatDouble& obj)            noexcept = default;
	StatDouble(StatDouble&& obj)                 noexcept = default;
	StatDouble& operator=(const StatDouble& obj) noexcept = default;
	//StatDouble& operator=(StatDouble obj)        noexcept;
	bool operator==(const StatDouble& obj) const noexcept = default;
	bool operator!=(const StatDouble& obj) const noexcept = default;

	/// \exception Error `min`/`max`/`value` is invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const;

	/// Makes Assigment from EventInput and Evaluators very easy
	/// \exception Error Could not perform conversation to the desired Stat's type
	void setValueFromString(const QString& str) override;

	double value = 0.0, 
		   min   = std::numeric_limits<double>::min(),
		   max   = std::numeric_limits<double>::max();

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	///Label for the opposite Stat, used for a nicer display
	//QString oppositeStatLabel;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};