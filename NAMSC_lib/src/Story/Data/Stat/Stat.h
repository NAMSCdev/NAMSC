#pragma once
#include "Global.h"

///A variable assigned to the player
///Does not persist across Saves
///@todo Make Stats that persist over Saves
class Stat
{
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Stat&);
	friend QDataStream& operator<<(QDataStream&, const Stat&);
	friend class StoryState;
	///Other friends
	friend bool operator==(const Stat &lhs, const QString &rhs);
	friend bool operator<(const Stat &lhs, const Stat &rhs);
public:
	///[optional] If there should be displayed some sort of notification once this Stat changes
	enum class ShowNotification
	{
		Default,	///Defaults to the StorySettings's setting
		Hide,
		Show
	};

	Stat() = default;
	Stat(QString&& name, QString&& displayName, bool bShow, unsigned priority, ShowNotification showNotification)
		: name(move(name)), displayName(move(displayName)), bShow(bShow), priority(priority), showNotification(showNotification)
	{
		if (this->displayName.isEmpty())
			this->displayName = this->name;
	}
	Stat(const Stat& obj) { *this = obj; }
	Stat& operator=(const Stat& obj)
	{
		if (this == &obj) return *this;

		name             = obj.name;
		displayName      = obj.displayName;
		bShow            = obj.bShow;
		priority         = obj.priority;
		showNotification = obj.showNotification;

		return *this;
	}
	virtual ~Stat();

	///Needed for serialization, to know the class of an object about to be serialization loaded
	virtual SerializationID getType() const	= 0;

protected:	
	///Every Stat has two names, [displayName] is for the name shown in a Stat Screen and [name] is the one 
	QString name, displayName;	

	///[optional] Whether this Stat is shown in Stat Screen
	bool bShow = true;

	///[optional] Priority is used to order Stats when they are being displayed
	unsigned priority = 0;

	///[optional] If there should be displayed some sort of notification once this Stat changes
	ShowNotification showNotification = ShowNotification::Default;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream& dataStream);

	///Saving an object to a binary file
	virtual void serializableSave(QDataStream& dataStream) const;
};

Stat::~Stat() = default;

bool operator<(const Stat &lhs, const Stat &rhs)
{
	if (lhs.priority == rhs.priority)
		return (lhs.name.compare(rhs.name, Qt::CaseInsensitive) < 0);
	return lhs.priority < rhs.priority;
}

bool operator==(const Stat &lhs, const QString &rhs)
{
	return lhs.name == rhs;
}

///A Stat with the string value
class StatString final : public Stat
{
public:
	StatString() = default;
	StatString(QString&& name, QString&& displayName, bool bShow, unsigned priority, ShowNotification showNotification, QString&& value, unsigned maxChars)
		: Stat(move(name), move(displayName), bShow, priority, showNotification), value(move(value)), maxChars(maxChars) {}
	StatString(const StatString& obj) { *this = obj; }
	StatString& operator=(const StatString& obj)
	{
		if (this == &obj) return *this;

		Stat::operator=(obj);
		value    = obj.value;
		maxChars = obj.maxChars;

		return *this;
	}
	///Every Stat has [value] field, but not all must have [max] and/or [min]
	///This one does not
	QString value;

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::StatString; }

	///Max characters displayed
	unsigned maxChars = 0;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};

///A Stat with the boolean value
class StatBool final : public Stat
{
public:
	StatBool() = default;
	StatBool(QString&& name, QString&& displayName, bool bShow, unsigned priority, ShowNotification showNotification, bool value)
		: Stat(move(name), move(displayName), bShow, priority, showNotification), value(value) {}
	StatBool(const StatBool& obj) { *this = obj; }
	StatBool& operator=(const StatBool& obj)
	{
		if (this == &obj) return *this;

		Stat::operator=(obj);
		value = obj.value;

		return *this;
	}
	///Every Stat has [value] field, but not all must have [max] and/or [min]
	///This one does not
	bool value;

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID getType() const override { return SerializationID::StatBool; }
	
	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};

///A Stat with the integer value
class StatLongLong final : public Stat
{
public:
	StatLongLong() = default;
	StatLongLong(QString&& name, QString&& displayName, bool bShow, unsigned priority, ShowNotification showNotification,
			int value, int min, int max/*, QString&& oppositeStatLabel*/) : 
		Stat(move(name), move(displayName), bShow, priority, showNotification), value(value), min(min), max(max)/*,
		oppositeStatLabel(move(oppositeStatLabel))*/ {}
	StatLongLong(const StatLongLong& obj) { *this = obj; }
	StatLongLong& operator=(const StatLongLong& obj)
	{
		if (this == &obj) return *this;

		Stat::operator=(obj);
		value = obj.value;
		min   = obj.min;
		max   = obj.max;

		return *this;
	}
	///Every Stat has [value] field, but not all must have [max] and/or [min]
	///This one does
	long long value, min, max;

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::StatLongLong; }

	//[optional] Label for the opposite Stat, used for a nicer display
	//QString oppositeStatLabel;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};

///A Stat with the floating-point value
class StatDouble final : public Stat
{
public:
	StatDouble() = default;
	StatDouble(QString&& name, QString&& displayName, bool bShow, unsigned priority, ShowNotification showNotification,
			   double value, double min, double max/*, QString&& oppositeStatLabel*/) : 
		Stat(move(name), move(displayName), bShow, priority, showNotification), value(value), min(min), max(max)/*, oppositeStatLabel(move(oppositeStatLabel))*/ {}
	StatDouble(const StatDouble& obj) { *this = obj; }
	StatDouble& operator=(const StatDouble& obj)
	{
		if (this == &obj) return *this;

		Stat::operator=(obj);
		value = obj.value;
		min   = obj.min;
		max   = obj.max;

		return *this;
	}
	///Every Stat has [value] field, but not all must have [max] and/or [min]
	///This one does
	double value, min, max;

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::StatDouble; }

	//[optional] Label for the opposite Stat, used for a nicer display
	//QString oppositeStatLabel;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};
