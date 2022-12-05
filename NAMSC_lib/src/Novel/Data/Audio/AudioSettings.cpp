#include "Novel/Data/Audio/AudioSettings.h"

AudioSettings::AudioSettings(double volume, double stereo, int timesPlayed, uint delayBetweenReplays)
	: volume(volume), stereo(stereo), timesPlayed(timesPlayed), delayBetweenReplays(delayBetweenReplays)
{
	//checkForErrors(true);
}

AudioSettings& AudioSettings::operator=(AudioSettings obj) noexcept
{
	if (this == &obj) return *this;

	std::swap(*this, obj);
	
	return *this;
}

//bool AudioSettings::operator==(const AudioSettings& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return	volume              == obj.volume             &&
//			stereo              == obj.stereo             &&
//			timesPlayed         == obj.timesPlayed        &&
//			delayBetweenReplays == obj.delayBetweenReplays;
//}

bool AudioSettings::checkForErrors(bool bComprehensive) const
{
	bool bError = false;

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	//if (bError)
	//	qDebug() << "An Error occurred in Action::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return false;
}

void AudioSettings::serializableLoad(QDataStream& dataStream)
{
	dataStream >> volume >> stereo >> timesPlayed >> delayBetweenReplays;
	//checkForErrors();
}

void AudioSettings::serializableSave(QDataStream& dataStream) const
{
	dataStream << volume << stereo << timesPlayed << delayBetweenReplays;
}