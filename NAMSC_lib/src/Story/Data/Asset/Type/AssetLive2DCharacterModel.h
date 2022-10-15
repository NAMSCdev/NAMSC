#pragma once
#include "Global.h"

#include "Story/Data/Asset/Asset.h"

///[optional] Allows Live2D Model loading and its memory management
class AssetLive2DCharacterModel final : public Asset
{
public:
	AssetLive2DCharacterModel() = default;
	AssetLive2DCharacterModel(QString &&name, unsigned pos = 0, bool bExternal = false, QString &&location = "") :
		Asset(move(name), pos, bExternal, move(location)) { }
	AssetLive2DCharacterModel(const AssetLive2DCharacterModel& obj) { *this = obj; }
	AssetLive2DCharacterModel& operator=(const AssetLive2DCharacterModel& obj) 
	{
		if (this == &obj) return *this;

		Asset::operator=(obj);

		return *this;
	}
	///Tries to load an Assent
	///Throws a noncritical Exception on failure
	void load() override {}

	///Release resources allocated for this asset
	void unload() override {}

	///Returns whether the asset is currently loaded
	bool isLoaded() const override { return true; }

protected:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::Live2DCharacterModelAsset; }
};