#pragma once
#include "Global.h"
#include <type_traits>

//A variable assigned to the player
//Does not persist across Saves [TODO: should we make Stats that do?]
class Stat
{
	//Friends for serialization
	friend QIODevice &operator>>(QIODevice &device, Stat &t);
	friend QIODevice &operator<<(QIODevice &device, const Stat &t);
	//Other friends
	friend bool operator==(const Stat &lhs, const QString &rhs);
	friend bool operator<(const Stat &lhs,	const Stat &rhs);
public:
	enum class SliderStyle
	{
		None,
		Filled,
		Shifting,
		DualColor,
		DualColorHiddenLabel
	};
	Stat() = default;
	Stat(QString &&name, QString &&displayName, bool bHidden = false, unsigned priority = 0)
		: name(move(name)), displayName(move(displayName)), bHidden(bHidden), priority(priority)
	{
		if (displayName.isEmpty())
			this->displayName = this->name;
	}

	//[optional] Whether this Stat is shown in Stat Screen
	bool							bHidden;

	//Returns formatted text for display and its DisplaySettings
	virtual void					display				(QLabel *display)	= 0;

protected:	
	//Needed for serialization, to know the class of an object about to be serialization loaded
	virtual SerializationID			getType				() const			= 0;

	//Every Stat has two names, [displayName] is for the name shown in a Stat Screen and [name] is the one 
	QString							name, displayName;	

	//Priority is used to order Stats when they are being displayed
	unsigned						priority								= 0;

	//---SERIALIZATION---
	//Loading an object from a binary file
	virtual void serializableLoad(QIODevice &ar)
	{
		QDataStream dataStream(&ar);
		dataStream >> name >> displayName >> bHidden >> priority;
	}
	//Saving an object to a binary file
	virtual void serializableSave(QIODevice &ar) const
	{
		QDataStream dataStream(&ar);
		dataStream << getType() << name << displayName << bHidden << priority;
	}
};

bool operator<(const Stat &lhs, const Stat &rhs)
{
	if (lhs.priority == rhs.priority)
		return (lhs.name.compare(rhs.name, Qt::CaseInsensitive) < 0);
	return lhs.priority < rhs.priority;
}

class StringStat final : public Stat
{
public:
	StringStat() = default;
	StringStat(QString &&name, QString &&displayName, QString &&value, bool bHidden = false, unsigned priority = 0)
		: Stat(move(name), move(displayName), bHidden, priority), value(move(value)) {}

	//Every Stat has [value] field, but not all must have [max] and/or [min]
	//This one does not
	QString						value;

	//Returns formatted text for display and its DisplaySettings
	void						display			(QLabel* display) override;

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID				getType			() const override			{ return SerializationID::StringStat; }

	//Max characters displayed
	unsigned maxChars = 0;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Stat::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> value;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Stat::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << value;
	}
};

class BoolStat final : public Stat
{
public:
	BoolStat() = default;
	BoolStat(QString &&name, QString &&displayName, bool value, bool bHidden = false, unsigned priority = 0)
		: Stat(move(name), move(displayName), bHidden, priority), value(value) {}

	//Every Stat has [value] field, but not all must have [max] and/or [min]
	//This one does not
	bool						value;

	//Returns formatted text for display and its DisplaySettings
	void						display			(QLabel* display) override;

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID				getType			() const override			{ return SerializationID::BoolStat; }

	//TODO: checkbox?
	
	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Stat::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> value;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Stat::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << value;
	}
};

class IntStat final : public Stat
{
public:
	IntStat() = default;
	IntStat(QString &&name, QString &&displayName, int value, int min, int max, QString &&oppositeStatName = "", bool bHidden = false, unsigned priority = 0)
		: Stat(move(name), move(displayName), bHidden, priority), oppositeStatName(move(oppositeStatName)), value(value), min(min), max(max) {}

	//Every Stat has [value] field, but not all must have [max] and/or [min]
	//This one does
	int							value, max, min;

	//Returns formatted text for display and its DisplaySettings
	void						display			(QLabel* display) override;

	//TODO: progression bar setup
	//void						setProgressBar	(QProgressBar *bar)			{ bar->setValue(static_cast<double>(value-min)/(max-min)); };
protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID				getType			() const override			{ return SerializationID::IntStat; }

	//Style of the slider showing Stat's progression
	SliderStyle					sliderStyle;

	//TODO: interpret opposite Stat
	QString						oppositeStatName;
	IntStat*					oppositeStat;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Stat::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> value >> min >> max >> oppositeStatName;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Stat::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << value << min << max << oppositeStatName;
	}
};

class DoubleStat final : public Stat
{
public:
	DoubleStat() = default;
	DoubleStat(QString &&name, QString &&displayName, double value, double min, double max, QString &&oppositeStatName = "", bool bHidden = false, unsigned priority = 0)
		: Stat(move(name), move(displayName), bHidden, priority), oppositeStatName(move(oppositeStatName)), value(value), min(min), max(max) {}

	//Every Stat has [value] field, but not all must have [max] and/or [min]
	//This one does
	double						value, max, min;

	//Returns formatted text for display and its DisplaySettings
	void						display			(QLabel* display) override;

	//TODO: progression bar setup
	//void						setProgressBar	(QProgressBar *bar)			{ bar->setValue(static_cast<double>(value-min)/(max-min)); };
protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID				getType			() const override			{ return SerializationID::DoubleStat; }

	//Style of the slider showing Stat's progression
	SliderStyle					sliderStyle;

	//TODO: interpret opposite Stat
	QString						oppositeStatName;
	IntStat*					oppositeStat;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Stat::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> value >> min >> max >> oppositeStatName;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Stat::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << value << min << max << oppositeStatName;
	}
};
