#pragma once
#include "Novel/Action/Action.h"

#include "Novel/Data/Audio/AudioSettings.h"

/// Contains common properties of Actions that manage Audio
class ActionAudio : public Action
{
	/// Swap trick
	friend void swap(ActionAudio& first, ActionAudio& second) noexcept;
public:
	explicit ActionAudio(Event* const parentEvent, const AudioSettings& audioSettings = AudioSettings());
	bool operator==(const ActionAudio& obj) const noexcept;
	bool operator!=(const ActionAudio& obj) const noexcept = default;
	//Makes it abstract
	virtual ~ActionAudio() = 0;

	/// \return Whether an Error has occurred
	virtual bool errorCheck(bool bComprehensive = false) const override;
	
	const AudioSettings& getAudioSettings() const             noexcept;
	AudioSettings&       getAudioSettings()                   noexcept;
	void setAudioSettings(const AudioSettings& audioSettings) noexcept;

protected:
	AudioSettings audioSettings_;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const override;
};