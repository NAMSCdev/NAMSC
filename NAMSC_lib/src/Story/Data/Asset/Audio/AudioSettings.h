#pragma once

///Common properties of Actions that manage Audio
struct AudioSettings
{
	AudioSettings() = default;
	AudioSettings(double volume, double stereo, int timesPlayed) :
		volume(volume), stereo(stereo), timesPlayed(timesPlayed) {}

	///Volume of the played Sound
	double volume = 1.0;

	///How the Sound is played in stereo headphones
	///0.0 - left only, 0.5 - both, 1.0 - right only
	///Accepted values: 0.0 - 1.0
	///@todo [optional] Allow more channels
	///[ensure todo] implement this
	double stereo = 0.5;

	///How many times it will be played
	///Can be set to -1, so it will be played infinite amount of times
	int	timesPlayed = 1;
};