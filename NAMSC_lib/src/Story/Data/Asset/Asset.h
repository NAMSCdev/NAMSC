#pragma once
#include "Global.h"

class Asset
{
	//Friends for serialization
	friend QIODevice &operator>>(QIODevice &device, Asset &t);
	friend QIODevice &operator<<(QIODevice &device, const Asset &t);
	//Other friends
	friend bool operator==(const Asset &lhs, const QString &rhs);
public:
	Asset() = default;
	Asset(QString &&URI, QString &&location, unsigned pos) : 
		URI(move(URI)), location(move(location)), pos(pos) {}

	//The destructor needs to be virtual, so the proper destructor will always be called when destroying an Asset pointer
	virtual ~Asset() = 0;

	//Tries to load an Assent
	//Throws a noncritical Exception on failure
	virtual bool			load	()				= 0;

	//Release resources allocated for this asset
	virtual void			unload	()				= 0;

	//Returns whether the asset is currently loaded
	virtual bool			isLoaded()				= 0;

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	virtual SerializationID	getType	() const		= 0;

	//Identificator for the Asset
	QString					URI;

	//Location of the resource
	QString					location;

	//If many Assets share the same binary file, we need to remember positions of every Asset
	unsigned				pos						= 0;

	//---SERIALIZATION---
	//Loading an object from a binary file
	virtual void serializableLoad(QIODevice &ar)
	{
		QDataStream dataStream(&ar);
		dataStream >> URI >> location >> pos;
	}
	//Saving an object to a binary file
	virtual void serializableSave(QIODevice &ar) const
	{
		QDataStream dataStream(&ar);
		dataStream << getType() << URI << location << pos;
	}
};

bool operator==(const Asset &lhs, const QString &rhs)
{
	return !lhs.URI.compare(rhs);
}