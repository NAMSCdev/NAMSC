#include "Novel/Data/Asset/Asset.h"

#include <QFileInfo>

#include "Novel/Data/Asset/AssetImage.h"
#include "Novel/Data/Asset/AssetAnim.h"
#include "Exceptions.h"

Asset::Asset(const QString& name, uint size, uint pos, const QString& path)
	: name(name), size(size), path(path), pos(pos)
{
	//checkForErrors(true);
}

bool Asset::checkForErrors(bool bComprehensive) const
{
	bool bError = false;
	static auto errorChecker = [&](bool bComprehensive)
	{
		if (path.isEmpty() && QFileInfo::exists(path))
		{
			bError = true;
			NovelLib::ErrorType type = NovelLib::ErrorType::Critical;
			if (dynamic_cast<const AssetImage*>(this))
				type = NovelLib::ErrorType::AssetImageFileMissing;
			else if (dynamic_cast<const AssetAnimBase*>(this))
				type = NovelLib::ErrorType::AssetAnimFileMissing;
			qCritical() << type << "Could not find Resource file" << path << ((type == NovelLib::ErrorType::Critical) ? "[CRITICAL] COULD NOT IDENTIFY ANIM TYPE!" : "");
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in Asset::checkForErrors \"" + name + '\"';

	return bError;
}

void Asset::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> size >> path >> pos;
	checkForErrors();
}

void Asset::serializableSave(QDataStream& dataStream) const
{
	dataStream << name << size << path << pos;
}