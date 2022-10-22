#pragma once
#include "Novel/Data/Asset/Type/AssetLive2DAnim.h"
#include "Novel/Data/Asset/Type/AssetLive2DModel.h"
#include "Novel/Data/Asset/Type/AssetAnim.h"
#include "Novel/Data/Asset/Type/AssetAudio.h"
#include "Novel/Data/Asset/Type/AssetImage.h"

/// Loads and unloads Assets - objects that manage Resources
/// @todo [optional] Create some smart algorithm that will prefetch Assets that might be soon loaded in some asynchronous manner
class AssetManager
{
public:
	static AssetManager& getInstance()
	{
		static AssetManager instance;
		return instance;
	}
	AssetManager() = default;
	AssetManager(const AssetManager&)            = delete;
	AssetManager& operator=(const AssetManager&) = delete;

	/// Loads all Asset objects without their resources
	void loadAllAssetsDefinitions();

	/// Finds an AssetLive2DAnim
	/// \param name The searched AssetLive2DAnim
	/// \exception Error Failure finding the AssetLive2DAnim
	/// \return Pointer to the found AssetLive2DAnim in `live2DAnims`
	AssetLive2DAnim* findAssetLive2DAnim(const QString& name) const
	{
		return findInArray<AssetLive2DAnim>(name, live2DAnims);
	}
		
	/// Finds an AssetLive2DModel
	/// \param name The searched AssetLive2DModel
	/// \exception Error Failure finding the AssetLive2DModel
	/// \return Pointer to the found AssetLive2DModel in `live2DModels`
	AssetLive2DModel* findAssetLive2DModel(const QString& name) const
	{
		return findInArray<AssetLive2DModel>(name, live2DModels);
	}

	/// Finds an AssetAnim that animates a SceneryObject with a **color** animation
	/// \param name The searched **color** AssetAnim
	/// \exception Error Failure finding the **color** AssetAnim
	/// \return Pointer to the found AssetAnim in `colorAnims`
	AssetAnim<AnimNodeDouble4D>* findAssetAnimColor(const QString& name) const
	{
		return findInArray<AssetAnim<AnimNodeDouble4D>>(name, colorAnims);
	}

	/// Finds an AssetAnim that animates a SceneryObject with a **movement** animation
	/// \param name The searched **movement** AssetAnim
	/// \exception Error Failure finding the **movement** AssetAnim
	/// \return Pointer to the found AssetAnim in `moveAnims`
	AssetAnim<AnimNodeDouble2D>* findAssetAnimMove(const QString& name) const
	{
		return findInArray<AssetAnim<AnimNodeDouble2D>>(name, moveAnims);
	}

	/// Finds an AssetAnim that animates a SceneryObject with a **rotation** animation
	/// \param name The searched **rotation** AssetAnim
	/// \exception Error Failure finding the **rotation** AssetAnim
	/// \return Pointer to the found AssetAnim in `rotateAnims`
	AssetAnim<AnimNodeDouble1D>* findAssetAnimRotate(const QString& name) const
	{
		return findInArray<AssetAnim<AnimNodeDouble1D>>(name, rotateAnims);
	}

	/// Finds an AssetAnim that animates a SceneryObject with a **scaling** animation
	/// \param name The searched **scaling** AssetAnim
	/// \exception Error Failure finding the **scaling** AssetAnim
	/// \return Pointer to the found AssetAnim in `scaleAnims`
	AssetAnim<AnimNodeDouble2D>* findAssetAnimScale(const QString& name) const
	{
		return findInArray<AssetAnim<AnimNodeDouble2D>>(name, scaleAnims);
	}

	/// Finds an AssetAudio that contains some Music
	/// \param name The searched AssetAudio
	/// \exception Error Failure finding the AssetAudio
	/// \return Pointer to the found AssetMusic in `music`
	AssetAudio*	findMusicAssetAudio(const QString &name) const
	{ 
		return findInArray<AssetAudio>(name, music);
	}

	/// Finds an AssetAudio that clontains a Sound
	/// \param name The searched AssetSound
	/// \exception Error Failure finding the AssetSound
	/// \return Pointer to the found AssetSound in `sounds`
	AssetAudio*	findSoundAssetAudio(const QString &name) const
	{ 
		return findInArray<AssetAudio>(name, sounds);
	}

