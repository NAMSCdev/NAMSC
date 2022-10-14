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
	friend bool operator<(const Stat &lhs,	const Stat &rhs);
public:
	///[optional] If there should be displayed some sort of notification once this Stat changes
	enum class ShowNotification
	{
		Default,	///Defaults to the StorySettings's setting
		Hide,
		Show
	};

	Stat() = default;
	Stat(QString &&name, QString &&displayName, bool bShow, unsigned priority, ShowNotification showNotification)
		: name(move(name)), displayName(move(displayName)), bShow(bShow), priority(priority), showNotification(showNotification)
	{
		if (this->displayName.isEmpty())
			this->displayName = this->name;
	}
	virtual ~Stat();

	///Needed for serialization, to know the class of an object about to be serialization loaded
	virtual SerializationID getType() const	= 0;

protected:	
	///Every Stat has two names, [displayName] is for the name shown in a Stat Screen and [name] is the one 
	QString	 name, displayName;	

	///[optional] Whether this Stat is shown in Stat Screen
	bool	 bShow							= true;

	///[optional] Priority is used to order Stats when they are being displayed
	unsigned priority						= 0;

	///[optional] If there should be displayed some sort of notification once this Stat changes
	ShowNotification showNotification		= ShowNotification::Default;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream)
	{
		dataStream >> name >> displayName >> bShow >> priority >> showNotification;
	}

	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const
	{
		dataStream << getType() << name << displayName << bShow << priority << showNotification;
	}
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
	StatString(QString &&name, QString &&displayName, bool bShow, unsigned priority, ShowNotification showNotification, QString &&value, unsigned maxChars)
		: Stat(move(name), move(displayName), bShow, priority, showNotification), value(move(value)), maxChars(maxChars) {}

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
	void serializableLoad(QDataStream &dataStream) override
	{
		Stat::serializableLoad(dataStream);

		dataStream >> value >> maxChars;
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override
	{
		Stat::serializableSave(dataStream);

		dataStream << value << maxChars;
	}
};

///A Stat with the boolean value
class StatBool final : public Stat
{
public:
	StatBool() = default;
	StatBool(QString &&name, QString &&displayName, bool bShow, unsigned priority, ShowNotification showNotification, bool value)
		: Stat(move(name), move(displayName), bShow, priority, showNotification), value(value) {}

	///Every Stat has [value] field, but not all must have [max] and/or [min]
	///This one does not
	bool value;

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID getType() const override { return SerializationID::StatBool; }
	
	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override
	{
		Stat::serializableLoad(dataStream);

		dataStream >> value;
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override
	{
		Stat::serializableSave(dataStream);

		dataStream << value;
	}
};

///A Stat with the integer value
class StatLongLong final : public Stat
{
public:
	StatLongLong() = default;
	StatLongLong(QString &&name, QString &&displayName, bool bShow, unsigned priority, ShowNotification showNotification,
			int value, int min, int max/*, QString &&oppositeStatLabel*/) : 
		Stat(move(name), move(displayName), bShow, priority, showNotification), value(value), min(min), max(max)/*,
		oppositeStatLabel(move(oppositeStatLabel))*/ {}

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
	void serializableLoad(QDataStream &dataStream) override
	{
		Stat::serializableLoad(dataStream);

		dataStream >> value >> min >> max/* >> oppositeStatLabel*/;
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override
	{
		Stat::serializableSave(dataStream);

		dataStream << value << min << max/* << oppositeStatLabel*/;
	}
};

///A Stat with the floating-point value
class StatDouble final : public Stat
{
public:
	StatDouble() = default;
	StatDouble(QString &&name, QString &&displayName, bool bShow, unsigned priority, ShowNotification showNotification,
			   double value, double min, double max/*, QString &&oppositeStatLabel*/) : 
		Stat(move(name), move(displayName), bShow, priority, showNotification), value(value), min(min), max(max)/*, oppositeStatLabel(move(oppositeStatLabel))*/ {}

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
	void serializableLoad(QDataStream &dataStream) override
	{
		Stat::serializableLoad(dataStream);

		dataStream >> value >> min >> max/* >> oppositeStatLabel*/;
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override
	{
		Stat::serializableSave(dataStream);

		dataStream << value << min << max/* << oppositeStatLabel*/;
	}
};
