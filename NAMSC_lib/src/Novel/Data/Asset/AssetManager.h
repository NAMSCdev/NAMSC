#pragma once

#include <QHash>

#include "Novel/Data/Asset/AssetAnim.h"
#include "Novel/Data/Asset/AssetImage.h"

/// Loads and unloads Assets - objects that manage Resources
/// \todo [optional] Create some smart algorithm that will prefetch Assets that might be soon loaded in some asynchronous manner
class AssetManager
{
public:
	static AssetManager& getInstance() noexcept;
	AssetManager()                               = default;
	AssetManager(const AssetManager&)            = delete;
	AssetManager& operator=(const AssetManager&) = delete;

	/// Loads all Asset objects without their Resources
	void loadAllAssetsDefinitions();

	/// Save all Asset objects without their Resources
	void saveAllAssetsDefinitions();

	/// \return Pointer to the **color** AssetAnim or nullptr if it wasn't found
	AssetAnimColor* getAssetAnimColor(const QString& name) noexcept;
	/// \return Pointer to the **move** AssetAnim or nullptr if it wasn't found
	AssetAnimMove* getAssetAnimMove(const QString& name) noexcept;
	/// \return Pointer to the **rotate** AssetAnim or nullptr if it wasn't found
	AssetAnimRotate* getAssetAnimRotate(const QString& name) noexcept;
	/// \return Pointer to the **scale** AssetAnim or nullptr if it wasn't found
	AssetAnimScale* getAssetAnimScale(const QString& name) noexcept;
	/// \return Pointer to the **background** AssetImage or nullptr if it wasn't found
	AssetImage* getAssetImageSceneryBackground(const QString& name) noexcept;
	/// \return Pointer to the **sprite** AssetImage or nullptr if it wasn't found
	AssetImage* getAssetImageSceneryObject(const QString& name) noexcept;

	/// \exception Error Name is not unique within the `colorAnims` container 
	/// \return Whether the insertion was successful
	bool insertAssetAnimColor(const QString& name, uint size, uint pos = 0, const QString& path = "");
	/// \exception Error Name is not unique within the `moveAnims_` container 
	/// \return Whether the insertion was successful
	bool insertAssetAnimMove(const QString& name, uint size, uint pos = 0, const QString& path = "");
	/// \exception Error Name is not unique within the `moveAnims_` container 
	/// \return Whether the insertion was successful
	bool insertAssetAnimRotate(const QString& name, uint size, uint pos = 0, const QString& path = "");
	/// \exception Error Name is not unique within the `scaleAnims_` container 
	/// \return Whether the insertion was successful
	bool insertAssetAnimScale(const QString& name, uint size, uint pos = 0, const QString& path = "");
	/// \exception Error Name is not unique within the `backgroundImages_` container 
	/// \return Whether the insertion was successful
	bool insertSceneryBackgroundAssetImage(const QString& name, uint size, uint pos = 0, const QString& path = "");
	/// \exception Error Name is not unique within the `objectImages_` container 
	/// \return Whether the insertion was successful
	bool insertSceneryObjectAssetImage(const QString& name, uint size, uint pos = 0, const QString& path = "");

	/// Saves all Assets' Resource changes
	/// \exception Error Could not find/open/read the Assets' Resource or Definition files
	void saveAllAssets();

	/// [optional] Corrects Assets after the Resource change in a compressed file
	/// If the Assets takes more space, the pos of other Assets that are stored in the same file must be adjusted
	/// \todo implement this
	void correctAssets(QString name, uint oldSize, uint size, uint pos, QString path);

private:
	/// \return Pointer to the Asset or nullptr if it wasn't found
	template<typename AssetType>
	AssetType* getAsset(const QString& name, QHash<QString, AssetType>& map) noexcept;

	/// \exception Error `name` is not unique within the container 
	template<class AssetType>
	void insertAsset(const QString& name, uint size, uint pos, const QString& path, QHash<QString, AssetType>& map);

	/// Loads a single type of Asset definitions from a single file
	/// \exception Error `name` is not unique within the container 
	template<typename AssetType>
	void loadDefinitions(const QString& path, QHash<QString, AssetType>& map);

	/// Saves a single type of Asset definitions to a single file
	/// \exception Error Name is not unique within the container 
	template<typename AssetType>
	void saveDefinitions(const QString& path, QHash<QString, AssetType>& map);

	QHash<QString, AssetAnimColor>  colorAnims_;
	QHash<QString, AssetAnimMove>   moveAnims_;
	QHash<QString, AssetAnimRotate> rotateAnims_;
	QHash<QString, AssetAnimScale>  scaleAnims_;

	QHash<QString, AssetImage>		backgroundImages_;
	QHash<QString, AssetImage>		objectImages_;
};
