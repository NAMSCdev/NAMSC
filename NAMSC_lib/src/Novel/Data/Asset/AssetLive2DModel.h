//#pragma once
//#include "Global.h"
//
//#include "Novel/Data/Asset/Asset.h"
//
///// [optional] Allows Live2D Model loading and its memory management
//class AssetLive2DModel final : public Asset
//{
//public:
//	AssetLive2DModel() noexcept = default;
//	AssetLive2DModel(QString&& name, uint pos = 0, QString&& location = "") noexcept;
//	AssetLive2DModel(const AssetLive2DModel&)            = delete;
//	AssetLive2DModel& operator=(const AssetLive2DModel&) = delete;
//
//	/// Tries to load an AssetLive2DModel
//	/// \exception Error Could not find/open/read the file
//	void load() override {}
//
//	/// Release resources allocated for the AssetLive2DModel
//	void unload() noexcept override {}
//
//	/// Returns whether the AssetLive2DModel is currently loaded
//  /// \return Whether the AssetLive2DModel is currently loaded
//	bool isLoaded() const override { return true; }
//
//	/// Accepts an AssetVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an AssetVisitor
//	void accept(AssetVisitor* visitor) override { visitor->visitAssetLive2DModel(this); }
//};
//
//
//
//
//inline AssetLive2DModel::AssetLive2DModel(QString&& name, uint size, uint pos, QString&& location) :
//	Asset(move(name), size, pos, move(location))
//{
//}
