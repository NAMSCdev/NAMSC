#pragma once
#include "pvnLib/Novel/Action/Audio/ActionAudio.h"

#include "pvnLib/Novel/Data/Audio/MusicPlaylist.h"

/// Overwrites current `sounds` in the Scenery, which contains Sounds queued to be played after `startDelay` milliseconds have passed
class ActionAudioSetMusic final : public ActionAudio
{
	friend class ActionVisitorCorrectMusicPlaylist;
	/// Swap trick
	friend void swap(ActionAudioSetMusic& first, ActionAudioSetMusic& second) noexcept;
public:
	explicit ActionAudioSetMusic(Event* const parentEvent)  noexcept;
	/// \exception Error Files in `musicPlaylist_.audioFilesPaths_` couldn't be found/read
	ActionAudioSetMusic(Event* const parentEvent, const AudioSettings& audioSettings, const MusicPlaylist& playlist = MusicPlaylist());
	ActionAudioSetMusic(const ActionAudioSetMusic& obj)     noexcept;
	ActionAudioSetMusic(ActionAudioSetMusic&& obj)          noexcept;
	ActionAudioSetMusic& operator=(ActionAudioSetMusic obj) noexcept;
	bool operator==(const ActionAudioSetMusic& obj) const   noexcept;
	bool operator!=(const ActionAudioSetMusic& obj) const   noexcept = default;

	/// \exception Error Paths in `musicPlaylist_.audioFilesPaths_` are invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionAudioSetMusic's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Event* const parentEvent, const MusicPlaylist* const musicPlaylist)> onRun) noexcept;

	const MusicPlaylist* getMusicPlaylist() const             noexcept;
	MusicPlaylist*       getMusicPlaylist()                   noexcept;
	void setMusicPlaylist(const MusicPlaylist& musicPlaylist) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

private:
	MusicPlaylist musicPlaylist_;

	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the ActionAudioSetMusic's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Event* const parentEvent, const MusicPlaylist* const musicPlaylist)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};