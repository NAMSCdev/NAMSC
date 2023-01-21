#pragma once

#include <QString>

#include "Exceptions.h"
#include "Serialization.h"

/// Holds some Resources, which very likely take time to be loaded and allocate significant memory, so they should be loaded only when needed
class Asset
{
public:
	/// \exception Error Could not find/open/read the Resource file
	Asset(const QString& name = "", uint size = 0, uint pos = 0, const QString& path = "");
	Asset(const Asset& obj)                 noexcept = delete;
	Asset(Asset&& obj)                      noexcept   = default;
	Asset& operator=(const Asset& obj)      noexcept = delete;
	bool operator==(const Asset& obj) const noexcept = delete;
	bool operator!=(const Asset& obj) const noexcept = delete;
	// The destructor needs to be virtual, so the proper destructor will always be called when destroying an Asset pointer
	virtual ~Asset()                   = 0;

	/// \exception Error Could not find/open/read the Resource file
	/// \todo more intelligent loading when it is a compact file, so it is not opened and closed multiple times (static members in AssetManager that open and close on demand should do the trick)
	virtual void load()           = 0;
	virtual bool isLoaded() const = 0;
	virtual void unload()         = 0;

	/// Saves content changes (the Resource, not the definition)
	/// \exception Error Could not find/open/write to the file
	/// \todo implement this
	virtual void save()           = 0;

	/// \exception Error Couldn't find/open/read the Resource file
	/// \return Whether an Error has occurred
	virtual bool errorCheck(bool bComprehensive = false) const;
	
	/// Sets a function pointer that is called (if not nullptr) after the ActionAudioSetMusic's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	//void setOnSaveListener(std::function<void(const Event* const parentEvent, Scene* const parentScene, QString name, uint oldSize, uint size, uint pos, QString path)> onSave) { onSave_ = onSave; }

	QString	name = "";

	QString	path = "";

	/// [optional] If many Assets share the same binary file, it is needed to remember the position of every Asset
	uint pos     = 0;

	/// In bytes
	uint size    = 0;

protected:
	/// A function pointer that is called (if not nullptr) after the Asset's `void save() const` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	//std::function<void(const Event* const parentEvent, Scene* const parentScene, QString name, uint oldSize, uint size, uint pos, QString path)> onSave_;

	/// Indicates if there were content changes (the Resource, not the definition)
	bool bChanged_ = false;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const;
};