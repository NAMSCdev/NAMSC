#pragma once
#include "Global.h"

#include "Novel/Data/Audio/Sound.h"
#include "Novel/Data/Audio/MusicPlaylist.h"

#include "Novel/Data/Asset/Type/AssetImage.h"
#include "Novel/Data/Asset/Type/AssetMusic.h"
#include "Novel/Data/Asset/AssetManager.h"

#include "Novel/Data/Visual/Animation/Animator.h"

#include "Novel/Data/Visual/Scenery/SceneryObject.h"
#include "Novel/Data/Visual/Scenery/Character.h"

///All the media managed by the library contained in a displayable Scene
class Scenery
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Scenery&);
	friend QDataStream& operator<<(QDataStream&, const Scenery&);
public:
	Scenery() = default;
	Scenery(QVector<QString> &&objectNames, QVector<QString> &&characterNames, QVector<Sound> &&sounds, MusicPlaylist &&musicPlaylist);
	Scenery(const Scenery& obj) { *this = obj; }
	Scenery& operator=(const Scenery& obj)
	{
		if (this == &obj) return *this;

		objectNames    = obj.objectNames;
		objects        = obj.objects;
		characterNames = obj.characterNames;
		characters     = obj.characters;
		sounds         = obj.sounds;
		musicPlaylist  = obj.musicPlaylist;

		return *this;
	}
	///Scenery's logic
	void run();

	//TODO:
	//-anims
	//-sounds
	void update();

	///Ensures Assets are loaded and if not - loads them
	void ensureResourcesAreLoaded()
	{
		for (Sound& sound : sounds)
			if (!sound.isLoaded())
				sound.load();

		if (musicPlaylist.isLoaded())
			musicPlaylist.load();
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

	//TODO: Connect QMediaPlayer
	///Sounds that haven't been played yet, but they are supossed to be played at some point in time
	QVector<Sound>			sounds;

	///Music played in current Scenery
	MusicPlaylist			musicPlaylist;

	QImage background;

	uint time;

	QVector<Animator>;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream);
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const;
};