#include "pvnLib/Novel/Data/Audio/MusicPlaylist.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(MusicPlaylist& first, MusicPlaylist& second) noexcept
{
	using std::swap;
	swap(first.songs,                  second.songs);
	swap(first.audioSettings,          second.audioSettings);
	swap(first.bRandomizePlaylist,     second.bRandomizePlaylist);
	swap(first.currentlyPlayedSongID_, second.currentlyPlayedSongID_);
}

MusicPlaylist::MusicPlaylist(const std::vector<std::pair<QString, QString>>& songs, AudioSettings audioSettings, bool bRandomizePlaylist, int currentlyPlayedSongID)
	: songs(songs),
	audioSettings(audioSettings),
	bRandomizePlaylist(bRandomizePlaylist),
	currentlyPlayedSongID_(currentlyPlayedSongID)
{
	errorCheck(true);
}

//defaulted
//MusicPlaylist::MusicPlaylist(const MusicPlaylist& obj) noexcept
//	: songs(obj.songs),
//	audioSettings(obj.audioSettings),
//	bRandomizePlaylist(obj.bRandomizePlaylist),
//	currentlyPlayedSongID_(obj.currentlyPlayedSongID_)
//{
//}

bool MusicPlaylist::operator==(const MusicPlaylist& obj) const noexcept
{
	if (this == &obj) return true;

	return songs              == obj.songs              &&
		   audioSettings      == obj.audioSettings      &&
		   bRandomizePlaylist == obj.bRandomizePlaylist;     //&&
	//currentlyPlayedSongID_  == obj.currentlyPlayedSongID_;
}

void MusicPlaylist::serializableLoad(QDataStream& dataStream)
{
	dataStream >> audioSettings /* >> songs*/ >> bRandomizePlaylist >> currentlyPlayedSongID_;
}

void MusicPlaylist::serializableSave(QDataStream& dataStream) const
{
	dataStream << audioSettings /* << songs */ << bRandomizePlaylist << currentlyPlayedSongID_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

//defaulted
//MusicPlaylist::MusicPlaylist(MusicPlaylist&& obj) noexcept
//	: MusicPlaylist()
//{
//	swap(*this, obj);
//}

//defaulted
//MusicPlaylist& MusicPlaylist::operator=(MusicPlaylist obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}