#pragma once
#include <QDataStream>

/// Common properties for Audio playing
struct AudioSettings final
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, AudioSettings&);
	friend QDataStream& operator<<(QDataStream&, const AudioSettings&);

	AudioSettings()                                 = default;
	AudioSettings(double volume, double stereo, int timesPlayed, uint delayBetweenReplays);
	AudioSettings(const AudioSettings& obj)         = default;
 	AudioSettings& operator=(AudioSettings obj) noexcept;
	bool operator==(const AudioSettings& obj) const = default;
	bool operator!=(const AudioSettings& obj) const = default; //{ return !(*this == obj); }

	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const;
	
	double volume            = 1.0;

	/// How the Sound is played in the stereo headphones
	/// 0.0 - left only, 0.5 - both, 1.0 - right only
	/// Accepted values: 0.0 - 1.0
	/// \todo [optional] Allow more channels
	double stereo            = 0.5;

	/// Can be set to -1, so it will be looped infinitely
	int	timesPlayed          = 1;

	/// How much time in millisecond passes before next repetition of this Audio
	uint delayBetweenReplays = 0;

private:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};