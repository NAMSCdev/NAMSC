#pragma once
#include "Global.h"

#include "Novel/Data/Asset/Asset.h"

/// Allows Audio loading and its memory management
class AssetAudio final : public Asset
{
public:
	AssetAudio() = default;
	AssetAudio(QString&& name, uint pos = 0, QString&& location = "");
	AssetAudio(const AssetAudio& obj)            = delete;
	AssetAudio& operator=(const AssetAudio& obj) = delete;

	/// Tries to load an Asset
	/// Throws a noncritical Exception on failure
	void load() override					
	{ 
		try
		{
			mediaPlayer = uPtr<QMediaPlayer>(new QMediaPlayer());
			mediaPlayer->setSource(QUrl::fromLocalFile(location));
		}
		//todo: what to catch?
		catch (...)
		{

		}
	}

	/// Release resources allocated for this asset
	void unload() override { mediaPlayer.reset(); }

	/// Returns whether the asset is currently loaded
	bool isLoaded() const override { return mediaPlayer.get() != nullptr; }

	/// Returns a pointer to a MediaPlayer with music potentially loaded
	QMediaPlayer* getMusicPlayer() { return mediaPlayer.get(); }

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::AssetMusic; }

	/// A smart pointer to the actual data
	uPtr<QMediaPlayer> mediaPlayer;
};




inline AssetAudio::AssetAudio(QString&& name, uint pos = 0, QString&& location = "") :
	Asset(move(name), pos, move(location)) 
{
}