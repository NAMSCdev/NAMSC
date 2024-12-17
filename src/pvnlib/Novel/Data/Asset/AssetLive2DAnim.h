//#pragma once
//#include "Global.h"
//
//#include "pvnLib/Novel/Data/Asset/Asset.h"
//
///// [optional] Allows Live2D Animation loading and its memory management
//class AssetLive2DAnim final : public Asset
//{
//public:
//	AssetLive2DAnim() noexcept = default;
//	AssetLive2DAnim(QString&& name, uint size, uint pos = 0, QString&& location = "") noexcept;
//	AssetLive2DAnim(const AssetLive2DAnim&)            = delete;
//	AssetLive2DAnim& operator=(const AssetLive2DAnim&) = delete;
//	
//	/// Tries to load the AssetLive2DAnim
//	/// \exception Error Could not find/open/read the file
//	void load() override {}
//
//	/// Release resources allocated for the AssetLive2DAnim
//	void unload() noexcept override {}
//	
//	/// Returns whether the AssetLive2DAnim is currently loaded
//	/// \return Whether the AssetLive2DAnim is currently loaded
//	bool isLoaded() const override { return true; }
//
//	/// Accepts an AssetVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an AssetVisitor
//	void accept(AssetVisitor* visitor) override { visitor->visitAssetLive2DAnim(this); }
//};
//
//
//
//
//inline AssetLive2DAnim::AssetLive2DAnim(QString&& name, uint size, uint pos, QString&& location) :
//	Asset(move(name), size, pos, move(location))
//{
//}