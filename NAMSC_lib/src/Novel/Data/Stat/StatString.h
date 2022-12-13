#pragma once
#include "Novel/Data/Stat/Stat.h"

/// A Stat with a string value
class StatString final : public Stat
{
public:
	StatString()                                 = default;
	StatString(const QString& name, const QString& displayName, bool bShow, uint priority,
			   const ShowNotification showNotification, const QString& value, uint maxChars);
	StatString(const StatString& obj)            = default;
	StatString(StatString&& obj)                 = default;
	StatString& operator=(StatString obj) noexcept;
	bool operator==(const StatString& obj) const noexcept;
	bool operator!=(const StatString& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error `min`/`max`/`value` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const;

	/// Makes Assigment from EventInput and Evaluators very easy
	/// \exception Error Could not perform conversation to the desired Stat's type
	void setValueFromString(const QString& str) override;

	QString value = "";

	/// [optional] Max characters displayed, not held
	uint maxChars = 0;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

public://---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};