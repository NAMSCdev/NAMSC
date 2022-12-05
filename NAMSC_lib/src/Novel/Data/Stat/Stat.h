#pragma once

#include <QDataStream>
#include <QString>

#include "Serialization.h"

/// A variable assigned to the Player
/// Does not persist across Saves
/// \todo [optional] Make Stats that persist over Saves
class Stat
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Stat&);
	friend QDataStream& operator<<(QDataStream&, const Stat&);
	friend class NovelState;
public:
	/// [optional] If there should be displayed some sort of notification once this Stat changes
	enum class ShowNotification
	{
		Default,	/// Defaults to the NovelSettings's setting
		Hide,
		Show
	};

	Stat() = default;
	Stat(const QString& name, const QString& displayName, bool bShow, uint priority, const ShowNotification showNotification);
	Stat(const Stat& obj)     = default;
	Stat(Stat&& obj)          = default;
	Stat& operator=(Stat obj) = delete;
	bool operator==(const Stat& obj) const = default;
	bool operator!=(const Stat& obj) const = default;
	bool operator==(const QString& name) const noexcept;
	bool operator!=(const QString& name) const noexcept;
	bool operator<(const Stat& rhs) const noexcept;
	// The destructor needs to be virtual, so the proper destructor will always be called when destroying a Stat pointer
	virtual ~Stat() = default;

	/// \return Whether an Error has occurred
	virtual bool checkForErrors(bool bComprehensive = false) const = 0;
	
	/// Assigns value to the Stat from a QString value
	/// Makes Assigment from EventInput and Evaluators very easy
	virtual void setValueFromString(const QString& str) = 0;

	/// Every Stat has two names, `displayName_` is for the name shown in a Stat Screen and `name_` is the one that the Stat is identified by
	QString name        = "",
			displayName = "";

	/// [optional] Whether this Stat is shown in Stat Screen
	bool bShow          = true;

	/// [optional] Priority is used to order Stats when they are being displayed
	uint priority       = 0;

	/// [optional] If there should be displayed some sort of notification once this Stat changes
	ShowNotification showNotification = ShowNotification::Default;

protected:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	virtual NovelLib::SerializationID getType() const = 0;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream);

	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const;
};