#include "Novel/Data/Audio/AudioSettings.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(AudioSettings& first, AudioSettings& second) noexcept
{
	using std::swap;

	swap(first.volume,              second.volume);
	swap(first.stereo,              second.stereo);
	swap(first.timesPlayed,         second.timesPlayed);
	swap(first.delayBetweenReplays, second.delayBetweenReplays);
}

AudioSettings::AudioSettings(double volume, double stereo, int timesPlayed, uint delayBetweenReplays)
	: volume(volume),
	stereo(stereo), 
	timesPlayed(timesPlayed), 
	delayBetweenReplays(delayBetweenReplays)
{
	errorCheck(true);
}

//defaulted
//AudioSettings::AudioSettings(const AudioSettings& obj) noexcept
//	: volume(obj.volume),
//	stereo(obj.stereo),
//	timesPlayed(obj.timesPlayed),
//	delayBetweenReplays(obj.delayBetweenReplays)
//{
//}

//defaulted
//bool AudioSettings::operator==(const AudioSettings& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return	volume              == obj.volume             &&
//			stereo              == obj.stereo             &&
//			timesPlayed         == obj.timesPlayed        &&
//			delayBetweenReplays == obj.delayBetweenReplays;
//}

void AudioSettings::serializableLoad(QDataStream& dataStream)
{
	dataStream >> volume >> stereo >> timesPlayed >> delayBetweenReplays;
}

void AudioSettings::serializableSave(QDataStream& dataStream) const
{
	dataStream << volume << stereo << timesPlayed << delayBetweenReplays;
}

//  MEMBER_FIELD_SECTION_CHANGE END

//defaulted
//AudioSettings::AudioSettings(AudioSettings&& obj) noexcept
//	: AudioSettings()
//{
//	swap(*this, obj);
//}

//defaulted
//AudioSettings& AudioSettings::operator=(AudioSettings obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}