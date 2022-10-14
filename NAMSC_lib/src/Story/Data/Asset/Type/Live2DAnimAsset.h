#pragma once
#include "Global.h"

#include "Story/Data/Asset/Asset.h"

///[optional] Allows Live2D Animation loading and its memory management
class Live2DAnimAsset final : public Asset
{
public:
	Live2DAnimAsset() = default;
	Live2DAnimAsset(QString &&name, QString &&location, unsigned pos = 0) : 
		Asset(move(name), move(location), pos)	{}
	Live2DAnimAsset(const Live2DAnimAsset& asset)				= default;
	Live2DAnimAsset& operator=(const Live2DAnimAsset& asset)	= default;
	
	///Tries to load the Asset
	///\exception Error Could not find/open file
	void load() override						{}

	///Release resources allocated for this asset
	void unload() override						{}
	
	///Returns whether the asset is currently loaded
	bool isLoaded() const override				{ return true; }

protected:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override	{ return SerializationID::Live2DAnimAsset; }
};