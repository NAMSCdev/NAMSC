#pragma once
#include "Global.h"

#include "Novel/Data/Asset/Asset.h"

///Allows Music loading and its memory management
class AssetMusic final : public Asset
{
public:
	AssetMusic() = default;
	AssetMusic(QString&& name, uint pos = 0, bool bExternal = false, QString&& location = "") :
		Asset(move(name), pos, bExternal, move(location)) { }
	AssetMusic(const AssetMusic& obj) { *this = obj; }
	AssetMusic& operator=(const AssetMusic& obj)
	{
		if (this == &obj) return *this;
		
		Asset::operator=(obj);
		mediaPlayer = nullptr;

		return *this;
	}
	///Tries to load an Asset
	///Throws a noncritical Exception on failure
	void load() override					
	{ 
		mediaPlayer = uPtr<QMediaPlayer>(new QMediaPlayer());
		mediaPlayer->setSource(QUrl::fromLocalFile(location));
	}

	///Release resources allocated for this asset
	void unload() override { mediaPlayer.reset(); }

	///Returns whether the asset is currently loaded
	bool isLoaded() const override { return mediaPlayer.get() != nullptr; }

	///Returns a pointer to a MediaPlayer with music potentially loaded
	QMediaPlayer* getMusicPlayer() { return mediaPlayer.get(); }

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::AssetMusic; }

	///A smart pointer to the actual data
	uPtr<QMediaPlayer> mediaPlayer;
};