#pragma once
#include "Global.h"
#include "Story/Data/Asset/AssetManager.h"

class MusicPlaylist {
	MusicPlaylist() = default;
	MusicPlaylist(MusicPlaylist& obj) {
		*this = obj;
	}
	MusicPlaylist& operator=(const MusicPlaylist& obj) {
		if (this == &obj) return *this;

		musicAssetsNames = obj.musicAssetsNames;
		musicAssets = obj.musicAssets;
		bRandomize = obj.bRandomize;
		bExclusive = obj.bExclusive;

		return *this;
	}

	///Names of the MusicAssets, so they can be loaded (if needed) and played
	QVector<QString> musicAssetsNames;
	///MusicAssets to be played
	QVector<MusicAsset*>musicAssets;

	///[low optional] Whether to randomize Music order
	bool bRandomize = false;

	///[low optional] Whether every Music should be played at least once
	bool bExclusive = false;
};