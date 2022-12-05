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

bool AssetManager::insertAssetAnimColor(const QString& assetAnimColor, uint size, uint pos, const QString& path) 
{
	insertAsset<AssetAnimColor>(assetAnimColor, size, pos, path, colorAnims_);
}

bool AssetManager::insertAssetAnimMove(const QString& name, uint size, uint pos, const QString& path)
{
	insertAsset<AssetAnimMove>(name, size, pos, path, moveAnims_);
}

bool AssetManager::insertAssetAnimRotate(const QString& name, uint size, uint pos, const QString& path)
{
	insertAsset<AssetAnimRotate>(name, size, pos, path, rotateAnims_);
}

bool AssetManager::insertAssetAnimScale(const QString& name, uint size, uint pos, const QString& path)
{
	insertAsset<AssetAnimScale>(name, size, pos, path, scaleAnims_);
}

bool AssetManager::insertSceneryBackgroundAssetImage(const QString& name, uint size, uint pos, const QString& path)
{
	insertAsset<AssetImage>(name, size, pos, path, backgroundImages_);
}

bool AssetManager::insertSceneryObjectAssetImage(const QString& name, uint size, uint pos, const QString& path)
{
	insertAsset<AssetImage>(name, size, pos, path, objectImages_);
}

void AssetManager::saveAllAssets()
{
	for (Asset& asset : colorAnims_)
		asset.save();
	for (Asset& asset : moveAnims_)
		asset.save();
	for (Asset& asset : rotateAnims_)
		asset.save();
	for (Asset& asset : scaleAnims_)
		asset.save();
	for (Asset& asset : backgroundImages_)
		asset.save();
	for (Asset& asset : objectImages_)
		asset.save();
}

void AssetManager::correctAssets(QString name, uint oldSize, uint size, uint pos, QString path)
{
}

template<typename AssetType>
AssetType* AssetManager::getAsset(const QString& name, QHash<QString, AssetType>& map) noexcept
{
	if (map.contains(name))
		return &map[name];
	return nullptr;
}

template<typename AssetType>
void AssetManager::insertAsset(const QString& name, uint size, uint pos, const QString& path, QHash<QString, AssetType>& map)
{
	if (map.contains(name))
		qCritical() << this << NovelLib::ErrorType::General << "An Asset with name (object's name: \"" << name << "\") already exists!";
	map.emplace(name, size, pos, path);
}

template<typename AssetType>
void AssetManager::loadDefinitions(const QString& path, QHash<QString, AssetType>& map)
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
			map[asset.name] = std::move(asset);
		}
	}
	catch (QException exception)
	{
		qCritical() << this << NovelLib::ErrorType::General << "Could not read from File \"" << path << "\": " << exception.what();
	}
}

template<typename AssetType>
void AssetManager::saveDefinitions(const QString& path, QHash<QString, AssetType>& map)
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
		for (const AssetType& asset : map)
			dataStream << asset;
	}
	catch (QException& exception)
	{
		qCritical() << this << NovelLib::ErrorType::General << "Could not write to File \"" << path << "\": " << exception.what();
	}
}