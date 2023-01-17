#include "Novel/Data/Audio/Sound.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(Sound& first, Sound& second) noexcept
{
	using std::swap;

	swap(first.name,               second.name);
	swap(first.soundFilePath,      second.soundFilePath);
	swap(first.audioSettings,      second.audioSettings);
	swap(first.startDelay,         second.startDelay);
	swap(first.bPersistToNewEvent, second.bPersistToNewEvent);
}

Sound::Sound(const QString &name, const QString& soundFilePath, AudioSettings audioSettings, uint startDelay, bool bPersistToNewEvent)
	: name(name),
	soundFilePath(soundFilePath), 
	audioSettings(audioSettings), 
	startDelay(startDelay),
	bPersistToNewEvent(bPersistToNewEvent)
{
	//errorCheck(true);
}

//defaulted
//Sound::Sound(const Sound& obj) noexcept
//	: name(obj.name),
//	soundFilePath(obj.soundFilePath), 
//	audioSettings(obj.audioSettings), 
//	startDelay(obj.startDelay), 
//	bPersistToNewEvent(obj.bPersistToNewEvent)
//{
//}

//defaulted
//bool Sound::operator==(const Sound& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return name               == obj.name               &&
//	       soundFilePath      == obj.soundFilePath      &&
//		   audioSettings      == obj.audioSettings		&&
//		   startDelay         == obj.startDelay		    &&
//		   bPersistToNewEvent == obj.bPersistToNewEvent;
//}

void Sound::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> soundFilePath >> audioSettings >> startDelay >> bPersistToNewEvent;
}

void Sound::serializableSave(QDataStream& dataStream) const
{
	dataStream << name << soundFilePath << audioSettings << startDelay << bPersistToNewEvent;
}

//  MEMBER_FIELD_SECTION_CHANGE END

//defaulted
//Sound::Sound(Sound&& obj) noexcept
//	: Sound()
//{
//	swap(*this, obj);
//}

//defaulted
//Sound& Sound::operator=(Sound obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}