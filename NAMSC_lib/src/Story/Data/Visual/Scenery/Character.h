#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/ImageAsset.h"
#include "Story/Data/Asset/AssetManager.h"

#include "Story/Data/Visual/Scenery/SceneryObject.h"

///Represents a Character in game 
class Character final : public SceneryObject
{
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Character&);
	friend QDataStream& operator<<(QDataStream&, const Character&);
public:
	Character() = default;
	Character(QString&& defaultVoiceName);

private:
	///Name of the default Voice that will be assigned to EventSpeak 
	QString		defaultVoiceName;
	///Default Voice - formatting of the Text
	Voice		*defaultVoice;

	//QString			idleLive2DAnimName;
	//Live2DAnimAsset *idleLive2DAnim;
	//QString			currentLive2DAnimName;
	//Live2DAnimAsset *currentLive2DAnim;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream& dataStream);
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream& dataStream) const;
};