#include "Novel/Data/Asset/AssetManager.h"

#include "Helpers.h"

AssetManager& AssetManager::getInstance() noexcept
{
	static AssetManager assetManager;
	return assetManager;
}

AssetAnimColor* AssetManager::getAssetAnimColor(const QString& assetAnimColorName)
{
	return NovelLib::getFromNamedMap(colorAnims_, assetAnimColorName, "Asset", NovelLib::ErrorType::General, false);
}

AssetAnimMove* AssetManager::getAssetAnimMove(const QString& assetAnimMoveName)
{
	return NovelLib::getFromNamedMap(moveAnims_, assetAnimMoveName, "Asset", NovelLib::ErrorType::General, false);
}

AssetAnimRotate* AssetManager::getAssetAnimRotate(const QString& assetAnimRotateName)
{
	return NovelLib::getFromNamedMap(rotateAnims_, assetAnimRotateName, "Asset", NovelLib::ErrorType::General, false);
}

AssetAnimScale* AssetManager::getAssetAnimScale(const QString& assetAnimScaleName)
{
	return NovelLib::getFromNamedMap(scaleAnims_, assetAnimScaleName, "Asset", NovelLib::ErrorType::General, false);
}

AssetImage* AssetManager::getAssetImageSceneryBackground(const QString& assetImageName)
{
	return NovelLib::getFromNamedMap(backgroundImages_, assetImageName, "Asset", NovelLib::ErrorType::General, false);
}

AssetImage* AssetManager::getAssetImageSceneryObject(const QString& assetImageName)
{
	return NovelLib::getFromNamedMap(objectImages_, assetImageName, "Asset", NovelLib::ErrorType::General, false);
}

AssetAnimColor* AssetManager::addAssetAnimColor(const QString& name, uint size, uint pos, const QString& path)
{
	return NovelLib::addToNamedMap(colorAnims_, name, std::move(AssetAnimColor(name, size, pos, path)), "Asset", NovelLib::ErrorType::General, false);
}

AssetAnimScale* AssetManager::addAssetAnimMove(const QString& name, uint size, uint pos, const QString& path)
{
	return NovelLib::addToNamedMap(moveAnims_, name, std::move(AssetAnimScale(name, size, pos, path)), "Asset", NovelLib::ErrorType::General, false);
}

AssetAnimRotate* AssetManager::addAssetAnimRotate(const QString& name, uint size, uint pos, const QString& path)
{
	return NovelLib::addToNamedMap(rotateAnims_, name, std::move(AssetAnimRotate(name, size, pos, path)), "Asset", NovelLib::ErrorType::General, false);
}

AssetAnimScale* AssetManager::addAssetAnimScale(const QString& name, uint size, uint pos, const QString& path)
{
	return NovelLib::addToNamedMap(scaleAnims_, name, std::move(AssetAnimScale(name, size, pos, path)), "Asset", NovelLib::ErrorType::General, false);
}

AssetImage* AssetManager::addAssetImageSceneryBackground(const QString& name, uint size, uint pos, const QString& path)
{
	return NovelLib::addToNamedMap(backgroundImages_, name, std::move(AssetImage(name, size, pos, path)), "Asset", NovelLib::ErrorType::General, false);
}

AssetImage* AssetManager::addAssetImageSceneryObject(const QString& name, uint size, uint pos, const QString& path)
{
	return NovelLib::addToNamedMap(objectImages_, name, std::move(AssetImage(name, size, pos, path)), "Asset", NovelLib::ErrorType::General, false);
}

AssetAnimColor* AssetManager::renameAssetAnimColor(const QString& oldName, const QString& newName)
{
	return NovelLib::renameInNamedMap(colorAnims_, oldName, newName, "Asset", NovelLib::ErrorType::General, NovelLib::ErrorType::General, false);
}

AssetAnimScale* AssetManager::renameAssetAnimMove(const QString& oldName, const QString& newName)
{
	return NovelLib::renameInNamedMap(moveAnims_, oldName, newName, "Asset", NovelLib::ErrorType::General, NovelLib::ErrorType::General, false);
}

AssetAnimRotate* AssetManager::renameAssetAnimRotate(const QString& oldName, const QString& newName)
{
	return NovelLib::renameInNamedMap(rotateAnims_, oldName, newName, "Asset", NovelLib::ErrorType::General, NovelLib::ErrorType::General, false);
}

AssetAnimScale* AssetManager::renameAssetAnimScale(const QString& oldName, const QString& newName)
{
	return NovelLib::renameInNamedMap(scaleAnims_, oldName, newName, "Asset", NovelLib::ErrorType::General, NovelLib::ErrorType::General, false);
}

AssetImage* AssetManager::renameAssetImageSceneryBackground(const QString& oldName, const QString& newName)
{
	return NovelLib::renameInNamedMap(backgroundImages_, oldName, newName, "Asset", NovelLib::ErrorType::General, NovelLib::ErrorType::General, false);
}

AssetImage* AssetManager::renameAssetImageSceneryObject(const QString& oldName, const QString& newName)
{
	return NovelLib::renameInNamedMap(objectImages_, oldName, newName, "Asset", NovelLib::ErrorType::General, NovelLib::ErrorType::General, false);
}

void AssetManager::correctAssets(QString name, uint oldSize, uint size, uint pos, QString path)
{
}