#pragma once

#include <vector>

#include "pvnLib/Novel/Data/Audio/AudioSettings.h"
#include "pvnLib/Novel/Data/Asset/AssetManager.h"

/// List of Songs that can be played in the background
class MusicPlaylist final
{
	friend class ActionVisitorCorrectMusicPlaylist;
	/// Swap trick
	friend void swap(MusicPlaylist& first, MusicPlaylist& second) noexcept;
public:
	MusicPlaylist()                                    noexcept = default;
	/// \param songs Contains pairs of `<name, path>`
	/// \exception Error Couldn't find/read the Song files
	explicit MusicPlaylist(const std::vector<std::pair<QString, QString>>& songs, AudioSettings audioSettings = AudioSettings(), bool bRandomizePlaylist = false, int currentlyPlayedSongID_ = -1);
	MusicPlaylist(const MusicPlaylist& obj)            noexcept = default;
	MusicPlaylist(MusicPlaylist&& obj)                 noexcept = default;
	MusicPlaylist& operator=(const MusicPlaylist& obj) noexcept = default;
	//MusicPlaylist& operator=(MusicPlaylist obj)        noexcept;
	bool operator==(const MusicPlaylist& obj) const    noexcept;
	bool operator!=(const MusicPlaylist& obj) const    noexcept = default;

	/// \exception Error Paths in `audioFilesPaths` are invalid / some Songs cannot be read (whatever the reason)
	/// \return Whether an Error has occurred
	/// \todo check if the format is right
	bool errorCheck(bool bComprehensive = false) const;

	/// \todo QT random replace
	const std::pair<QString, QString> nextSong();

	AudioSettings audioSettings;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Contains pairs of `<name, path>`
	std::vector<std::pair<QString, QString>> songs;

	bool bRandomizePlaylist    = false;

private:
	int currentlyPlayedSongID_ = -1;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};