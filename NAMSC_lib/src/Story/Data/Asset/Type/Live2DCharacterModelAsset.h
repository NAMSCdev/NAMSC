#pragma once
#include "Global.h"

#include "Story/Data/Asset/Asset.h"

///[optional] Allows Live2D Model loading and its memory management
class Live2DCharacterModelAsset final : public Asset
{
public:
	Live2DCharacterModelAsset() = default;
	Live2DCharacterModelAsset(QString &&name, QString &&location, unsigned pos = 0) : 
		Live2DCharacterModelAsset(move(name), move(location), pos)	{}
	Live2DCharacterModelAsset(const Live2DCharacterModelAsset& asset)				= default;
	Live2DCharacterModelAsset& operator=(const Live2DCharacterModelAsset& asset)	= default;
	///Tries to load an Assent
	///Throws a noncritical Exception on failure
	void load() override						{}

	///Release resources allocated for this asset
	void unload() override						{}

	///Returns whether the asset is currently loaded
	bool isLoaded() const override				{ return true; }

protected:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override	{ return SerializationID::Live2DCharacterModelAsset; }
};