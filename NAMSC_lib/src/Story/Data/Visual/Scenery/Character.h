#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/ImageAsset.h"
#include "Story/Data/Asset/AssetManager.h"

#include "Story/Data/Text/Voice.h"

#include "Story/Data/Visual/Scenery/SceneryObject.h"

//This hasn't been thought through yet. It is very WIP
//TODO: comment this
class Character : public SceneryObject
{
	//Friends for serialization
	friend QIODevice &operator>>(QIODevice &device, Character &t);
	friend QIODevice &operator<<(QIODevice &device, const Character &t);
public:
	Character() = default;
	Character(QString &&defaultVoiceName, QString idleLive2DAnimURI = "") : 
		defaultVoiceName(move(defaultVoiceName)), idleLive2DAnimURI(idleLive2DAnimURI) {};
	//TODO: comment this
	void			playLive2DAnim	(QString Live2DAnimURI);
	
public:
	//TODO: comment this
	QString			defaultVoiceName;
	Voice			*defaultVoice;

	//TODO: comment this
	//[optional]
	QString			idleLive2DAnimURI;
	Live2DAnimAsset *idleLive2DAnim;
	QString			currentLive2DAnimURI;
	Live2DAnimAsset *currentLive2DAnim;

	//TODO: serialization
	//---SERIALIZATION---
	//Loading an object from a binary file
	virtual void serializableLoad(QIODevice &ar)
	{
		SceneryObject::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream;
	}
	//Saving an object to a binary file
	virtual void serializableSave(QIODevice &ar) const
	{
		SceneryObject::serializableSave(ar);
		QDataStream dataStream(&ar);
	}
};