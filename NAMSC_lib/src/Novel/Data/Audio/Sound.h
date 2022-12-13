#pragma once

#include <QString>

#include "Novel/Data/Audio/AudioSettings.h"

class ActionVisitorCorrectSounds;

/// Holds data for QSoundEffect, to play some Sound
struct Sound final
{
	friend ActionVisitorCorrectSounds;
public:
	Sound()                                 = default;
	/// \exception Error Couldn't find/read the File under `soundFilePath`
	Sound(const QString& name, const QString& soundFilePath, AudioSettings audioSettings, uint startDelay, bool bPersistToNewEvent);
	Sound(const Sound& obj)                 = default;
	Sound& operator=(Sound obj) noexcept;
	bool operator==(const Sound& obj) const noexcept;
	bool operator!=(const Sound& obj) const = default;

	/// \todo Setup audioSettings as well
	/// \todo Connect with our new class
	void load();// if (!qSoundEffect_) qSoundEffect_ = std::unique_ptr<QSoundEffect>(new QSoundEffect()); qSoundEffect_->setSource(soundFilePath);
	/// \todo Connect with our new class
	bool isLoaded() const;// return qSoundEffect_ != nullptr; }
	/// \todo Connect with our new class
	void unload();// qSoundEffect_.clear(); }

	/// \exception Error `soundFilePath` is invalid / Sound File's content cannot be read (whatever the reason)
	/// \return Whether an Error has occurred
	/// \todo check if the format is right
	bool checkForErrors(bool bComprehensive = false) const;

	QString name            = "";

	//QString soundAssetName
	/// \todo Replace with some kind of SoundAsset
	QString soundFilePath   = "";

	AudioSettings audioSettings;

	/// In milliseconds
	uint startDelay         = 0;

	/// Whether the Sound should be cut if user gets to the next Scene's Event before this SoundEffect has ended playing
	bool bPersistToNewEvent = false;

private:
	//std::unique_ptr<QSoundEffect> qSoundEffect_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};