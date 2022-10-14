#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/ImageAsset.h"
#include "Story/Data/Asset/Type/MusicAsset.h"
#include "Story/Data/Asset/AssetManager.h"

#include "Story/Data/Visual/Scenery/SceneryObject.h"
#include "Story/Data/Visual/Scenery/Character.h"

///All media contained in a displayable Scene
///@todo Add special media types e.g. chocie buttons and display text boxes
class Scenery
{
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Scenery&);
	friend QDataStream& operator<<(QDataStream&, const Scenery&);
public:
	Scenery() = default;
	///TODO: add a special constructor, once fields are set in stone
	///Scenery(
	///TODO: think how exactly the QImage will be created and if the interface is sufficient
	QImage	display();

	///TODO: think about helper functions e.g.: shuffle
	///TODO: more fields needed for the music
	///TODO: should it be tied with event instead? What should display the text? Scenery or Scene? How do we sync?
	///TODO: should this return a pointer to MediaPlayer or play one that Asset has?
	void	playMusic();

	void	run() 
	{ 
		display(); 
		playMusic(); 
	};

private:
	///TODO: comment this
	QVector<QString>		objectNames;
	///TODO: comment this
	QVector<SceneryObject*>	objects;

	///TODO: comment this
	QVector<QString>		characterNames;
	///TODO: comment this
	QVector<Character*>		characters;

	///TODO: comment this
	QVector<QString>		musicNameS;
	///TODO: comment this
	QVector<MusicAsset*>	musicPlaylist;

	///TODO: serialization including all the objects
	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream)
	{

		dataStream;
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const
	{

		dataStream;
	}
};