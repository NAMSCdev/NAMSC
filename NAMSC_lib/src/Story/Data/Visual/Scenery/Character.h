#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/ImageAsset.h"
#include "Story/Data/Asset/AssetManager.h"

#include "Story/Data/Text/Voice.h"

#include "Story/Data/Visual/Scenery/SceneryObject.h"

///This hasn't been thought through yet. It is very WIP
///TODO: comment this
class Character final : public SceneryObject
{
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Character&);
	friend QDataStream& operator<<(QDataStream&, const Character&);
public:
	Character() = default;
	Character(QString &&defaultVoiceName, QString idleLive2DAnimName = "") : 
		defaultVoiceName(move(defaultVoiceName)), idleLive2DAnimName(idleLive2DAnimName) {};
	///TODO: comment this
	void			playLive2DAnim(QString Live2DAnimName);
	
private:
	///TODO: comment this
	QString			defaultVoiceName;
	Voice			*defaultVoice;

	///TODO: comment this
	///[optional]
	QString			idleLive2DAnimName;
	Live2DAnimAsset *idleLive2DAnim;
	QString			currentLive2DAnimName;
	Live2DAnimAsset *currentLive2DAnim;

	///TODO: serialization
	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream)
	{
		SceneryObject::serializableLoad(dataStream);
		dataStream;
	}
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const
	{
		SceneryObject::serializableSave(dataStream);

	}
};