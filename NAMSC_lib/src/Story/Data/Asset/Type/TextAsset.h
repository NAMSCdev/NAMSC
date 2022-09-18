#pragma once
#include "Global.h"

#include "Story/Data/Asset/Asset.h"

//Allows Image loading and its memory management
class TextAsset final : public Asset
{
public:
	TextAsset() = default;
	TextAsset(QString &&URI, QString &&location, unsigned pos = 0) : 
		Asset(move(URI), move(location), pos) {}

	//Tries to load an Assent
	//Throws a noncritical Exception on failure
	bool					load	() override		
	{
		QFile file(location);
		if (!file.open(QIODevice::ReadOnly)) 
		{
			//TODO: add some Exception
			return false;
		}
		QDataStream datastream(&file);
		datastream.skipRawData(pos);
		datastream >> *(str.get());
		return true;
	}

	//Release resources allocated for this asset
	void					unload	() override			{ str.reset(); }

	//Returns a pointer to the QImage object that this Asset holds
	QString*				getText	()					{ return str.get(); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	virtual SerializationID	getType	() const override	{ return SerializationID::TextAsset; }

	//A smart pointer to the actual data
	uPtr<QString>			str;
};