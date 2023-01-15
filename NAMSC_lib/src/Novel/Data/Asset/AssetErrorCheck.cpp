#include "Novel/Data/Asset/AssetImage.h"
#include "Novel/Data/Asset/AssetAnim.h"

#include <QFileInfo>

bool Asset::errorCheck(bool bComprehensive) const
{
	bool bError = false;
	auto errorChecker = [this](bool bComprehensive)
	{
		if (path.isEmpty() && QFileInfo::exists(path))
		{
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
		qDebug() << "Error occurred in Asset::errorCheck \"" + name + '\"';

	return bError;
}

template<typename AnimNode>
bool AssetAnim<AnimNode>::errorCheck(bool bComprehensive) const
{
	bool bError = Asset::errorCheck(bComprehensive);

	auto errorChecker = [this](bool bComprehensive)
	{
		//todo: check timeStamps
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in AssetAnim::errorCheck \"" + name + '\"';

	return bError;
}

bool AssetImage::errorCheck(bool bComprehensive) const
{
	bool bError = Asset::errorCheck(bComprehensive);

	auto errorChecker = [this](bool bComprehensive)
	{
		if (bComprehensive)
		{
			//todo: check lastError?
			if (!isLoaded())
			{
				AssetImage fake(name, size, pos, path, false);
				fake.load();
				fake.unload();
			}
			//todo: compare lastError?
		}

		return false;
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in AssetImage::errorCheck \"" + name + '\"';

	return bError;
}

#include "Novel/Data/Asset/AssetAnimInstances.h"