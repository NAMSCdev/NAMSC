#pragma once
#include "Global.h"

#include "Story/Data/Asset/Asset.h"

//Allows Image loading and its memory management
class ImageAsset : public Asset
{
public:
	ImageAsset() = default;
	ImageAsset(QString &&URI, QString &&location, unsigned pos = 0) :
		Asset(move(URI), move(location), pos) {}

	//The destructor needs to be virtual, so the proper destructor will always be called when destroying an Asset pointer
	virtual ~ImageAsset() = 0;

	//Tries to load an Assent
	//Throws a noncritical Exception on failure
	bool					load	() override			{ img = uPtr<QImage>(new QImage(location)); return true; }

	//Release resources allocated for this asset
	void					unload	() override			{ img.reset(); }
	
	//Returns whether the asset is currently loaded
	bool					isLoaded() override			{ return img.get() != nullptr; }

	//Returns a pointer to the QImage object that this Asset holds
	QImage*					getImage()					{ return img.get(); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	virtual SerializationID	getType	() const override	= 0;

	//A smart pointer to the actual data
	uPtr<QImage>			img;
};