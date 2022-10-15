#pragma once
#include "Story/Data/Asset/Asset.h"

//-----ASSET

void Asset::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> location >> pos >> bExternal;
}

void Asset::serializableSave(QDataStream& dataStream) const
{
	dataStream << getType() << name << location << pos << bExternal;
}