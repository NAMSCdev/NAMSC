#pragma once
#include "Novel/Data/Asset/Type/AssetLive2DAnim.h"
#include "Novel/Data/Asset/Type/AssetLive2DModel.h"
#include "Novel/Data/Asset/Type/AssetAnim.h"
#include "Novel/Data/Asset/Type/AssetFont.h"
#include "Novel/Data/Asset/Type/AssetMusic.h"
#include "Novel/Data/Asset/Type/AssetImage.h"
#include "Novel/Data/Asset/Type/AssetSound.h"

///Loads and unloads Assets that are not associated directly with any of the SceneryObject, but into/from memory
///[optional todo] Create some smart algorithm that will use Visitors to see if an Asset will be loaded soon and prefetch it dNameng a Chapter load
class AssetManager
{
public:
	static AssetManager& getInstance()
	{
		static AssetManager instance;
		return instance;
	}
	AssetManager() = default;
	AssetManager(AssetManager const&)	= delete;
	void operator=(AssetManager const&)	= delete;

	///Loads all Asset objects without their resources
	void loadAllAssetsDefinitions();

	//todo: lepszy opis
	///Insert AssetLive2DAnim
	void insertAssetLive2DAnim(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetLive2DAnim>(name, location, pos, live2DAnims);
	}

	//todo: lepszy opis
	///Insert AssetLive2DModel
	void insertAssetLive2DModels(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetLive2DModel>(name, location, pos, live2DModels);
	}

	///Find by `name` an AssetLive2DAnim
	///\param name The searched AssetLive2DAnim
	///\exception CriticalException Failure finding the AssetLive2DAnim
	///\return Pointer to the found AssetLive2DAnim
	AssetLive2DAnim* findAssetLive2DAnim(const QString& name)
	{
		return findInArray<AssetLive2DAnim>(name, live2DAnims);
	}
		
	///Find by `name` an AssetLive2DModel
	///\param name The searched AssetLive2DModel
	///\exception CriticalException Failure finding the AssetLive2DModel
	///\return Pointer to the found AssetLive2DModel
	AssetLive2DModel* findAssetLive2DModel(const QString& name)
	{
		return findInArray<AssetLive2DModel>(name, live2DModels);
	}

	///Find by `name` an AssetFont
	///\param name The searched AssetFont
	///\exception CriticalException Failure finding the AssetFont
	///\return Pointer to the found AssetFont
	AssetFont*	findAssetFont(const QString &name)
	{ 
		return findInArray<AssetFont>(name, fonts);
	}

	///Find by `name` an AssetMusic
	///\param name The searched AssetMusic
	///\exception CriticalException Failure finding the AssetMusic
	///\return Pointer to the found AssetMusic
	AssetMusic*	findAssetMusic(const QString &name)
	{ 
		return findInArray<AssetMusic>(name, music);
	}

	///Find by `name` an AssetSound
	///\param name The searched AssetSound
	///\exception CriticalException Failure finding the AssetSound
	///\return Pointer to the found AssetSound
	AssetSound*	findAssetSound(const QString &name)	
	{ 
		return findInArray<AssetSound>(name, sounds);
	}

	///Finds by `name` an AssetImage that is supposed to be used as **background** for Scenery
	///\param name The searched **background** AssetImage
	///\exception CriticalException failure finding the **background** AssetImage
	///\return Pointer to the found AssetImage
	AssetImage*	findSceneryBackgroundAssetImage(const QString &name)
	{ 
		return findInArray<AssetImage>(name, sceneryBackgroundImages);
	}

	///Finds by `name` an AssetImage that is supposed to be a SceneryObject **sprite** or part of it
	///\param name The searched **sprite** AssetImage
	///\exception CriticalException failure finding the **sprite** AssetImage
	///\return Pointer to the found AssetImage
	AssetImage*	findSceneryObjectAssetImage(const QString &name)
	{ 
		return findInArray<AssetImage>(name, sceneryObjectImages);
	}

	///Finds by `name` an AssetAnim that animates a SceneryObject with a **movement** animation
	///\param name The searched **movement** AssetAnim
	///\exception CriticalException failure finding the **movement** AssetAnim
	///\return Pointer to the found AssetAnim
	AssetAnim<AnimNodeDouble2D>* findAssetAnimMove(const QString &name)
	{ 
		return findInArray<AssetAnim<AnimNodeDouble2D>>(name, moveAnims);
	}

	///Finds by `name` an AssetAnim that animates a SceneryObject with a **scaling** animation
	///\param name The searched **scaling** AssetAnim
	///\exception CriticalException failure finding the **scaling** AssetAnim
	///\return Pointer to the found AssetAnim
	AssetAnim<AnimNodeDouble2D>* findAssetAnimScale(const QString &name)
	{ 
		return findInArray<AssetAnim<AnimNodeDouble2D>>(name, scaleAnims);
	}

