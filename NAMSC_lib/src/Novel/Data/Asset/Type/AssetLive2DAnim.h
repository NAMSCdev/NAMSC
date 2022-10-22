#pragma once
#include "Global.h"

#include "Novel/Data/Asset/Asset.h"

/// [optional] Allows Live2D Animation loading and its memory management
class AssetLive2DAnim final : public Asset
{
public:
	AssetLive2DAnim() = default;
	AssetLive2DAnim(QString&& name, uint pos = 0, QString&& location = "");
	AssetLive2DAnim(const AssetLive2DAnim&) = delete;
	AssetLive2DAnim& operator=(const AssetLive2DAnim&) = delete;
	
	/// Tries to load the Asset
	/// \exception Error Could not find/open file
	void load() override {}

	/// Release resources allocated for this asset
	void unload() override {}
	
	/// Returns whether the asset is currently loaded
	bool isLoaded() const override { return true; }

protected:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::AssetLive2DAnim; }
};




inline AssetLive2DAnim::AssetLive2DAnim(QString&& name, uint pos = 0, QString&& location) :
	Asset(move(name), pos, move(location))
{
}