#pragma once
#include "Global.h"

#include "Story/Data/Asset/Asset.h"

///Allows Sound loading and its memory management
class SoundAsset final : public Asset
{
public:
	SoundAsset() = default;
	SoundAsset(QString &&name, QString &&location, unsigned pos = 0) : 
		Asset(move(name), move(location), pos)		{}
	SoundAsset(const SoundAsset& asset)				{ *this = asset; }
	SoundAsset& operator=(const SoundAsset& asset)	{ Asset::operator=(asset); }
	///Tries to load an Assent
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
	QMediaPlayer*		getSoundPlayer()			{ return mediaPlayer.get(); }

protected:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID		getType() const override	{ return SerializationID::SoundAsset; }

	///A smart pointer to the actual data
	uPtr<QMediaPlayer>	mediaPlayer;
};