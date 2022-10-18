#pragma once
#include "Global.h"

#include "Novel/Data/Asset/Type/AssetImage.h"
#include "Novel/Data/Asset/AssetManager.h"

#include "Novel/Data/Visual/Scenery/SceneryObject.h"

///Represents a Character in tbe Novel
class Character final : public SceneryObject
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Character&);
	friend QDataStream& operator<<(QDataStream&, const Character&);
public:
	Character() = default;
	Character(QString&& defaultVoiceName);
	Character(const Character& obj) { *this = obj; }
	Character& operator=(const Character& obj)
	{
		if (this == &obj) return *this;

		SceneryObject::operator=(obj);
		defaultVoiceName = obj.defaultVoiceName;
		defaultVoice     = obj.defaultVoice;

		return *this;
	}


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