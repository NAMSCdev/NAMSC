#include "Novel/Data/Audio/Sound.h"

#include <QFile>

#include "Exceptions.h"

Sound::Sound(const QString &name, const QString& soundFilePath, AudioSettings audioSettings, uint startDelay, bool bPersistToNewEvent)
	: name(name), soundFilePath(soundFilePath), audioSettings(audioSettings), startDelay(startDelay), bPersistToNewEvent(bPersistToNewEvent)
{
	checkForErrors(true);
}

//Sound::Sound(const Sound& obj) noexcept
//	: soundFilePath(obj.soundFilePath), 
//	  audioSettings(obj.audioSettings), 
//	  startDelay(obj.startDelay), 
//	  bPersistToNewEvent(obj.bPersistToNewEvent)
//	  //qSoundEffect_(qSoundEffect)
//{
//}

Sound& Sound::operator=(Sound obj) noexcept
{ 
	if (this == &obj) return *this;

	std::swap(*this, obj); 
	
	return *this; 
}

bool Sound::operator==(const Sound& obj) const noexcept
{
	if (this == &obj) return true;

	return	soundFilePath      == obj.soundFilePath      &&
			audioSettings      == obj.audioSettings		 &&
			startDelay         == obj.startDelay		 &&
			bPersistToNewEvent == obj.bPersistToNewEvent; //&&
			//qSoundEffect_      == obj.qSoundEffect_;
}

void Sound::load() 
{
}

bool Sound::isLoaded() const 
{
	return true;
}

void Sound::unload() 
{
}

bool Sound::checkForErrors(bool bComprehensive) const
{
	bool bError = false;
	static auto errorChecker = [&](bool bComprehensive)
	{
		//Check if the name is undefined
		if (soundFilePath == "")
		{
			qCritical() << this << NovelLib::ErrorType::AudioInvalid << "No Sound file assigned. Was it deleted and not replaced?";
			bError = true;
		}

		//Check if the File is still there in the User's filesystem
		if (!QFile::exists(soundFilePath))
		{
			qCritical() << this << NovelLib::ErrorType::AudioFileMissing << "Could not find a Sound file \"" << soundFilePath << "\"";
			bError = true;
		}

		if (bComprehensive)
		{
			//todo: do checking in our new class
			//QSoundEffect effect;
			//TODO: check if this will ensure the format is right
			//effect.setSource(soundFilePath);
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "An Error occurred in Sound::checkForErrors";

	return bError;
}

void Sound::serializableLoad(QDataStream& dataStream)
{
	dataStream >> soundFilePath >> audioSettings >> startDelay >> bPersistToNewEvent;
	//checkForErrors();
}

void Sound::serializableSave(QDataStream& dataStream) const
{
	dataStream << soundFilePath << audioSettings << startDelay << bPersistToNewEvent;
}