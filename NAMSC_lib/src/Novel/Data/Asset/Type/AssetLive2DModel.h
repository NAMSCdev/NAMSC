#pragma once
#include "Global.h"

#include "Novel/Data/Asset/Asset.h"

/// [optional] Allows Live2D Model loading and its memory management
class AssetLive2DModel final : public Asset
{
public:
	AssetLive2DModel() = default;
	AssetLive2DModel(QString&& name, uint pos = 0, QString&& location = "");
	AssetLive2DModel(const AssetLive2DModel&) = delete;
	AssetLive2DModel& operator=(const AssetLive2DModel&) = delete;

	/// Tries to load an Assent
	/// Throws a noncritical Exception on failure
	void load() override {}

	/// Release resources allocated for this asset
	void unload() override {}

	/// Returns whether the asset is currently loaded
	bool isLoaded() const override { return true; }

protected:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::AssetLive2DModel; }
};




inline AssetLive2DModel::AssetLive2DModel(QString&& name, uint pos, QString&& location) :
	Asset(move(name), pos, move(location))
{
}
