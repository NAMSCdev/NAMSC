#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/ImageAsset.h"

//Allows SceneryObject's part Image loading and its memory management
class SceneryObjectPartImageAsset final : public ImageAsset
{
public:
	SceneryObjectPartImageAsset() = default;
	SceneryObjectPartImageAsset(QString &&URI, QString &&location, unsigned pos = 0) : 
		ImageAsset(move(URI), move(location), pos) {}

	//Tries to load an Assent
	//Throws a noncritical Exception on failure
	bool					load	() override			{ ImageAsset::load(); return true; }

	//Release resources allocated for this asset
	void					unload	() override			{ ImageAsset::unload(); }
	
	//Returns whether the asset is currently loaded
	bool					isLoaded() override			{ return ImageAsset::isLoaded(); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID			getType	() const override	{ return SerializationID::SceneryObjectPartImageAsset; }
};