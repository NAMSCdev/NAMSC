#pragma once

#include <QDataStream>

#include "Serialization.h"

/// Common properties for Audio playing
class AudioSettings final
{
	/// Swap trick
	friend void swap(AudioSettings& first, AudioSettings& second) noexcept;

public:
	AudioSettings()                                    noexcept = default;
	/// \param stereo How the Sound is played in the stereo headphones
	/// \param timesPlayed Can be set to -1, so it will be looped infinitely
	/// \param delayBetweenReplays How much time in millisecond passes before next repetition of this Audio
	explicit AudioSettings(double volume, double stereo = 0.5, int timesPlayed = 1, uint delayBetweenReplays = 0);
	AudioSettings(const AudioSettings& obj)            noexcept = default;
	AudioSettings(AudioSettings&& obj)                 noexcept = default;
	AudioSettings& operator=(const AudioSettings& obj) noexcept = default;
	//AudioSettings& operator=(AudioSettings obj)        noexcept;
	bool operator==(const AudioSettings& obj) const    noexcept = default;
	bool operator!=(const AudioSettings& obj) const    noexcept = default;

	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const;
	
	double volume            = 0.7;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// How the Sound is played in the stereo headphones
	/// 0.0 - left only, 0.5 - both, 1.0 - right only
	/// Accepted values: 0.0 - 1.0
	/// \todo [optional] Allow more channels
	double stereo            = 0.5;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Can be set to -1, so it will be looped infinitely
	int	timesPlayed          = 1;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// How much time in millisecond passes before next repetition of this Audio
	uint delayBetweenReplays = 0;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};