#pragma once
#include "Global.h"

#include "Novel/Data/Asset/Asset.h"

/// Allows Image loading and its memory management
class AssetImage final : public Asset
{
public:
	AssetImage() = default;
	AssetImage(QString&& name, uint pos = 0, QString&& location = "");
	AssetImage(const AssetImage& obj) = delete;
	AssetImage& operator=(const AssetImage& obj) = delete;

	/// The destructor needs to be virtual, so the proper destructor will always be called when destroying an Asset pointer
	virtual ~AssetImage() = 0;

	/// Tries to load an Assent
	/// Throws a noncritical Exception on failure
	void load() override { img = uPtr<QImage>(new QImage(location)); }

	/// Release resources allocated for this asset
	void unload() override { img.reset(); }
	
	/// Returns whether the asset is currently loaded
	bool isLoaded() const override { return img.get() != nullptr; }

	/// Returns a pointer to the QImage object that this Asset holds
	QImage*	getImage() { return img.get(); }

protected:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::AssetImage; }

	/// A smart pointer to the actual data
	uPtr<QImage> img;
};




inline AssetImage::AssetImage(QString&& name, uint pos = 0, QString&& location = "") :
	Asset(move(name), pos, move(location))
{ 
}