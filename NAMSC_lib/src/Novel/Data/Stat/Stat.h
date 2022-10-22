#pragma once
#include "Global.h"

/// A variable assigned to the player
/// Does not persist across Saves
/// @todo Make Stats that persist over Saves
class Stat
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Stat&);
	friend QDataStream& operator<<(QDataStream&, const Stat&);
	friend class NovelState;
	//Other friends
	friend bool operator==(const Stat &lhs, const QString &rhs);
	friend bool operator<(const Stat &lhs, const Stat &rhs);
public:
	/// [optional] If there should be displayed some sort of notification once this Stat changes
	enum class ShowNotification
	{
		Default,	/// Defaults to the NovelSettings's setting
		Hide,
		Show
	};

	Stat() = default;
	Stat(QString&& name, QString&& displayName, bool bShow, uint priority, ShowNotification showNotification);
	Stat(const Stat& obj) { *this = obj; }
	Stat& operator=(const Stat& obj);
	virtual ~Stat();

	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	virtual SerializationID getType() const	= 0;
	
	/// Assigns value to the Stat from a QString value
	/// Makes Assigment from EventInput and Evaluators very easy
	virtual void setValueFromString(const QString &str) = 0;

protected:	
	/// Every Stat has two names, [displayName] is for the name shown in a Stat Screen and [name] is the one 
	QString name, displayName;	

	/// [optional] Whether this Stat is shown in Stat Screen
	bool bShow = true;

	/// [optional] Priority is used to order Stats when they are being displayed
	uint priority = 0;

	/// [optional] If there should be displayed some sort of notification once this Stat changes
	ShowNotification showNotification = ShowNotification::Default;

	//---SERIALIZATION---
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream);

	/// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const;
};




inline Stat::~Stat() = default;

inline Stat::Stat(QString&& name, QString&& displayName, bool bShow, uint priority, ShowNotification showNotification) : 
	name(move(name)), displayName(move(displayName)), bShow(bShow), priority(priority), showNotification(showNotification)
{
	if (this->displayName.isEmpty())
		this->displayName = this->name;
}

inline Stat& Stat::operator=(const Stat& obj)
{
	if (this == &obj) return *this;

	name = obj.name;
	displayName = obj.displayName;
	bShow = obj.bShow;
	priority = obj.priority;
	showNotification = obj.showNotification;

	return *this;
}

inline bool operator<(const Stat &lhs, const Stat &rhs)
{
	if (lhs.priority == rhs.priority)
		return (lhs.name.compare(rhs.name, Qt::CaseInsensitive) < 0);
	return lhs.priority < rhs.priority;
}

inline bool operator==(const Stat &lhs, const QString &rhs)
{
	return lhs.name == rhs;
}