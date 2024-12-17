#include "pvnLib/Novel/Data/Audio/MusicPlaylist.h"
#include "pvnLib/Novel/Data/Audio/Sound.h"

#include <random>

const std::pair<QString, QString> MusicPlaylist::nextSong()
{
	if (!songs.size())
		return std::pair<QString, QString>();
	if (currentlyPlayedSongID_ == -1)
		return songs[currentlyPlayedSongID_ = 0];

	if (++currentlyPlayedSongID_ > songs.size())
	{
		if (bRandomizePlaylist && songs.size() > 1)
		{
			std::pair<QString, QString> previous = songs[(currentlyPlayedSongID_ == 0) ? (songs.size() - 1) : (currentlyPlayedSongID_ - 1)];
			std::random_device randomDevice;
			std::mt19937 generator(randomDevice());
			do
				std::shuffle(songs.begin(), songs.end(), generator);
			while (songs[0] == previous);
		}
		currentlyPlayedSongID_ = 0;
	}
	return songs[currentlyPlayedSongID_];
}

void Sound::load()
{
}

bool Sound::isLoaded() const
{
	return true;
}

void Sound::unload()
{
}