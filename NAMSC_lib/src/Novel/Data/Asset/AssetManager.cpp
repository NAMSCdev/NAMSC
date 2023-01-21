#include "Novel/Data/Asset/AssetManager.h"

#include "Helpers.h"

AssetManager& AssetManager::getInstance() noexcept
{
	static AssetManager assetManager;
	return assetManager;
}

const AssetAnimColor* AssetManager::getAssetAnimColor(const QString& name) const
{
	return NovelLib::Helpers::mapGet(colorAnims_, name, "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetAnimColor* AssetManager::getAssetAnimColor(const QString& name)
{
	return NovelLib::Helpers::mapGet(colorAnims_, name, "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

const AssetAnimMove* AssetManager::getAssetAnimMove(const QString& name) const
{
	return NovelLib::Helpers::mapGet(moveAnims_, name, "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetAnimMove* AssetManager::getAssetAnimMove(const QString& name)
{
	return NovelLib::Helpers::mapGet(moveAnims_, name, "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

const AssetAnimRotate* AssetManager::getAssetAnimRotate(const QString& name) const
{
	return NovelLib::Helpers::mapGet(rotateAnims_, name, "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetAnimRotate* AssetManager::getAssetAnimRotate(const QString& name)
{
	return NovelLib::Helpers::mapGet(rotateAnims_, name, "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

const AssetAnimScale* AssetManager::getAssetAnimScale(const QString& name) const
{
	return NovelLib::Helpers::mapGet(scaleAnims_, name, "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetAnimScale* AssetManager::getAssetAnimScale(const QString& name)
{
	return NovelLib::Helpers::mapGet(scaleAnims_, name, "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

const AssetImage* AssetManager::getAssetImageSceneryBackground(const QString& name) const
{
	return NovelLib::Helpers::mapGet(backgroundImages_, name, "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetImage* AssetManager::getAssetImageSceneryBackground(const QString& name)
{
	return NovelLib::Helpers::mapGet(backgroundImages_, name, "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

const AssetImage* AssetManager::getAssetImageSceneryObject(const QString& name) const
{
	return NovelLib::Helpers::mapGet(objectImages_, name, "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetImage* AssetManager::getAssetImageSceneryObject(const QString& name)
{
	return NovelLib::Helpers::mapGet(objectImages_, name, "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetAnimColor* AssetManager::addAssetAnimColor(const QString& name, uint size, uint pos, const QString& path)
{
	return NovelLib::Helpers::mapSet(colorAnims_, std::move(AssetAnimColor(name, size, pos, path)), "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetAnimScale* AssetManager::addAssetAnimMove(const QString& name, uint size, uint pos, const QString& path)
{
	return NovelLib::Helpers::mapSet(moveAnims_, std::move(AssetAnimScale(name, size, pos, path)), "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetAnimRotate* AssetManager::addAssetAnimRotate(const QString& name, uint size, uint pos, const QString& path)
{
	return NovelLib::Helpers::mapSet(rotateAnims_, std::move(AssetAnimRotate(name, size, pos, path)), "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetAnimScale* AssetManager::addAssetAnimScale(const QString& name, uint size, uint pos, const QString& path)
{
	return NovelLib::Helpers::mapSet(scaleAnims_, std::move(AssetAnimScale(name, size, pos, path)), "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetImage* AssetManager::addAssetImageSceneryBackground(const QString& name, uint size, uint pos, const QString& path)
{
	return NovelLib::Helpers::mapSet(backgroundImages_, std::move(AssetImage(name, size, pos, path)), "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetImage* AssetManager::addAssetImageSceneryObject(const QString& name, uint size, uint pos, const QString& path)
{
	return NovelLib::Helpers::mapSet(objectImages_, std::move(AssetImage(name, size, pos, path)), "Asset", NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetAnimColor* AssetManager::renameAssetAnimColor(const QString& oldName, const QString& newName)
{
	return NovelLib::Helpers::mapRename(colorAnims_, oldName, newName, "Asset", NovelLib::ErrorType::General, NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetAnimScale* AssetManager::renameAssetAnimMove(const QString& oldName, const QString& newName)
{
	return NovelLib::Helpers::mapRename(moveAnims_, oldName, newName, "Asset", NovelLib::ErrorType::General, NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetAnimRotate* AssetManager::renameAssetAnimRotate(const QString& oldName, const QString& newName)
{
	return NovelLib::Helpers::mapRename(rotateAnims_, oldName, newName, "Asset", NovelLib::ErrorType::General, NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetAnimScale* AssetManager::renameAssetAnimScale(const QString& oldName, const QString& newName)
{
	return NovelLib::Helpers::mapRename(scaleAnims_, oldName, newName, "Asset", NovelLib::ErrorType::General, NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetImage* AssetManager::renameAssetImageSceneryBackground(const QString& oldName, const QString& newName)
{
	return NovelLib::Helpers::mapRename(backgroundImages_, oldName, newName, "Asset", NovelLib::ErrorType::General, NovelLib::ErrorType::General, "", "", "", "", false);
}

AssetImage* AssetManager::renameAssetImageSceneryObject(const QString& oldName, const QString& newName)
{
	return NovelLib::Helpers::mapRename(objectImages_, oldName, newName, "Asset", NovelLib::ErrorType::General, NovelLib::ErrorType::General, "", "", "", "", false);
}

void AssetManager::correctAssets(QString name, uint oldSize, uint size, uint pos, QString path)
{
}