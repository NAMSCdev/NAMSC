#pragma once
#include "Global.h"

#include "Story/Data/Asset/Asset.h"

///Allows Music loading and its memory management
class MusicAsset final : public Asset
{
public:
	MusicAsset() = default;
	MusicAsset(QString &&name, QString &&location, unsigned pos = 0) : 
		Asset(move(name), move(location), pos)		{}
	MusicAsset(const MusicAsset& asset)				{ *this = asset; }
	MusicAsset& operator=(const MusicAsset& asset)	{ Asset::operator=(asset); }
	///Tries to load an Asset
	///Throws a noncritical Exception on failure
	void load() override					
	{ 
		mediaPlayer = uPtr<QMediaPlayer>(new QMediaPlayer());
		mediaPlayer->setSource(QUrl::fromLocalFile(location));
	}

	///Release resources allocated for this asset
	void unload() override							{ mediaPlayer.reset(); }

	///Returns whether the asset is currently loaded
	bool isLoaded() const override					{ return mediaPlayer.get() != nullptr; }

	///Returns a pointer to a MediaPlayer with music potentially loaded
	QMediaPlayer*		getMusicPlayer()			{ return mediaPlayer.get(); }

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID		getType() const override	{ return SerializationID::MusicAsset; }

	///A smart pointer to the actual data
	uPtr<QMediaPlayer>	mediaPlayer;
};