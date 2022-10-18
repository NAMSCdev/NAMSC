#pragma once
#include "Novel/Data/Asset/Asset.h"
#include "Novel/Data/Asset/Type/AssetFont.h"

//-----ASSET

void Asset::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> location >> pos >> bExternal;
}

void Asset::serializableSave(QDataStream& dataStream) const
{
	dataStream << getType() << name << location << pos << bExternal;
}

void AssetFont::serializableLoad(QDataStream& dataStream)
{
	dataStream >> fontSize >> systemFont;
}
///Saving an object to a binary file
void AssetFont::serializableSave(QDataStream& dataStream) const
{
	dataStream << fontSize << systemFont;
}