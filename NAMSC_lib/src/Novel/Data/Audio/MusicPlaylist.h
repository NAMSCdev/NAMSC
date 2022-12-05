#pragma once

#include <vector>

#include "Novel/Data/Audio/AudioSettings.h"
#include "Novel/Data/Asset/AssetManager.h"

/// List of Songs that can be played in the background
class MusicPlaylist final
{
	friend class ActionVisitorCorrectMusicPlaylist;
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, MusicPlaylist&);
	friend QDataStream& operator<<(QDataStream&, const MusicPlaylist&);
public:
	MusicPlaylist()                                 = default;
	/// \exception Error Couldn't find/read the Song files
	MusicPlaylist(const std::vector<std::pair<QString, QString>>& songFilesPaths, AudioSettings audioSettings, bool bRandomizePlaylist);
	MusicPlaylist(const MusicPlaylist& obj) noexcept;
	MusicPlaylist& operator=(MusicPlaylist obj) noexcept;
	bool operator==(const MusicPlaylist& obj) const noexcept;
	bool operator!=(const MusicPlaylist& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error Paths in `audioFilesPaths` are invalid / some Songs cannot be read (whatever the reason)
	/// \return Whether an Error has occurred
	/// \todo check if the format is right
	bool checkForErrors(bool bComprehensive = false) const;

	/// \todo QT random replace
	const std::pair<QString, QString> nextSong();

	AudioSettings audioSettings;

	/// Contains pairs of `<name, path>`
	std::vector<std::pair<QString, QString>> songs;

	bool bRandomizePlaylist    = false;

private:
	int currentlyPlayedSongID_ = -1;
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};