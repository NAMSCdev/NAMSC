#pragma once
#include "Global.h"

class Asset
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Asset&);
	friend QDataStream& operator<<(QDataStream&, const Asset&);
	//Other friends
	friend bool operator==(const Asset& lhs, const QString& rhs);
public:
	Asset() = default;
	Asset(QString&& name, uint pos = 0, QString&& location = "");
	Asset(const Asset& obj)            = delete;
	Asset& operator=(const Asset& obj) = delete;

	/// The destructor needs to be virtual, so the proper destructor will always be called when destroying an Asset pointer
	virtual ~Asset()              = 0;

	/// Tries to load an Asset
	/// @exception Throws a noncritical Exception on failure
	/// @todo more intelligent loading when it is a compact file, so it is not opened and closed multiple times (static members in AssetManager that open and close on demand should do the trick)
	virtual void load()           = 0;

	/// Release resources allocated for this asset
	virtual void unload()         = 0;

	/// Returns whether the Asset is currently loaded
	virtual bool isLoaded() const = 0;

	/// Checks whether the file that the Asset refers to is present in the filesystem
	QPair<bool, QString> checkFileExistence() const;

protected:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	virtual SerializationID	getType() const	= 0;

	/// Identificator for the Asset
	QString	name;

	/// Location of the resource
	QString	location;

	/// [optional]If many Assets share the same binary file, we need to remember position of every Asset
	uint pos = 0;

	//---SERIALIZATION---
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream &dataStream);
	/// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const;
};




inline Asset::~Asset() = default;

inline Asset::Asset(QString&& name, uint pos = 0, QString&& location = "") :
	name(move(name)), location(move(location)), pos(pos)
{
}

inline QPair<bool, QString> Asset::checkFileExistence() const
{
	if (location == "") 
		return { QFile::exists("resource.bin"), "resource.bin" };

	return { QFile::exists(location), location };
}

inline bool operator==(const Asset& lhs, const QString& rhs)
{
	return lhs.name == rhs;
}