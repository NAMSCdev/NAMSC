#pragma once
#include "Story/Data/Asset/Type/FontAsset.h"
#include "Story/Data/Asset/Type/MusicAsset.h"
#include "Story/Data/Asset/Type/ImageAsset.h"
#include "Story/Data/Asset/Type/SoundAsset.h"

///Loads and unloads Assets that are not associated directly with any of the SceneryObject, but into/from memory
///[optional todo] Create some smart algorithm that will use Visitors to see if an Asset will be loaded soon and prefetch it dNameng a Chapter load
class AssetManager
{
public:
	static AssetManager& getInstance()
	{
		static AssetManager instance;
		return instance;
	};
	AssetManager() = default;
	AssetManager(AssetManager const&)	= delete;
	void operator=(AssetManager const&)	= delete;

	///Loads all Asset objects without their resources
	void		loadAllAssetsDefinitions();

	///Find by `name` a FontAsset
	///\param name The searched FontAsset
	///\exception CriticalException Failure finding the FontAsset
	///\return Pointer to the found FontAsset
	FontAsset*	findFontAsset(const QString &name)
	{ 
		return findInArray<FontAsset>(name, fonts);
	}

	///Find by `name` a MusicAsset
	///\param name The searched MusicAsset
	///\exception CriticalException Failure finding the MusicAsset
	///\return Pointer to the found MusicAsset
	MusicAsset*	findMusicAsset(const QString &name)
	{ 
		return findInArray<MusicAsset>(name, music);
	}

	///Find by `name` a SoundAsset
	///\param name The searched SoundAsset
	///\exception CriticalException Failure finding the SoundAsset
	///\return Pointer to the found SoundAsset
	SoundAsset*	findSoundAsset(const QString &name)	
	{ 
		return findInArray<SoundAsset>(name, sounds);
	}

	///Finds by `name` an ImageAsset that is supposed to be used as **background** for Scenery
	///\param name The searched **background** ImageAsset
	///\exception CriticalException failure finding the **background** ImageAsset
	///\return Pointer to the found ImageAsset
	ImageAsset*	findSceneryBackgroundImageAsset(const QString &name)
	{ 
		return findInArray<ImageAsset>(name, sceneryBackgroundImages);
	}

	///Finds by `name` an ImageAsset that is supposed to be a SceneryObject **sprite** or part of it
	///\param name The searched **sprite** ImageAsset
	///\exception CriticalException failure finding the **sprite** ImageAsset
	///\return Pointer to the found ImageAsset
	ImageAsset*	findSceneryObjectImageAsset(const QString &name)
	{ 
		return findInArray<ImageAsset>(name, sceneryObjectImages);
	}

	///Finds by `name` an AnimAsset that animates a SceneryObject with a **movement** animation
	///\param name The searched **movement** AnimAsset
	///\exception CriticalException failure finding the **movement** AnimAsset
	///\return Pointer to the found AnimAsset
	AnimAsset<AnimNodeDouble2D>* findAnimAssetMove(const QString &name)
	{ 
		return findInArray<AnimAsset<AnimNodeDouble2D>>(name, moveAnims);
	}

	///Finds by `name` an AnimAsset that animates a SceneryObject with a **scaling** animation
	///\param name The searched **scaling** AnimAsset
	///\exception CriticalException failure finding the **scaling** AnimAsset
	///\return Pointer to the found AnimAsset
	AnimAsset<AnimNodeDouble2D>* findAnimAssetScale(const QString &name)
	{ 
		return findInArray<AnimAsset<AnimNodeDouble2D>>(name, scaleAnims);
	}

	///Finds by `name` an AnimAsset that animates a SceneryObject with a **rotation** animation
	///\param name The searched **rotation** AnimAsset
	///\exception CriticalException failure finding the **rotation** AnimAsset
	///\return Pointer to the found AnimAsset
	AnimAsset<AnimNodeDouble1D>* findAnimAssetRotate(const QString& name)
	{
		return findInArray<AnimAsset<AnimNodeDouble1D>>(name, rotateAnims);
	}

