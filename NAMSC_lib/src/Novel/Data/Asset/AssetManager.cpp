#include "Novel/Data/Asset/AssetManager.h"

#include <QFile>

AssetManager& AssetManager::getInstance() noexcept
{
	static AssetManager assetManager;
	return assetManager;
};

void AssetManager::loadAllAssetsDefinitions()
{
	loadDefinitions("Assets/colorAnims.bin",		colorAnims_);
	loadDefinitions("Assets/moveAnims.bin",			moveAnims_);
	loadDefinitions("Assets/rotateAnims.bin",		rotateAnims_);
	loadDefinitions("Assets/scaleAnims.bin",		scaleAnims_);
	loadDefinitions("Assets/backgroundImages.bin",	backgroundImages_);
	loadDefinitions("Assets/objectImages.bin",		objectImages_);
}

void AssetManager::saveAllAssetsDefinitions()
{
	saveDefinitions("Assets/colorAnims.bin",		colorAnims_);
	saveDefinitions("Assets/moveAnims.bin",			moveAnims_);
	saveDefinitions("Assets/rotateAnims.bin",		rotateAnims_);
	saveDefinitions("Assets/scaleAnims.bin",		scaleAnims_);
	saveDefinitions("Assets/backgroundImages.bin",	backgroundImages_);
	saveDefinitions("Assets/objectImages.bin",		objectImages_);
}

AssetAnimColor* AssetManager::getAssetAnimColor(const QString& assetAnimColorName) noexcept
{
	return getAsset<AssetAnimColor>(assetAnimColorName, colorAnims_);
}

AssetAnimMove* AssetManager::getAssetAnimMove(const QString& assetAnimMoveName) noexcept
{
	return getAsset<AssetAnimMove>(assetAnimMoveName, moveAnims_);
}

AssetAnimRotate* AssetManager::getAssetAnimRotate(const QString& assetAnimRotateName) noexcept
{
	return getAsset<AssetAnimRotate>(assetAnimRotateName, rotateAnims_);
}

AssetAnimScale* AssetManager::getAssetAnimScale(const QString& assetAnimScaleName) noexcept
{
	return getAsset<AssetAnimScale>(assetAnimScaleName, scaleAnims_);
}

AssetImage* AssetManager::getAssetImageSceneryBackground(const QString& assetImageName) noexcept
{
	return getAsset<AssetImage>(assetImageName, backgroundImages_);
}

AssetImage* AssetManager::getAssetImageSceneryObject(const QString& assetImageName) noexcept
{
	return getAsset<AssetImage>(assetImageName, objectImages_);
}

void AssetManager::insertAssetAnimColor(const QString& assetAnimColor, uint size, uint pos, const QString& path) 
{
	insertAsset<AssetAnimColor>(assetAnimColor, size, pos, path, colorAnims_);
}

void AssetManager::insertAssetAnimMove(const QString& name, uint size, uint pos, const QString& path)
{
	insertAsset<AssetAnimMove>(name, size, pos, path, moveAnims_);
}

void AssetManager::insertAssetAnimRotate(const QString& name, uint size, uint pos, const QString& path)
{
	insertAsset<AssetAnimRotate>(name, size, pos, path, rotateAnims_);
}

void AssetManager::insertAssetAnimScale(const QString& name, uint size, uint pos, const QString& path)
{
	insertAsset<AssetAnimScale>(name, size, pos, path, scaleAnims_);
}

void AssetManager::insertAssetImageSceneryBackground(const QString& name, uint size, uint pos, const QString& path)
{
	insertAsset<AssetImage>(name, size, pos, path, backgroundImages_);
}

void AssetManager::insertAssetImageSceneryObject(const QString& name, uint size, uint pos, const QString& path)
{
	insertAsset<AssetImage>(name, size, pos, path, objectImages_);
}

void AssetManager::saveAllAssets()
{
	//for (std::pair<const QString, AssetAnimColor>& asset : colorAnims_)
	//	asset.second.save();
	//for (std::pair<const QString, AssetAnimMove>& asset : moveAnims_)
	//	asset.second.save();
	//for (std::pair<const QString, AssetAnimRotate>& asset : rotateAnims_)
	//	asset.second.save();
	//for (std::pair<const QString, AssetAnimScale>& asset : scaleAnims_)
	//	asset.second.save();
	//for (std::pair<const QString, AssetImage>& asset : backgroundImages_)
	//	asset.second.save();
	//for (std::pair<const QString, AssetImage>& asset : objectImages_)
	//	asset.second.save();
}

void AssetManager::correctAssets(QString name, uint oldSize, uint size, uint pos, QString path)
{
}

template<typename AssetType>
const AssetType* AssetManager::getAsset(const QString& name, const std::unordered_map<QString, AssetType>& map) const noexcept
{
	if (map.contains(name))
		return &map[name];
	return nullptr;
}

template<typename AssetType>
AssetType* AssetManager::getAsset(const QString& name, std::unordered_map<QString, AssetType>& map) noexcept
{
	if (map.contains(name))
		return &map[name];
	return nullptr;
}

template<typename AssetType>
void AssetManager::insertAsset(const QString& name, uint size, uint pos, const QString& path, std::unordered_map<QString, AssetType>& map)
{
	if (map.contains(name))
		qCritical() << this << NovelLib::ErrorType::General << "An Asset with name (object's name: \"" << name << "\") already exists!";
	map.insert(std::make_pair(name, std::move(AssetType(name, size, pos, path))));
}

template<typename AssetType>
void AssetManager::loadDefinitions(const QString& path, std::unordered_map<QString, AssetType>& map)
{
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly))
	{
		qCritical() << this << NovelLib::ErrorType::General << "Could not open the File \"" << path << "\": ";
		return;
	}
	try
	{
		QDataStream dataStream(&file);
		while (!dataStream.atEnd())
		{
			AssetType asset;
			dataStream >> asset;
			map.insert(std::make_pair<QString, AssetType>(QString(asset.name), std::move(asset)));
		}
	}
	catch (QException exception)
	{
		qCritical() << this << NovelLib::ErrorType::General << "Could not read from File \"" << path << "\": " << exception.what();
	}
}

template<typename AssetType>
void AssetManager::saveDefinitions(const QString& path, std::unordered_map<QString, AssetType>& map)
{
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		qCritical() << this << NovelLib::ErrorType::General << "Couldn't open \"" << path << "\" File";
		return;
	}
	try
	{
		QDataStream dataStream(&file);
		//for (const std::pair<const QString, AssetType>& asset : map)
		//	dataStream << asset.second;
	}
	catch (QException& exception)
	{
		qCritical() << this << NovelLib::ErrorType::General << "Could not write to File \"" << path << "\": " << exception.what();
	}
}