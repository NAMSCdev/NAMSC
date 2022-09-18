#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/FontAsset.h"
#include "Story/Data/Asset/Type/MusicAsset.h"
#include "Story/Data/Asset/Type/SceneryBackgroundImageAsset.h"
#include "Story/Data/Asset/Type/SceneryObjectPartImageAsset.h"
#include "Story/Data/Asset/Type/SoundAsset.h"

//Loads and unloads Assets that are not associated directly with any of the SceneryObject, but into/from memory
//[optional todo] Create some smart algorithm that will use Visitators to see if an Asset will be loaded soon and prefetch it during a Catalogue load
class AssetManager
{
public:
	AssetManager() = delete;

	//Loads all Asset objects without their resources
	static void										loadAllAssetsDefinitions			();

	//Find FontAsset by URI
	static FontAsset*								findFontAsset						(const QString &URI)		{ return &(*std::find(fonts.begin(), fonts.end(), URI)); }

	//Find MusicAsset by URI
	static MusicAsset*								findMusicAsset						(const QString &URI)		{ return &(*std::find(music.begin(), music.end(), URI)); }

	//Find SoundAsset by URI
	static SoundAsset*								findSoundAsset						(const QString &URI)		{ return &(*std::find(sounds.begin(), sounds.end(), URI)); }

	//Find SceneryBackgroundImageAsset by URI
	static SceneryBackgroundImageAsset*				findSceneryBackgroundImageAsset		(const QString &URI)		{ return &(*std::find(backgroundImages.begin(), backgroundImages.end(), URI)); }

	//Find SceneryObjectPartImageAsset by URI
	static SceneryObjectPartImageAsset*				findSceneryObjectPartImageAsset		(const QString &URI)		{ return &(*std::find(sceneryObjectPartImages.begin(), sceneryObjectPartImages.end(), URI)); }

	//Insert FontAsset
	static bool insertFontAsset						(const QString &URI, const QString &location, unsigned pos)
	{
		if (std::find(fonts.begin(), fonts.end(), URI) != fonts.end())
		{
			//TODO: exception
			return false;
		}
		fonts.emplace_back(URI, location, pos);
		return true;
	}

	//Insert MusicAsset by URI
	static bool insertMusicAsset					(const QString &URI, const QString &location, unsigned pos)
	{
		if (std::find(music.begin(), music.end(), URI) != music.end())
		{
			//TODO: exception
			return false;
		}
		music.emplace_back(URI, location, pos);
		return true;
	}

	//Insert SoundAsset by URI
	static bool insertSoundAsset					(const QString &URI, const QString &location, unsigned pos)
	{
		if (std::find(sounds.begin(), sounds.end(), URI) != sounds.end())
		{
			//TODO: exception
			return false;
		}
		sounds.emplace_back(URI, location, pos);
		return true;
	}

	//Insert SceneryBackgroundImageAsset
	static bool insertSceneryBackgroundImageAsset	(const QString &URI, const QString &location, unsigned pos)
	{
		if (std::find(backgroundImages.begin(), backgroundImages.end(), URI) != backgroundImages.end())
		{
			//TODO: exception
			return false;
		}
		backgroundImages.emplace_back(URI, location, pos);
		return true;
	}
	//Insert SceneryObjectPartImageAsset
	static bool insertSceneryObjectPartImageAsset	(const QString &URI, const QString &location, unsigned pos)
	{
		if (std::find(sceneryObjectPartImages.begin(), sceneryObjectPartImages.end(), URI) != sceneryObjectPartImages.end())
		{
			//TODO: exception
			return false;
		}
		sceneryObjectPartImages.emplace_back(URI, location, pos);
		return true;
	}

protected:
	//All the available Fonts
	static std::vector<FontAsset>					fonts;

	//All the available Music
	static std::vector<MusicAsset>					music;

	//All the available Sounds
	static std::vector<SoundAsset>					sounds;

	//All the available background Images
	static std::vector<SceneryBackgroundImageAsset>	backgroundImages;

	//All the available Images for SceneryObjects' parts
	static std::vector<SceneryObjectPartImageAsset>	sceneryObjectPartImages;
};