	/// Finds an AssetImage that can be used as a **background** Image for the Scenery
	/// \param name The searched **background** AssetImage
	/// \exception Error Failure finding the **background** AssetImage
	/// \return Pointer to the found AssetImage in `backgroundImages`
	AssetImage*	findSceneryBackgroundAssetImage(const QString &name) const
	{ 
		return findInArray<AssetImage>(name, backgroundImages);
	}

	/// Finds an AssetImage that can be used as a SceneryObject **sprite** or part of it
	/// \param name The searched **sprite** AssetImage
	/// \exception Error Failure finding the **sprite** AssetImage
	/// \return Pointer to the found AssetImage in `objectImages`
	AssetImage*	findSceneryObjectAssetImage(const QString &name) const
	{ 
		return findInArray<AssetImage>(name, objectImages);
	}

	/// Creates and inserts an AssetLive2DAnim	
	/// \param name A unique identificator within the `live2DAnims` container
	/// \param location The file that stores the Resource's data. If empty - it will default to `"resource.bin"`
	/// \param pos Data offset in the file, so the read will begin from this position
	/// \exception Error Name is not unique within the `live2DAnims` container 
	/// \return Whether the insertion was successful
	/// A proper QMessageLogger must be installed to not throw an Exception and allow this function to return
	void insertAssetLive2DAnim(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetLive2DAnim>(name, pos, location, live2DAnims);
	}

	/// Creates and inserts an AssetLive2DModel	
	/// \param name A unique identificator within the `live2DModels` container
	/// \param location The file that stores the Resource's data. If empty - it will default to `"resource.bin"`
	/// \param pos Data offset in the file, so the read will begin from this position
	/// \exception Error Name is not unique within the `live2DModels` container 
	/// \return Whether the insertion was successful
	/// A proper QMessageLogger must be installed to not throw an Exception and allow this function to return
	void insertAssetLive2DModel(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetLive2DModel>(name, pos, location, live2DModels);
	}

	/// Creates and inserts into an AssetAnim that animates a SceneryObject with a **color** Animation
	/// \param name A unique identificator within the `colorAnims` container
	/// \param location The file that stores the Resource's data. If empty - it will default to `"resource.bin"`
	/// \param pos Data offset in the file, so the read will begin from this position
	/// \exception Error Name is not unique within the `colorAnims` container 
	/// \return Whether the insertion was successful
	/// A proper QMessageLogger must be installed to not throw an Exception and allow this function to return
	bool insertAssetAnimColor(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetAnim<AnimNodeDouble4D>>(name, pos, location, colorAnims);
	}

	/// Creates and inserts an AssetAnim that animates a SceneryObject with a **move** Animation
	/// \param name A unique identificator within the `moveAnims` container
	/// \param location The file that stores the Resource's data. If empty - it will default to `"resource.bin"`
	/// \param pos Data offset in the file, so the read will begin from this position
	/// \exception Error Name is not unique within the `moveAnims` container 
	/// \return Whether the insertion was successful
	/// A proper QMessageLogger must be installed to not throw an Exception and allow this function to return
	bool insertAssetAnimMove(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetAnim<AnimNodeDouble2D>>(name, pos, location, moveAnims);
	}

	/// Creates and inserts an AssetAnim that animates a SceneryObject with a **rotate** Animation
	/// \param name A unique identificator within the `moveAnims` container
	/// \param location The file that stores the Resource's data. If empty - it will default to `"resource.bin"`
	/// \param pos Data offset in the file, so the read will begin from this position
	/// \exception Error Name is not unique within the `moveAnims` container 
	/// \return Whether the insertion was successful
	/// A proper QMessageLogger must be installed to not throw an Exception and allow this function to return
	bool insertAssetAnimRotate(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetAnim<AnimNodeDouble1D>>(name, pos, location, rotateAnims);
	}

