#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/FontAsset.h"
#include "Story/Data/Asset/Type/MusicAsset.h"
#include "Story/Data/Asset/Type/SceneryBackgroundImageAsset.h"
#include "Story/Data/Asset/Type/SceneryObjectPartImageAsset.h"
#include "Story/Data/Asset/Type/SoundAsset.h"

///Loads and unloads Assets that are not associated directly with any of the SceneryObject, but into/from memory
///[optional todo] Create some smart algorithm that will use Visitators to see if an Asset will be loaded soon and prefetch it dNameng a Catalogue load
class AssetManager
{
public:
	AssetManager() = delete;

	///Loads all Asset objects without their resources
	static void		loadAllAssetsDefinitions			();

	///Find FontAsset by name
	static FontAsset*		findFontAsset		(const QString &name)		{ return &(*std::find(fonts.begin(), fonts.end(), name)); }

	///Find MusicAsset by name
	static MusicAsset*		findMusicAsset		(const QString &name)		{ return &(*std::find(music.begin(), music.end(), name)); }

	///Find SoundAsset by name
	static SoundAsset*		findSoundAsset		(const QString &name)		{ return &(*std::find(sounds.begin(), sounds.end(), name)); }

	///Find SceneryBackgroundImageAsset by name
	static SceneryBackgroundImageAsset*		findSceneryBackgroundImageAsset		(const QString &name)		{ return &(*std::find(backgroundImages.begin(), backgroundImages.end(), name)); }

	///Find SceneryObjectPartImageAsset by name
	static SceneryObjectPartImageAsset*		findSceneryObjectPartImageAsset		(const QString &name)		{ return &(*std::find(sceneryObjectPartImages.begin(), sceneryObjectPartImages.end(), name)); }

	///Insert FontAsset
	static bool insertFontAsset		(const QString &name, const QString &location, unsigned pos)
	{
		if (std::find(fonts.begin(), fonts.end(), name) != fonts.end())
		{
			///TODO: exception
			return false;
		}
		fonts.emplace_back(name, location, pos);
		return true;
	}

	///Insert MusicAsset by name
	static bool insertMusicAsset			(const QString &name, const QString &location, unsigned pos)
	{
		if (std::find(music.begin(), music.end(), name) != music.end())
		{
			///TODO: exception
			return false;
		}
		music.emplace_back(name, location, pos);
		return true;
	}

	///Insert SoundAsset by name
	static bool insertSoundAsset			(const QString &name, const QString &location, unsigned pos)
	{
		if (std::find(sounds.begin(), sounds.end(), name) != sounds.end())
		{
			///TODO: exception
			return false;
		}
		sounds.emplace_back(name, location, pos);
		return true;
	}

	///Insert SceneryBackgroundImageAsset
	static bool insertSceneryBackgroundImageAsset	(const QString &name, const QString &location, unsigned pos)
	{
		if (std::find(backgroundImages.begin(), backgroundImages.end(), name) != backgroundImages.end())
		{
			///TODO: exception
			return false;
		}
		backgroundImages.emplace_back(name, location, pos);
		return true;
	}
	///Insert SceneryObjectPartImageAsset
	static bool insertSceneryObjectPartImageAsset	(const QString &name, const QString &location, unsigned pos)
	{
		if (std::find(sceneryObjectPartImages.begin(), sceneryObjectPartImages.end(), name) != sceneryObjectPartImages.end())
		{
			///TODO: exception
			return false;
		}
		sceneryObjectPartImages.emplace_back(name, location, pos);
		return true;
	}

protected:
	///All the available Fonts
	static QVector<FontAsset>			fonts;

	///All the available Music
	static QVector<MusicAsset>			music;

	///All the available Sounds
	static QVector<SoundAsset>			sounds;

	///All the available background Images
	static QVector<SceneryBackgroundImageAsset>	backgroundImages;

	///All the available Images for SceneryObjects' parts
	static QVector<SceneryObjectPartImageAsset>	sceneryObjectPartImages;
};

