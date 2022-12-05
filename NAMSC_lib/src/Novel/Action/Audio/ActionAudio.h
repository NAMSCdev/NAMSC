#pragma once
#include "Novel/Action/Action.h"

#include "Novel/Data/Audio/AudioSettings.h"

/// Contains common properties of Actions that manage Audio
class ActionAudio : public Action
{
public:
	ActionAudio(Event* const parentEvent, Scene* const parentScene) noexcept;
	ActionAudio(Event* const parentEvent, Scene* const parentScene, const AudioSettings& audioSettings);
	ActionAudio(const ActionAudio& obj) = delete;
	ActionAudio& operator=(const ActionAudio& obj) noexcept;
	bool operator==(const ActionAudio& obj) const noexcept;
	bool operator!=(const ActionAudio& obj) const = default; //{ return !(*this == obj); }

	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive) const;
	
	const AudioSettings& getAudioSettings() const noexcept;
	AudioSettings& getAudioSettings() noexcept;
	void setAudioSettings(const AudioSettings& audioSettings) noexcept;

protected:
	AudioSettings audioSettings_;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const override;
};