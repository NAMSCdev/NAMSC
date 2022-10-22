#pragma once
#include "Global.h"

#include "Novel/Data/Asset/Asset.h"

/// Allows Image loading and its memory management
class AssetText final : public Asset
{
public:
	AssetText() = default;
	AssetText(QString&& name, uint pos = 0, QString&& location = "");
	AssetText(const AssetText& obj) = delete;
	AssetText& operator=(const AssetText& obj) = delete;

	/// Tries to load an Assent
	/// Throws a noncritical Exception on failure
	void load() override		
	{
		QFile file(location);
		if (!file.open(QIODevice::ReadOnly)) 
		{
			/// TODO: add some Exception
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

	/// Release resources allocated for this asset
	void unload() override { str.reset(); }

	/// Returns a pointer to the QImage object that this Asset holds
	QString* getText() { return str.get(); }

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::AssetText; }

	/// A smart pointer to the actual data
	uPtr<QString> str;
};




inline AssetText::AssetText(QString&& name, uint pos = 0, QString&& location = "") :
	Asset(move(name), pos, move(location)) 
{
}