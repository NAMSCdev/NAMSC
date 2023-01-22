#pragma once

#include <qhashfunctions.h>
#include <unordered_map>

#include "Novel/Data/Asset/AssetAnim.h"
#include "Novel/Data/Asset/AssetImage.h"

/// Loads and unloads Assets - objects that manage Resources
/// \todo [optional] Create some smart algorithm that will prefetch Assets that might be soon loaded in some asynchronous manner
class AssetManager final
{
public:
	static AssetManager& getInstance()           noexcept;
	AssetManager(const AssetManager&)            noexcept = delete;
	AssetManager(AssetManager&&)                 noexcept = delete;
	AssetManager& operator=(const AssetManager&) noexcept = delete;

	/// Loads all Asset objects without their Resources
	void loadAllAssetsDefinitions();

	/// Save all Asset objects without their Resources
	void saveAllAssetsDefinitions();

	/// \return Pointer to the **color** AssetAnim or nullptr if it wasn't found
	const AssetAnimColor* getAssetAnimColor(const QString&          name) const;
	/// \return Pointer to the **color** AssetAnim or nullptr if it wasn't found
	AssetAnimColor* getAssetAnimColor(const QString&                name);
	/// \return Pointer to the **move** AssetAnim or nullptr if it wasn't found
	const AssetAnimMove* getAssetAnimMove(const QString&            name) const;
	/// \return Pointer to the **move** AssetAnim or nullptr if it wasn't found
	AssetAnimMove* getAssetAnimMove(const QString&                  name);
	/// \return Pointer to the **rotate** AssetAnim or nullptr if it wasn't found
	const AssetAnimRotate* getAssetAnimRotate(const QString&        name) const;
	/// \return Pointer to the **rotate** AssetAnim or nullptr if it wasn't found
	AssetAnimRotate* getAssetAnimRotate(const QString&              name);
	/// \return Pointer to the **rotate** AssetAnim or nullptr if it wasn't found
	const AssetAnimScale* getAssetAnimScale(const QString&         name) const;
	/// \return Pointer to the **scale** AssetAnim or nullptr if it wasn't found
	AssetAnimScale* getAssetAnimScale(const QString&                name);
	/// \return Pointer to the **background** AssetImage or nullptr if it wasn't found
	const AssetImage* getAssetImageSceneryBackground(const QString& name) const;
	/// \return Pointer to the **background** AssetImage or nullptr if it wasn't found
	AssetImage* getAssetImageSceneryBackground(const QString&       name);
	/// \return Pointer to the **sprite** AssetImage or nullptr if it wasn't found
	const AssetImage* getAssetImageSceneryObject(const QString&     name) const;
	/// \return Pointer to the **sprite** AssetImage or nullptr if it wasn't found
	AssetImage* getAssetImageSceneryObject(const QString&           name);

	/// \exception Error `name` is not unique within the `colorAnims` container 
	AssetAnimColor* addAssetAnimColor(const QString&          name, uint size, uint pos = 0, const QString& path = "");
	/// \exception Error `name` is not unique within the `moveAnims_` container 
	AssetAnimMove* addAssetAnimMove(const QString&            name, uint size, uint pos = 0, const QString& path = "");
	/// \exception Error `name` is not unique within the `moveAnims_` container 
	AssetAnimRotate* addAssetAnimRotate(const QString&        name, uint size, uint pos = 0, const QString& path = "");
	/// \exception Error `name` is not unique within the `scaleAnims_` container 
	AssetAnimScale* addAssetAnimScale(const QString&          name, uint size, uint pos = 0, const QString& path = "");
	/// \exception Error `name` is not unique within the `backgroundImages_` container 
	AssetImage* addAssetImageSceneryBackground(const QString& name, uint size, uint pos = 0, const QString& path = "");
	/// \exception Error `name` is not unique within the `objectImages_` container 
	AssetImage* addAssetImageSceneryObject(const QString&     name, uint size, uint pos = 0, const QString& path = "");

	/// \exception Error `newName` is not unique within the `colorAnims` container or no AssetAnimColor with `oldName` exists
	AssetAnimColor* renameAssetAnimColor(const QString&          oldName, const QString& newName);
	/// \exception Error `newName` is not unique within the `moveAnims_` container or no AssetAnimMove with `oldName` exists
	AssetAnimMove* renameAssetAnimMove(const QString&            oldName, const QString& newName);
	/// \exception Error `newName` is not unique within the `moveAnims_` container or no AssetAnimRotate with `oldName` exists
	AssetAnimRotate* renameAssetAnimRotate(const QString&        oldName, const QString& newName);
	/// \exception Error `newName` is not unique within the `scaleAnims_` container or no AssetAnimScale with `oldName` exists
	AssetAnimScale* renameAssetAnimScale(const QString&          oldName, const QString& newName);
	/// \exception Error `newName` is not unique within the `backgroundImages_` container or no **background** AssetImage with `oldName` exists
	AssetImage* renameAssetImageSceneryBackground(const QString& oldName, const QString& newName);
	/// \exception Error `newName` is not unique within the `objectImages_` container or no **sprite** AssetImage with `oldName` exists
	AssetImage* renameAssetImageSceneryObject(const QString&     oldName, const QString& newName);

	/// Saves all Assets' Resource changes
	/// \exception Error Could not find/open/read the Assets' Resource or Definition files
	void saveAllAssets();

	/// [optional] Corrects Assets after the Resource change in a compressed file
	/// If the Assets takes more space, the pos of other Assets that are stored in the same file must be adjusted
	/// \todo implement this
	void correctAssets(QString name, uint oldSize, uint size, uint pos, QString path);

private:
	//Nothing can create the AssetManager, but its methods
	AssetManager() = default;

	/// Loads a single type of Asset definitions from a single file
	/// \exception Error `name` is not unique within the container 
	template<typename AssetType>
	void loadDefinitions(const QString& path, std::unordered_map<QString, AssetType>& map);

	/// Saves a single type of Asset definitions to a single file
	/// \exception Error Name is not unique within the container 
	template<typename AssetType>
	void saveDefinitions(const QString& path, std::unordered_map<QString, AssetType>& map);

	std::unordered_map<QString, AssetAnimColor>  colorAnims_;
	std::unordered_map<QString, AssetAnimMove>   moveAnims_;
	std::unordered_map<QString, AssetAnimRotate> rotateAnims_;
	std::unordered_map<QString, AssetAnimScale>  scaleAnims_;

	std::unordered_map<QString, AssetImage>	     backgroundImages_;
	std::unordered_map<QString, AssetImage>	     objectImages_;
};
