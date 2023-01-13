#include "Novel/Data/Asset/Asset.h"

#include <QFileInfo>

#include "Novel/Data/Asset/AssetImage.h"
#include "Novel/Data/Asset/AssetAnim.h"
#include "Exceptions.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

Asset::Asset(const QString& name, uint size, uint pos, const QString& path)
	: name(name), 
	size(size), 
	path(path), 
	pos(pos)
{
}

Asset::~Asset() = default;

void Asset::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> size >> path >> pos;
	errorCheck();
}

void Asset::serializableSave(QDataStream& dataStream) const
{
	dataStream << name << size << path << pos;
}

//  MEMBER_FIELD_SECTION_CHANGE END