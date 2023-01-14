#include "Novel/Data/Text/Sentence.h"

#include "Novel/Data/Novel.h"
#include "Novel/Data/Scene.h"

Sentence::Sentence(Event* const parentEvent)
	: parentEvent(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(Sentence& first, Sentence& second) noexcept
{
	using std::swap;
	swap(first.text,                   second.text);
	swap(first.displayedName,          second.displayedName);
	swap(first.characterName_,         second.characterName_);
	swap(first.voiceName_,             second.voiceName_);
	swap(first.assetImageName_,        second.assetImageName_);
	swap(first.cpsMultiplier,          second.cpsMultiplier);
	swap(first.cpsOverwrite,           second.cpsOverwrite);
	swap(first.bEndWithInput,          second.bEndWithInput);
	swap(first.waitBeforeContinueTime, second.waitBeforeContinueTime);
	swap(first.character_,             second.character_);
	swap(first.voice_,                 second.voice_);
	swap(first.assetImage_,            second.assetImage_);
}

Sentence::Sentence(Event* const parentEvent, const Translation& text, const QString& displayedName, const QString& characterName, const QString& voiceName, const QString& assetImageName, double cpsMultiplier, uint cpsOverwrite, bool bEndWithInput, uint waitBeforeContinueTime, Character* character, Voice* voice, AssetImage* assetImage)
	: parentEvent(parentEvent), 
	text(text), 
	displayedName(displayedName), 
	characterName_(characterName), 
	voiceName_(voiceName), 
	assetImageName_(assetImageName), 
	cpsMultiplier(cpsMultiplier), 
	cpsOverwrite(cpsOverwrite), 
	bEndWithInput(bEndWithInput), 
	waitBeforeContinueTime(waitBeforeContinueTime),
	character_(character),
	voice_(voice),
	assetImage_(assetImage)
{
	errorCheck(true);
}

Sentence::Sentence(const Sentence& obj) noexcept
	: parentEvent(obj.parentEvent),
	text(obj.text),
	displayedName(obj.displayedName),
	characterName_(obj.characterName_),
	voiceName_(obj.voiceName_),
	assetImageName_(obj.assetImageName_),
	cpsMultiplier(obj.cpsMultiplier),
	cpsOverwrite(obj.cpsOverwrite),
	bEndWithInput(obj.bEndWithInput),
	waitBeforeContinueTime(obj.waitBeforeContinueTime),
	character_(obj.character_),
	voice_(obj.voice_),
	assetImage_(obj.assetImage_)
{
}

bool Sentence::operator==(const Sentence& obj) const noexcept
{
	if (this == &obj) return true;

	return text                   == obj.text                   &&
		   displayedName          == obj.displayedName          &&
		   characterName_         == obj.characterName_         &&
		   voiceName_             == obj.voiceName_             &&
		   assetImageName_        == obj.assetImageName_        &&
		   cpsMultiplier          == obj.cpsMultiplier          &&
		   cpsOverwrite           == obj.cpsOverwrite           &&
		   bEndWithInput          == obj.bEndWithInput          &&
		   waitBeforeContinueTime == obj.waitBeforeContinueTime;
}

void Sentence::serializableLoad(QDataStream& dataStream)
{
	dataStream >> text >> displayedName >> characterName_ >> voiceName_ >> assetImageName_ >> cpsMultiplier >> cpsOverwrite >> bEndWithInput >> waitBeforeContinueTime;

	//voice_ = Novel::getInstance().getVoice(voiceName_);
}

void Sentence::serializableSave(QDataStream& dataStream) const
{
	dataStream << text << displayedName << characterName_ << voiceName_ << assetImageName_ << cpsMultiplier << cpsOverwrite << bEndWithInput << waitBeforeContinueTime;
}

//  MEMBER_FIELD_SECTION_CHANGE END

Sentence::Sentence(Sentence&& obj) noexcept
	: Sentence(obj.parentEvent)
{
	swap(*this, obj);
}

Sentence& Sentence::operator=(Sentence obj) noexcept
{
	if (this == &obj) return *this;

	return *this;
}

QString Sentence::getAssetImageName() const noexcept
{
	return assetImageName_;
}

const AssetImage* Sentence::getAssetImage() const noexcept
{
	return assetImage_;
}

AssetImage* Sentence::getAssetImage() noexcept
{ 
	return assetImage_; 
}

void Sentence::setAssetImage(const QString& assetImageName, AssetImage* assetImage) noexcept
{
	if (assetImage)
	{
		if (assetImage->name != assetImageName)
		{
			qCritical() << NovelLib::ErrorType::AssetImageInvalid << "AssetImage's name missmatch (assetImageName=\"" + assetImageName + "\", assetImage->name=\"" + assetImage->name + "\")";
			return;
		}
	}
	else assetImage = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName);

	if (!assetImage)
	{
		qCritical() << NovelLib::ErrorType::AssetImageMissing << "Sprite AssetImage \"" + assetImageName + "\" does not exist";
		return;
	}
	assetImageName_ = assetImageName;
	assetImage_     = assetImage;
	errorCheck(true);
}

QString Sentence::getCharacterName() const noexcept
{
	return characterName_;
}

const Character* Sentence::getCharacter() const noexcept
{
	return character_;
}

Character* Sentence::getCharacter() noexcept
{
	return character_;
}

void Sentence::setCharacter(const QString& characterName, Character* character) noexcept
{
	if (character)
	{
		if (character->name != characterName)
		{
			qCritical() << NovelLib::ErrorType::CharacterInvalid << "Character's name missmatch (characterName=\"" + characterName + "\", character->name=\"" + character->name + "\")";
			return;
		}
	}

	if (parentEvent->parentScene->scenery.getDisplayedCharacter(characterName_) == nullptr)
		qCritical() << NovelLib::ErrorType::CharacterMissing << "Character \"" + characterName + "\" does not exist";
	characterName_ = characterName_;
	errorCheck(true);
}

QString Sentence::getVoiceName() const noexcept
{
	return voiceName_;
}

const Voice* Sentence::getVoice() const noexcept
{
	return voice_; 
}

Voice* Sentence::getVoice() noexcept
{
	return voice_;
}

void Sentence::setVoice(const QString& voiceName, Voice* voice) noexcept
{
	if (voice)
	{
		if (voice->name != voiceName)
		{
			qCritical() << NovelLib::ErrorType::VoiceInvalid << "Voice's name missmatch (voiceName=\"" + voiceName + "\", voice->name=\"" + voice->name + "\")";
			return;
		}
	}
	else voice = Novel::getInstance().getVoice(voiceName);

	if (!voice)
	{
		qCritical() << NovelLib::ErrorType::VoiceMissing << "Voice \"" + voiceName + "\" does not exist";
		return;
	}
	voiceName_ = voiceName;
	voice_     = voice;
	errorCheck(true);
}