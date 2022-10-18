#pragma once
#include "Global.h"

#include "Novel/Data/Asset/Asset.h"

///Allows Image loading and its memory management
class AssetText final : public Asset
{
public:
	AssetText() = default;
	AssetText(QString &&name, uint pos = 0, bool bExternal = false, QString &&location = "") :
		Asset(move(name), pos, bExternal, move(location)) { }
	AssetText(const AssetText& obj) { *this = obj; }
	AssetText& operator=(const AssetText& obj);
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
		QString data;
		datastream >> data;
		str = uPtr<QString>(new QString(std::move(temp)));
	}

	bool isLoaded() const override
	{
		return true;
	}

	///Release resources allocated for this asset
	void unload() override { str.reset(); }

	///Returns a pointer to the QImage object that this Asset holds
	QString* getText() { return str.get(); }

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::AssetText; }

	///A smart pointer to the actual data
	uPtr<QString> str;
};

inline AssetText& AssetText::operator=(const AssetText& obj)
{
	if (this == &obj) return *this;

	Asset::operator=(obj);
	str = nullptr;

	return *this;
}