	///Finds by `name` an AssetAnim that animates a SceneryObject with a **rotation** animation
	///\param name The searched **rotation** AssetAnim
	///\exception CriticalException failure finding the **rotation** AssetAnim
	///\return Pointer to the found AssetAnim
	AssetAnim<AnimNodeDouble1D>* findAssetAnimRotate(const QString& name)
	{
		return findInArray<AssetAnim<AnimNodeDouble1D>>(name, rotateAnims);
	}

	///Finds by `name` an AssetAnim that animates a SceneryObject with a **color** animation
	///\param name The searched **color** AssetAnim
	///\exception CriticalException failure finding the **color** AssetAnim
	///\return Pointer to the found AssetAnim
	AssetAnim<AnimNodeDouble4D>* findAssetAnimColor(const QString& name)
	{
		return findInArray<AssetAnim<AnimNodeDouble4D>>(name, colorAnims);
	}

	//todo: lepszy opis
	///Insert AssetLive2DAnim
	void insertAssetLive2DAnim(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetLive2DAnim>(name, location, pos, live2DAnims);
	}

	//todo: lepszy opis
	///Insert AssetLive2DModel
	void insertAssetFont(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetLive2DModel>(name, location, pos, live2DModels);
	}

	//todo: lepszy opis
	///Insert AssetFont
	void insertAssetFont(const QString &name, const QString &location, uint pos)
	{
		insertAsset<AssetFont>(name, location, pos, fonts);
	}

	//todo: lepszy opis
	///Insert AssetMusic
	bool insertAssetMusic(const QString &name, const QString &location, uint pos)
	{
		insertAsset<AssetMusic>(name, location, pos, music);
	}

	//todo: lepszy opis
	///Insert AssetSound
	bool insertAssetSound(const QString &name, const QString &location, uint pos)
	{
		insertAsset<AssetSound>(name, location, pos, sounds);
	}

	//todo: lepszy opis
	///Insert SceneryBackgroundAssetImage
	bool insertSceneryBackgroundAssetImage(const QString &name, const QString &location, uint pos)
	{
		insertAsset<AssetImage>(name, location, pos, sceneryBackgroundImages);
	}

	//todo: lepszy opis
	///Insert SceneryObjectAssetImage
	bool insertSceneryObjectAssetImage(const QString &name, const QString &location, uint pos)
	{
		insertAsset<AssetImage>(name, location, pos, sceneryObjectImages);
	}

	//todo: lepszy opis
	bool insertMoveAssetAnim(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetAnim<AnimNodeDouble2D>>(name, location, pos, moveAnims);
	}

	//todo: lepszy opis
	bool insertAssetAnim(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetAnim<AnimNodeDouble2D>>(name, location, pos, scaleAnims);
	}

	//todo: lepszy opis
	bool insertScaleAssetAnim(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetAnim<AnimNodeDouble1D>>(name, location, pos, rotateAnims);
	}

	//todo: lepszy opis
	bool insertColorAssetAnim(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetAnim<AnimNodeDouble4D>>(name, location, pos, colorAnims);
	}

private:
	template<class Type>
	void insertAsset(const QString &name, const QString &location, uint pos, QVector<Type> &vector)
	{
		if (std::find(vector.begin(), vector.end(), name) != vector.end())
			error("An Asset with name \"" + name "\" already exists!");
		vector.emplace_back(name, location, pos);
	}

	///[optional]All the available Live2D Animations for Characters
	QVector<AssetLive2DAnim> live2DAnims;

	///[optional]All the available Characters' Live2D models
	QVector<AssetLive2DModel> live2DModels;

	///All the available Animations for moving SeceneryObjects around 
	QVector<AssetAnim<AnimNodeDouble2D>> moveAnims;

	///All the available Animations for rotate SeceneryObjects
	QVector<AssetAnim<AnimNodeDouble1D>> rotateAnims;

	///All the available Animations for scaling SeceneryObjects
	QVector<AssetAnim<AnimNodeDouble2D>> scaleAnims;

	///All the available Animations for changing SeceneryObjects' colors
	QVector<AssetAnim<AnimNodeDouble4D>> colorAnims;

	///All the available Fonts
	QVector<AssetFont>	fonts;

	///All the available Music
	QVector<AssetMusic>	music;

	///All the available Sounds
	QVector<AssetSound>	sounds;

	///All the available background Images for the Scenery
	QVector<AssetImage>	sceneryBackgroundImages;

	///All the available Images for SceneryObjects
	QVector<AssetImage>	sceneryObjectImages;
};

