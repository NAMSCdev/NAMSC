#pragma once
#include "Novel/Action/Audio/ActionAudio.h"

#include "Novel/Data/Audio/MusicPlaylist.h"

/// Overwrites current `sounds` in the Scenery, which contains Sounds queued to be played after `startDelay` milliseconds have passed
class ActionAudioSetMusic final : public ActionAudio
{
	friend class ActionVisitorCorrectMusicPlaylist;
public:
	ActionAudioSetMusic(Event* const parentEvent) noexcept;
	/// \exception Error Files in `musicPlaylist_.audioFilesPaths_` couldn't be found/read
	ActionAudioSetMusic(Event* const parentEvent, const AudioSettings& audioSettings, const MusicPlaylist& playlist);
	ActionAudioSetMusic(const ActionAudioSetMusic& obj) noexcept;
	ActionAudioSetMusic& operator=(const ActionAudioSetMusic& obj) noexcept;
	bool operator==(const ActionAudioSetMusic& obj) const noexcept;
	bool operator!=(const ActionAudioSetMusic& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error Paths in `musicPlaylist_.audioFilesPaths_` are invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const override;

	Action* clone() const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionAudioSetMusic's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, MusicPlaylist* musicPlaylist)> onRun) noexcept;

	const MusicPlaylist* getMusicPlaylist() const noexcept;
	MusicPlaylist* getMusicPlaylist() noexcept;
	void setMusicPlaylist(const MusicPlaylist& musicPlaylist) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

private:

	MusicPlaylist musicPlaylist_;

	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the ActionAudioSetMusic's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, MusicPlaylist* musicPlaylist)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};