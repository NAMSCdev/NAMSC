#pragma once
#include "Global.h"

#include "Story/Data/Asset/Asset.h"

//Allows Font loading and its memory management
class FontAsset final : public Asset
{
public:
	FontAsset() = default;
	FontAsset(QString &&URI, QString &&location, unsigned pos = 0) :
		Asset(move(URI), move(location), pos) {}

	//Tries to load an Assent
	//Throws a noncritical Exception on failure
	bool					load	() override			{ font = uPtr<QFont>(new QFont(location)); return true; }

	//Release resources allocated for this asset
	void					unload	() override			{ font.reset(); }

	//Returns whether the asset is currently loaded
	bool					isLoaded() override			{ return font.get() != nullptr; }

	//Returns a pointer to a MediaPlayer with music potentially loaded
	QFont*					getFont	()					{ return font.get(); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID			getType	() const override	{ return SerializationID::FontAsset; }

	//A smart pointer to the actual data
	uPtr<QFont>				font;
};