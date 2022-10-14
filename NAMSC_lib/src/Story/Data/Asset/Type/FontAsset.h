#pragma once
#include "Global.h"

#include "Story/Data/Asset/Asset.h"

///Allows Font loading and its memory management
class FontAsset final : public Asset
{
public:
	FontAsset() = default;
	FontAsset(QString &&name, QString &&location, unsigned pos = 0) :
		Asset(move(name), move(location), pos)	{}
	FontAsset(const FontAsset& asset)			{ *this = asset; }
	FontAsset& operator=(const FontAsset& asset){ Asset::operator=(asset); }
	///Tries to load an Assent
	///Throws a noncritical Exception on failure
	///@todo allow quering the operating system for font
	void load() override				
	{ 
		font = uPtr<QRawFont>(new QRawFont()); 
		font.get()->loadFromFile(location, fontSize, QFont::HintingPreference::PreferFullHinting); 
	}

	///Release resources allocated for this asset
	void unload() override						{ font.reset(); }

	///Returns whether the asset is currently loaded
	bool isLoaded() const override				{ return font.get() != nullptr; }

	///Returns a pointer to a MediaPlayer with music potentially loaded
	QRawFont* getFont()							{ return font.get(); }

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override	{ return SerializationID::FontAsset; }

	///A smart pointer to the actual data
	uPtr<QRawFont>	font;

	///Size in the font file database
	///@todo implement better  
	unsigned		fontSize;

	///Whether this font is an one provided by the operating system
	bool			systemFont = false;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override
	{
		dataStream >> fontSize >> systemFont;
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override
	{
		dataStream << fontSize << systemFont;
	}
};