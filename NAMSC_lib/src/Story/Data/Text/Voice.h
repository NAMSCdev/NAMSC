#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/FontAsset.h"
#include "Story/Data/Asset/AssetManager.h"

//This hasn't been fully thought through yet. It is WIP
//Tells how the text should be displayed 
//[optional] ...And if there should be any lip syncing done (if the character is Live2d compatible)
class Voice
{
	//Friends for serialization
	friend QIODevice &operator>>(QIODevice &device, Voice &t);
	friend QIODevice &operator<<(QIODevice &device, const Voice &t);
public:
	//If a Character is compatible with Live2d, we can animate its lips while they are talking
	enum class LipSyncType
	{
		None,
		Full,
		Static		//Open mouth while talking, but no animation
	};

	Voice() = default;
	Voice(LipSyncType lipSync, QString &&font, unsigned fontSize, Qt::AlignmentFlag alignment)
		: lipSync(lipSync), font(move(font)), fontSize(fontSize), alignment(alignment)		{ fontAsset = AssetManager::findFontAsset(font); }

private:
	//If a Character is compatible with Live2d, we can animate its lips while they are talking
	//Possible values:
	//None
	//Full
	//Static
	LipSyncType			lipSync		= LipSyncType::Full;

	//Font used to display this text spoken by this Voice
	QString				font;
	FontAsset			*fontAsset;

	//Font size used to display this text spoken by this Voice
	unsigned			fontSize;

	//Alignment of the text
	//TODO: add default and to constructor too
	Qt::AlignmentFlag	alignment;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar)
	{
		QDataStream dataStream(&ar);
		dataStream >> lipSync >> font >> fontSize >> alignment;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const
	{
		QDataStream dataStream(&ar);
		dataStream << SerializationID::Voice << lipSync << font << fontSize << alignment;
	}
};