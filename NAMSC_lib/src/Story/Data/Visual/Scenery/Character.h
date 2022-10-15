#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/AssetImage.h"
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
	//AssetLive2DAnim *idleLive2DAnim;
	//QString			currentLive2DAnimName;
	//AssetLive2DAnim *currentLive2DAnim;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream& dataStream);
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream& dataStream) const;
};