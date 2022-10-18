#pragma once
#include "Global.h"

class Asset
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Asset&);
	friend QDataStream& operator<<(QDataStream&, const Asset&);
	//Other friends
	friend bool operator==(const Asset &lhs, const QString &rhs);
public:
	Asset() = default;
	Asset(QString&& name, uint pos = 0, bool bExternal = false, QString&& location = "");
	Asset(const Asset& asset) { *this = asset; }
	Asset& operator=(const Asset& asset)	
	{
		name = asset.name; location = asset.location; bExternal = asset.bExternal; pos = asset.pos;
		return *this;
	}
	///The destructor needs to be virtual, so the proper destructor will always be called when destroying an Asset pointer
	virtual ~Asset()		= 0;

	///Tries to load an Asset
	///todo: describe petter
	///Throws a noncritical Exception on failure
	virtual void load()		= 0;

	///Release resources allocated for this asset
	virtual void unload()	= 0;

	///Returns whether the Asset is currently loaded
	virtual bool isLoaded() const = 0;

protected:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	virtual SerializationID	getType() const	= 0;

	///Identificator for the Asset
	QString	name;

	///Location of the resource
	QString	location;

	///Whether the location is relevant and the Asset should be loaded from external file
	///@todo implement this
	bool bExternal = false;

	///If many Assets share the same binary file, we need to remember positions of every Asset
	///@todo implement this
	uint pos = 0;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream);
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const;
};




inline Asset::~Asset() = default;

inline Asset& Asset::operator=(const Asset& asset)
{
	name      = asset.name;
	location  = asset.location; 
	bExternal = asset.bExternal; 
	pos       = asset.pos;
	return *this;
}

inline Asset::Asset(QString && name, uint pos = 0, bool bExternal = false, QString && location = "") :
	name(move(name)), location(move(location)), bExternal(bExternal), pos(pos) {}

inline bool operator==(const Asset &lhs, const QString &rhs)
{
	return lhs.name == rhs;
}