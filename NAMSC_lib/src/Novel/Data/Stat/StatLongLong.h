#pragma once
#include "Novel/Data/Stat/Stat.h"

/// A Stat with an integer value
class StatLongLong final : public Stat
{
	/// Swap trick
	friend void swap(StatLongLong& first, StatLongLong& second) noexcept;
public:
	StatLongLong()                                   noexcept = default;
	/// \param name The Stat is identified by this unique name
	/// \param displayName The name shown in a Stat Screen
	/// \param bShow Whether this Stat is shown in Stat Screen
	/// \param priority Priority is used to order Stats when they are being displayed
	/// \param showNotification If there should be displayed some sort of notification once this Stat changes
	/// \exception Error `min` is higher than `max` or the `value` is out of bounds
	explicit StatLongLong(const QString& name, const QString& displayName = "", bool bShow = true, uint priority = 0, const ShowNotification showNotification = ShowNotification::Default, long long value = 0ll, long long min = std::numeric_limits<long long>::min(), long long max = std::numeric_limits<long long>::max());
	StatLongLong(const StatLongLong& obj)            noexcept = default;
	StatLongLong(StatLongLong&& obj)                 noexcept = default;
	StatLongLong& operator=(const StatLongLong& obj) noexcept = default;
	//StatLongLong& operator=(StatLongLong obj)        noexcept;
	bool operator==(const StatLongLong& obj) const   noexcept = default;
	bool operator!=(const StatLongLong& obj) const   noexcept = default;

	/// \exception Error `min`/`max`/`value` is invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const;

	/// Makes Assigment from EventInput and Evaluators very easy
	/// \exception Error Could not perform conversation to the desired Stat's type
	void setValueFromString(const QString& valueInText) override;

	long long value = 0ll,
			  min   = std::numeric_limits<long long>::min(),
			  max   = std::numeric_limits<long long>::max();

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