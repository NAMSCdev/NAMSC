#pragma once
#include "Novel/Action/Audio/ActionAudio.h"

#include <QHash>

#include "Novel/Data/Audio/Sound.h"

/// Overwrites current `sounds` in the Scenery, which contains Sounds queued to be played after `startDelay` milliseconds have passed
class ActionAudioSetSounds final : public ActionAudio
{
	friend class ActionVisitorCorrectSounds;
public:
	ActionAudioSetSounds(Event* const parentEvent, Scene* const parentScene) noexcept;
	/// \exception Error Couldn't find/read the SoundEffects' files
	ActionAudioSetSounds(Event* const parentEvent, Scene* const parentScene, const AudioSettings& audioSettings, const QHash<QString, Sound>& sounds);
	ActionAudioSetSounds(const ActionAudioSetSounds& obj) = delete;
	ActionAudioSetSounds& operator=(const ActionAudioSetSounds& obj) noexcept;
	bool operator==(const ActionAudioSetSounds& obj) const noexcept;
	bool operator!=(const ActionAudioSetSounds& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error Some of Sounds in `sounds` container are invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const;

	void ensureResourcesAreLoaded();

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionAudioSetSounds's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QHash<QString, Sound>* sound)> onRun) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

	QHash<QString, Sound> sounds;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;
	
	/// A function pointer that is called (if not nullptr) after the ActionAudioSetSounds's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, QHash<QString, Sound>* sound)> onRun_ = nullptr;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};