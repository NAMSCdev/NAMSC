#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/ImageAsset.h"
#include "Story/Data/Asset/Type/MusicAsset.h"
#include "Story/Data/Asset/AssetManager.h"

#include "Story/Data/Visual/Scenery/SceneryObject.h"
#include "Story/Data/Visual/Scenery/Character.h"

//This hasn't been thought through yet. It is very WIP
//TODO: add specia media type e.g. chocie buttons and display text boxes
//All media contained in a displayable Scene
class Scenery
{
	//Friends for serialization
	friend QIODevice &operator>>(QIODevice &device, Scenery &t);
	friend QIODevice &operator<<(QIODevice &device, const Scenery &t);
public:
	Scenery() = default;
	//TODO: add a special constructor, once fields are set in stone
	//Scenery(
	//TODO: think how exactly the QImage will be created and if the interface is sufficient
	QImage	display		();

	//TODO: think about helper functions e.g.: shuffle
	//TODO: more fields needed for the music
	//TODO: should it be tied with event instead? What should display the text? Scenery or Scene? How do we sync?
	//TODO: should this return a pointer to MediaPlayer or play one that Asset has?
	void	playMusic	();

private:
	//TODO: comment this
	std::vector<QString>		objectNames;
	//TODO: comment this
	std::vector<SceneryObject*>	objects;

	//TODO: comment this
	std::vector<QString>		characterNames;
	//TODO: comment this
	std::vector<Character*>		characters;

	//TODO: comment this
	std::vector<QString>		musicPlaylistNames;
	//TODO: comment this
	std::vector<MusicAsset*>	musicPlaylist;

	//TODO: serialization including all the objects
	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar)
	{
		QDataStream dataStream(&ar);
		dataStream;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const
	{
		QDataStream dataStream(&ar);
		dataStream;
	}
};