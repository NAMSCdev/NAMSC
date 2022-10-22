#pragma once
#include "Global.h"

#include "Novel/Action/Action.h"
#include "Novel/Data/Audio/AudioSettings.h"
#include "Novel/Data/Asset/Type/AssetAudio.h"

/// Contains common properties of Actions that manage Audio
class ActionAudio : public Action
{
public:
	ActionAudio() noexcept = default;
	ActionAudio(AudioSettings settings, QVector<QString>&& assetAudioNames);
	ActionAudio(double volume, double stereo, int timesPlayed, uint delayBetweenReplays, QVector<QString>&& assetAudioNames);
	ActionAudio(const ActionAudio& obj) noexcept { *this = obj; }
	ActionAudio& operator=(const ActionAudio& obj) noexcept;

protected:
	/// Common properties of Actions that manage Audio
	AudioSettings settings;

	/// Names of the AssetAudio objects, so they can be loaded when needed
	QVector<QString> assetAudioNames;
	/// AssetAudio to be played
	QVector<AssetAudio*> assetAudioList;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const override;
};




inline ActionAudio::ActionAudio(AudioSettings settings, QVector<QString>&& assetAudioNames) :
	Action(), settings(settings), assetAudioNames(move(assetAudioNames))
{
}

inline ActionAudio::ActionAudio(double volume, double stereo, int timesPlayed, uint delayBetweenReplays, QVector<QString>&& assetAudioNames) :
	ActionAudio(AudioSettings(volume, stereo, timesPlayed, delayBetweenReplays), move(assetAudioNames))
{
}

inline ActionAudio& ActionAudio::operator=(const ActionAudio& obj)
{
	if (this == &obj) return *this;

	Action::operator=(obj);
	settings        = obj.settings;
	assetAudioNames = obj.assetAudioNames;
	assetAudioList  = obj.assetAudioList;

	return *this;
}