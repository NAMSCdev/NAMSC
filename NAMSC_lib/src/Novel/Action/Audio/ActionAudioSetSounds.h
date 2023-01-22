#pragma once
#include "Novel/Action/Audio/ActionAudio.h"

#include <qhashfunctions.h>
#include <unordered_map> 

#include "Novel/Data/Audio/Sound.h"

/// Overwrites current `sounds` in the Scenery, which contains Sounds queued to be played after `startDelay` milliseconds have passed
class ActionAudioSetSounds final : public ActionAudio
{
	friend ActionVisitorCorrectSounds;
	/// Swap trick
	friend void swap(ActionAudioSetSounds& first, ActionAudioSetSounds& second) noexcept;
public:
	explicit ActionAudioSetSounds(Event* const parentEvent)   noexcept;
	/// \exception Error Couldn't find/read the SoundEffects' files
	ActionAudioSetSounds(Event* const parentEvent, const AudioSettings& audioSettings, const std::vector<Sound>& sounds = std::vector<Sound>());
	ActionAudioSetSounds(const ActionAudioSetSounds& obj)     noexcept;
	ActionAudioSetSounds(ActionAudioSetSounds&& obj)          noexcept;
	ActionAudioSetSounds& operator=(ActionAudioSetSounds obj) noexcept;
	bool operator==(const ActionAudioSetSounds& obj) const    noexcept;
	bool operator!=(const ActionAudioSetSounds& obj) const    noexcept = default;

	/// \exception Error Some of Sounds in `sounds` container are invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const override;

	void ensureResourcesAreLoaded();

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionAudioSetSounds's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Event* const parentEvent, const std::vector<Sound>* const sounds)> onRun) noexcept;

	const std::vector<Sound>* getSounds() const noexcept;
	/// \exception Error Tried to get a Sound past the `sounds_` container's size
	const Sound* getSound(uint index)     const;
	/// \exception Error Tried to get a Sound past the `sounds_` container's size
	Sound*       getSound(uint index);
	/// \exception Error Could not find a Sound with this name
	const Sound* getSound(const QString& soundName) const;
	/// \exception Error Could not find a Sound with this name
	Sound*       getSound(const QString& soundName);
	const std::vector<Sound>* setSounds(const std::vector<Sound>& sounds) noexcept;
	const std::vector<Sound>* setSounds(std::vector<Sound>&& sounds)      noexcept;
	//Sounds should be custom sorted
	/// \exception Error Tried to insert a Sound past the `sounds_` container's size
	//Sound* insertSound(uint index, const Sound& sound);
	/// \exception Error Tried to insert a Sound past the `sounds_` container's size
	//Sound* insertSound(uint index, Sound&& sound);
	/// \exception Error Tried to reinsert a Sound past the `sounds_` container's size
	//Sound* reinsertSound(uint index, uint newIndex);
	Sound* addSound(const Sound& sound);
	Sound* addSound(Sound&& sound);
	/// \exception Error Tried to remove a Sound past the `sounds_` container's size
	bool removeSound(uint index);
	/// \exception Error Could not find a Sound with this name
	bool removeSound(const QString& soundName);
	void clearSounds() noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;
	
	/// A function pointer that is called (if not nullptr) after the ActionAudioSetSounds's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Event* const parentEvent, const std::vector<Sound>* const sounds)> onRun_ = nullptr;

	std::vector<Sound> sounds_;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};