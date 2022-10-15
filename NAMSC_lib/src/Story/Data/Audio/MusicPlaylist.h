#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/AssetMusic.h"

#include "Story/Data/Asset/AssetManager.h"

class MusicPlaylist
{
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream&, MusicPlaylist&);
	friend QDataStream& operator<<(QDataStream&, const MusicPlaylist&);
public:
	MusicPlaylist() = default;
	MusicPlaylist(QVector<QString>&& musicAssetsNames, bool bRandomize, bool bExclusive, double volume, double stereo, int timesPlayed, unsigned delay) :
		musicAssetsNames(move(musicAssetsNames)), bRandomize(bRandomize), bExclusive(bExclusive), settings(volume, stereo, timesPlayed, delay)
	{
		for (const QString& musicAssetName : this->musicAssetsNames)
			musicAssets.push_back(AssetManager::getInstance().findAssetMusic(musicAssetName));
	}
	MusicPlaylist(MusicPlaylist& obj) { *this = obj; }
	MusicPlaylist& operator=(const MusicPlaylist& obj)
	{
		if (this == &obj) return *this;

		musicAssetsNames = obj.musicAssetsNames;
		musicAssets = obj.musicAssets;
		bRandomize = obj.bRandomize;
		bExclusive = obj.bExclusive;
		settings = obj.settings;

		return *this;
	}

	///Tries to load an AssetSound
	void load()
	{
		for (AssetMusic* assetMusic : musicAssets)
			if (!assetMusic->isLoaded())
				assetMusic->load(); 
		
		if (!musicAssets.isEmpty())
			player = musicAssets.at(0)->getMusicPlayer();
	}
	///Returns whether the asset is currently loaded
	bool isLoaded() 
	{
		for (const AssetMusic*& assetMusic : musicAssets)
			if (!assetMusic->isLoaded()) 
				return false;
		return true;
	}

	///todo: describe
	void shufflePlaylist();

	///todo: describe
	QMediaPlayer* player;

private:
	///Names of the AssetMusics, so they can be loaded (if needed) and played
	QVector<QString> musicAssetsNames;
	///AssetMusics to be played
	QVector<AssetMusic*> musicAssets;

	///[low optional] Whether to randomize Music order
	bool bRandomize = false;

	///[low optional] Whether every Music should be played at least once
	bool bExclusive = false;

	///Common properties of Actions that manage Audio
	AudioSettings settings;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream& dataStream);
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream& dataStream) const;
};