	///Finds by `name` an AnimAsset that animates a SceneryObject with a **color** animation
	///\param name The searched **color** AnimAsset
	///\exception CriticalException failure finding the **color** AnimAsset
	///\return Pointer to the found AnimAsset
	AnimAsset<AnimNodeDouble4D>* findAnimAssetColor(const QString& name)
	{
		return findInArray<AnimAsset<AnimNodeDouble4D>>(name, colorAnims);
	}

	//todo: lepszy opis
	///Insert FontAsset
	void insertFontAsset(const QString &name, const QString &location, unsigned pos)
	{
		insertAsset<FontAsset>(name, location, pos, fonts);
	}

	//todo: lepszy opis
	///Insert MusicAsset
	bool insertMusicAsset(const QString &name, const QString &location, unsigned pos)
	{
		insertAsset<MusicAsset>(name, location, pos, music);
	}

	//todo: lepszy opis
	///Insert SoundAsset
	bool insertSoundAsset(const QString &name, const QString &location, unsigned pos)
	{
		insertAsset<SoundAsset>(name, location, pos, sounds);
	}

	//todo: lepszy opis
	///Insert SceneryBackgroundImageAsset
	bool insertSceneryBackgroundImageAsset(const QString &name, const QString &location, unsigned pos)
	{
		insertAsset<ImageAsset>(name, location, pos, sceneryBackgroundImages);
	}

	//todo: lepszy opis
	///Insert SceneryObjectImageAsset
	bool insertSceneryObjectImageAsset(const QString &name, const QString &location, unsigned pos)
	{
		insertAsset<ImageAsset>(name, location, pos, sceneryObjectImages);
	}

	//todo: lepszy opis
	bool insertMoveAnimAsset(const QString& name, const QString& location, unsigned pos)
	{
		insertAsset<AnimAsset<AnimNodeDouble2D>>(name, location, pos, moveAnims);
	}

	//todo: lepszy opis
	bool insertAnimAsset(const QString& name, const QString& location, unsigned pos)
	{
		insertAsset<AnimAsset<AnimNodeDouble2D>>(name, location, pos, scaleAnims);
	}

	//todo: lepszy opis
	bool insertScaleAnimAsset(const QString& name, const QString& location, unsigned pos)
	{
		insertAsset<AnimAsset<AnimNodeDouble1D>>(name, location, pos, rotateAnims);
	}

	//todo: lepszy opis
	bool insertColorAnimAsset(const QString& name, const QString& location, unsigned pos)
	{
		insertAsset<AnimAsset<AnimNodeDouble4D>>(name, location, pos, colorAnims);
	}


private:
	template<class Type>
	void insertAsset(const QString &name, const QString &location, unsigned pos, QVector<Type> &vector)
	{
		if (std::find(vector.begin(), vector.end(), name) != vector.end())
			error("An Asset with name \"" + name "\" already exists!");
		vector.emplace_back(name, location, pos);
	}

	///All the available Animations for moving SeceneryObjects around 
	QVector<AnimAsset<AnimNodeDouble2D>> moveAnims;

	///All the available Animations for rotate SeceneryObjects
	QVector<AnimAsset<AnimNodeDouble1D>> rotateAnims;

	///All the available Animations for scaling SeceneryObjects
	QVector<AnimAsset<AnimNodeDouble2D>> scaleAnims;

	///All the available Animations for changing SeceneryObjects' colors
	QVector<AnimAsset<AnimNodeDouble4D>> colorAnims;

	///All the available Fonts
	QVector<FontAsset>	fonts;

	///All the available Music
	QVector<MusicAsset>	music;

	///All the available Sounds
	QVector<SoundAsset>	sounds;

	///All the available background Images for the Scenery
	QVector<ImageAsset>	sceneryBackgroundImages;

	///All the available Images for SceneryObjects
	QVector<ImageAsset>	sceneryObjectImages;
};

