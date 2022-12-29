#include "Novel/Data/Audio/MusicPlaylist.h"

#include <QMediaPlayer>
#include <QFile>
#include <random>

#include "Exceptions.h"

MusicPlaylist::MusicPlaylist(const std::vector<std::pair<QString, QString>>& songFilesPaths, AudioSettings audioSettings, bool bRandomizePlaylist) 
	: songs(songs), audioSettings(audioSettings), bRandomizePlaylist(bRandomizePlaylist)
{
	checkForErrors(true);
}

MusicPlaylist::MusicPlaylist(const MusicPlaylist& obj) noexcept
	: songs(obj.songs),
	  audioSettings(obj.audioSettings),
	  bRandomizePlaylist(obj.bRandomizePlaylist)// ,
	//currentlyPlayedSongID_(obj.currentlyPlayedSongID_);
{
}

MusicPlaylist& MusicPlaylist::operator=(MusicPlaylist obj) noexcept
{
	if (this == &obj) return *this;

	std::swap(this->songs,              obj.songs);
	std::swap(this->audioSettings,      obj.audioSettings);
	std::swap(this->bRandomizePlaylist, obj.bRandomizePlaylist);

	return *this;
}

bool MusicPlaylist::operator==(const MusicPlaylist& obj) const noexcept
{
	if (this == &obj) return true;

	return	songs                  == obj.songs              &&
		    audioSettings          == obj.audioSettings      &&
			bRandomizePlaylist     == obj.bRandomizePlaylist;     //&&
			//currentlyPlayedSongID_  == obj.currentlyPlayedSongID_;
}

bool MusicPlaylist::checkForErrors(bool bComprehensive) const
{
	bool bError = false;
	static auto errorChecker = [&](bool bComprehensive)
	{
		for (const std::pair<QString, QString>& song : songs)
		{
			//Check if the path is undefined
			if (song.second == "")
			{
				bError = true;
				qCritical() << this << NovelLib::ErrorType::AudioInvalid << "No Song file assigned. Was it deleted and not replaced?";
			}

			//Check if the File is still there in the User's filesystem
			if (!QFile::exists(song.second))
			{
				bError = true;
				qCritical() << this << NovelLib::ErrorType::AudioFileMissing << "Could not find a Song file \"" << song.second << "\"";
			}

			if (bComprehensive)
			{
				QMediaPlayer player;
				//TODO: check if this will ensure the format is right
				player.setSource(song.second);
			}
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "An Error occurred in MusicPlaylist::checkForErrors";

	return bError;
}

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

void MusicPlaylist::serializableLoad(QDataStream& dataStream)
{
	dataStream >> audioSettings /* >> songs*/ >> bRandomizePlaylist >> currentlyPlayedSongID_;
	//checkForErrors();
}

void MusicPlaylist::serializableSave(QDataStream& dataStream) const
{
	dataStream << audioSettings /* << songs */ << bRandomizePlaylist << currentlyPlayedSongID_;
}