	/// Creates and inserts an AssetAnim that animates a SceneryObject with a **scale** Animation
	/// \param name A unique identificator within the `scaleAnims` container
	/// \param location The file that stores the Resource's data. If empty - it will default to `"resource.bin"`
	/// \param pos Data offset in the file, so the read will begin from this position
	/// \exception Error Name is not unique within the `scaleAnims` container 
	/// \return Whether the insertion was successful
	/// A proper QMessageLogger must be installed to not throw an Exception and allow this function to return
	bool insertAssetAnimScale(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetAnim<AnimNodeDouble2D>>(name, pos, location, scaleAnims);
	}

	/// Creates and inserts an AssetAudio that contains some Music
	/// \param name A unique identificator within the `music` container
	/// \param location The file that stores the Resource's data. If empty - it will default to `"resource.bin"`
	/// \param pos Data offset in the file, so the read will begin from this position
	/// \exception Error Name is not unique within the `music` container 
	/// \return Whether the insertion was successful
	/// A proper QMessageLogger must be installed to not throw an Exception and allow this function to return
	bool insertAssetMusic(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetAudio>(name, pos, location, music);
	}

	/// Creates and inserts an AssetAudio that contains a Sound
	/// \param name A unique identificator within the `sounds` container
	/// \param location The file that stores the Resource's data. If empty - it will default to `"resource.bin"`
	/// \param pos Data offset in the file, so the read will begin from this position
	/// \exception Error Name is not unique within the `sounds` container 
	/// \return Whether the insertion was successful
	/// A proper QMessageLogger must be installed to not throw an Exception and allow this function to return	
	bool insertAssetSound(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetAudio>(name, pos, location, sounds);
	}

	/// Creates and inserts an AssetImage that 
	/// \param name A unique identificator within the `backgroundImages` container
	/// \param location The file that stores the Resource's data. If empty - it will default to `"resource.bin"`
	/// \param pos Data offset in the file, so the read will begin from this position
	/// \exception Error Name is not unique within the `backgroundImages` container 
	/// \return Whether the insertion was successful
	/// A proper QMessageLogger must be installed to not throw an Exception and allow this function to return
	bool insertSceneryBackgroundAssetImage(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetImage>(name, pos, location, backgroundImages);
	}
	
	/// Creates and inserts into a special contrainer an AssetAnim that animates a SceneryObject with a **color** Animation
	/// \param name A unique identificator within the `AssetImage` container
	/// \param location The file that stores the Resource's data. If empty - it will default to `"resource.bin"`
	/// \exception Error Name is not unique within the `colorAnims` container 
	/// \return Whether the insertion was successful
	/// A proper QMessageLogger must be installed to not throw an Exception and allow this function for a return
	bool insertSceneryObjectAssetImage(const QString& name, const QString& location, uint pos)
	{
		insertAsset<AssetImage>(name, pos, location, objectImages);
	}

private:
	/// Inserts an Asset into a dedicated container for it
	template<class Type>
	void insertAsset(const QString& name, uint pos, const QString& location, QVector<Type>& vector)
	{
		if (std::find(vector.begin(), vector.end(), name) != vector.end())
			error("An Asset with name \"" + name "\" already exists!");
		vector.emplace_back(name, pos, location);
	}

	/// [optional]All the available Live2D Animations for Characters
	QVector<AssetLive2DAnim> live2DAnims;

	/// [optional]All the available Characters' Live2D models
	QVector<AssetLive2DModel> live2DModels;

	/// All the available Animations for SceneryObjects' colors changing
	QVector<AssetAnim<AnimNodeDouble4D>> colorAnims;

	/// All the available Animations for SceneryObjects' movement 
	QVector<AssetAnim<AnimNodeDouble2D>> moveAnims;

	/// All the available Animations for SceneryObjects' rotation
	QVector<AssetAnim<AnimNodeDouble1D>> rotateAnims;

	/// All the available Animations for SceneryObjects' scaling
	QVector<AssetAnim<AnimNodeDouble2D>> scaleAnims;

	/// All the available Music
	QVector<AssetAudio>	music;

	/// All the available Sounds
	QVector<AssetAudio>	sounds;

	/// All the available background Images for the Scenery
	QVector<AssetImage>	backgroundImages;

	/// All the available Images for SceneryObjects
	QVector<AssetImage>	objectImages;
};
