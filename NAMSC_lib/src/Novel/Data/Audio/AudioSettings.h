#pragma once

///Common properties of Actions that manage Audio
class AudioSettings
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, AudioSettings&);
	friend QDataStream& operator<<(QDataStream&, const AudioSettings&);
public:
	AudioSettings() = default;
	AudioSettings(double volume, double stereo, int timesPlayed, uint delayBetweenReplays) :
		volume(volume), stereo(stereo), timesPlayed(timesPlayed), delayBetweenReplays(delayBetweenReplays) {}
	AudioSettings(const AudioSettings& obj) { *this = obj; }
	AudioSettings& operator=(const AudioSettings& obj)
	{
		if (this == &obj) return *this;

		volume              = obj.volume;
		stereo              = obj.stereo;
		timesPlayed         = obj.timesPlayed;
		delayBetweenReplays = obj.delayBetweenReplays;

		return *this;
	}
	///Volume of the played Sound
	double volume   = 1.0;

	///How the Sound is played in stereo headphones
	///0.0 - left only, 0.5 - both, 1.0 - right only
	///Accepted values: 0.0 - 1.0
	///@todo [optional] Allow more channels
	///[ensure todo] implement this
	double stereo   = 0.5;

	///How many times it will be played
	///Can be set to -1, so it will be looped infinitely
	int	timesPlayed = 1;

	///How much time in millisecond passes before next repetition of this Audio
	uint delayBetweenReplays = 0;

private:
	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream& dataStream);
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream& dataStream) const;
};