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
	explicit ActionAudioSetSounds(Event* const parentEvent)          noexcept;
	/// \exception Error Couldn't find/read the SoundEffects' files
	ActionAudioSetSounds(Event* const parentEvent, const AudioSettings& audioSettings, const std::unordered_map<QString, Sound>& sounds = std::unordered_map<QString, Sound>());
	ActionAudioSetSounds(const ActionAudioSetSounds& obj)            noexcept = delete;
	ActionAudioSetSounds(ActionAudioSetSounds&& obj)                 noexcept;
	ActionAudioSetSounds& operator=(const ActionAudioSetSounds& obj) noexcept = delete;
	//ActionAudioSetSounds& operator=(ActionAudioSetSounds obj)        noexcept;
	bool operator==(const ActionAudioSetSounds& obj) const           noexcept = delete;
	bool operator!=(const ActionAudioSetSounds& obj) const           noexcept = delete;

	/// \exception Error Some of Sounds in `sounds` container are invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const override;

	void ensureResourcesAreLoaded();

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionAudioSetSounds's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Event* const parentEvent, const std::unordered_map<QString, Sound>* const sounds)> onRun) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

	/// TODO: make it private and create setters/getters
	std::unordered_map<QString, Sound> sounds;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;
	
	/// A function pointer that is called (if not nullptr) after the ActionAudioSetSounds's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Event* const parentEvent, const std::unordered_map<QString, Sound>* const sounds)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};