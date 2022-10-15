#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/AssetImage.h"
#include "Story/Data/Asset/Type/AssetMusic.h"
#include "Story/Data/Asset/AssetManager.h"

#include "Story/Data/Visual/Scenery/SceneryObject.h"
#include "Story/Data/Visual/Scenery/Character.h"

///All the media managed by the library contained in a displayable Scene
class Scenery
{
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Scenery&);
	friend QDataStream& operator<<(QDataStream&, const Scenery&);
public:
	Scenery() = default;
	Scenery();

	///Scenery's logic
	void run();

	///Ensures Assets are loaded and if not - loads them
	void ensureAssetsAreLoaded()
	{
	}

private:
	///Names of currently displayed SceneryObjects
	QVector<QString>		objectNames;
	///List of all the currently displayed SceneryObjects
	QVector<SceneryObject*>	objects;

	///Names of all the currently displayed Characters
	QVector<QString>		characterNames;
	///List of all the currently displayed Characters
	QVector<Character*>		characters;

	///Names of the Asset holding the music that will be played
	QVector<QString>		musicNames;
	///Music played in current Scenery`
	QVector<AssetMusic*>	musicPlaylist;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream);
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const;
};