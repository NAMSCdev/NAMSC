#pragma once
#include "Global.h"

#include "Story/Data/Asset/Asset.h"

///Allows Image loading and its memory management
class TextAsset final : public Asset
{
public:
	TextAsset() = default;
	TextAsset(QString &&name, QString &&location, unsigned pos = 0) : 
		Asset(move(name), move(location), pos)	{}
	TextAsset(const TextAsset& asset)			{ *this = asset; }
	TextAsset &operator=(const TextAsset &asset){ Asset::operator=(asset); }
	///Tries to load an Assent
	///Throws a noncritical Exception on failure
	void load() override		
	{
		QFile file(location);
		if (!file.open(QIODevice::ReadOnly)) 
		{
			///TODO: add some Exception
		}
		QDataStream datastream(&file);
		datastream.skipRawData(pos);
		QString temp;
		datastream >> temp;
		str = uPtr<QString>(new QString(std::move(temp)));
	}

	bool isLoaded() const override
	{
		return true;
	}

	///Release resources allocated for this asset
	void unload() override						{ str.reset(); }

	///Returns a pointer to the QImage object that this Asset holds
	QString*		getText()					{ return str.get(); }

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override	{ return SerializationID::TextAsset; }

	///A smart pointer to the actual data
	uPtr<QString>	str;
};