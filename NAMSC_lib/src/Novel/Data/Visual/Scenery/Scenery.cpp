#include "Novel/Data/Visual/Scenery/Scenery.h"

#include "Novel/Data/Asset/AssetManager.h"
#include "Novel/Data/Novel.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectColor.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectFade.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectMove.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectRotate.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectScale.h"
#include "Helpers.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(Scenery& first, Scenery& second) noexcept
{
	using std::swap;
	swap(first.backgroundAssetImageName_, second.backgroundAssetImageName_);
	swap(first.musicPlaylist,             second.musicPlaylist);
	swap(first.displayedCharacters_,      second.displayedCharacters_);
	swap(first.displayedSceneryObjects_,  second.displayedSceneryObjects_);
	swap(first.sounds_,                   second.sounds_);
	swap(first.backgroundAssetImage_,     second.backgroundAssetImage_);
}

Scenery::Scenery(const QString& backgroundAssetImageName, const MusicPlaylist& musicPlaylist, const std::vector<Character>& displayedCharacters, const std::vector<SceneryObject>& displayedSceneryObjects, const std::vector<Sound>& sounds, AssetImage* backgroundAssetImage)
	: backgroundAssetImageName_(backgroundAssetImageName),
	musicPlaylist(musicPlaylist), 
	displayedCharacters_(displayedCharacters), 
	displayedSceneryObjects_(displayedSceneryObjects), 
	sounds_(sounds),
	backgroundAssetImage_(backgroundAssetImage)
{
	if (!backgroundAssetImage_)
		backgroundAssetImage_ = AssetManager::getInstance().getAssetImageSceneryBackground(backgroundAssetImageName_);
	errorCheck(true);
}

//defaulted
//Scenery::Scenery(const Scenery& obj) noexcept
//	: backgroundAssetImageName_(obj.backgroundAssetImageName_),
//	musicPlaylist(obj.musicPlaylist),
//	displayedCharacters_(obj.displayedCharacters_),
//	displayedSceneryObjects_(obj.displayedSceneryObjects_),
//	sounds_(obj.sounds_),
//	backgroundAssetImage_(obj.backgroundAssetImage_)
//{
//}

//defaulted
//Scenery& Scenery::operator=(const Scenery& obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	backgroundAssetImageName_ = obj.backgroundAssetImageName_;
//	backgroundAssetImage_     = obj.backgroundAssetImage_;
//	musicPlaylist             = obj.musicPlaylist;
//	displayedCharacters_      = obj.displayedCharacters_;
//	displayedSceneryObjects_  = obj.displayedSceneryObjects_;
//	sounds_                   = obj.sounds_;
//
//	return *this; 
//}

bool Scenery::operator==(const Scenery& obj) const noexcept
{
	if (this == &obj)
		return true;

	return backgroundAssetImageName_ == obj.backgroundAssetImageName_ &&
		   musicPlaylist             == obj.musicPlaylist             &&
		   displayedCharacters_      == obj.displayedCharacters_      &&
		   displayedSceneryObjects_  == obj.displayedSceneryObjects_  &&
		   sounds_                   == obj.sounds_;
}

void Scenery::serializableLoad(QDataStream& dataStream)
{
	dataStream >> backgroundAssetImageName_ >> musicPlaylist;
	size_t displayedCharactersSize, displayedSceneryObjectsSize, soundsSize;
	dataStream >> displayedCharactersSize >> displayedSceneryObjectsSize >> soundsSize;
	for (size_t i = 0; i != displayedCharactersSize; ++i)
	{
		Character character;
		dataStream >> character;
		addDisplayedCharacter(std::move(character));
	}

	for (size_t i = 0; i != displayedSceneryObjectsSize; ++i)
	{
		SceneryObject sceneryObject;
		dataStream >> sceneryObject;
		addDisplayedSceneryObject(std::move(sceneryObject));
	}

	for (size_t i = 0; i != soundsSize; ++i)
	{
		Sound sound;
		dataStream >> sound;
		addSound(std::move(sound));
	}

	errorCheck();
}

void Scenery::serializableSave(QDataStream& dataStream) const
{
	dataStream << backgroundAssetImageName_ << musicPlaylist;
	dataStream << displayedCharacters_.size() << displayedSceneryObjects_.size() << sounds_.size();
	for (const Character& character : displayedCharacters_)
		dataStream << character;
	for (const SceneryObject& sceneryObject : displayedSceneryObjects_)
		dataStream << sceneryObject;
	for (const Sound& sound : sounds_)
		dataStream << sound;
}

//  MEMBER_FIELD_SECTION_CHANGE END

//defaulted
//Scenery::Scenery(Scenery&& obj) noexcept
//	: Scenery()
//{
//	swap(*this, obj);
//}

void Scenery::addAnimator(AnimatorSceneryObjectColor&& animatorColor)
{
	animatorColor.parentSceneryObject_->addAnimator(std::move(animatorColor));
}

void Scenery::addAnimator(AnimatorSceneryObjectFade&& animatorFade)
{
	animatorFade.parentSceneryObject_->addAnimator(std::move(animatorFade));
}

void Scenery::addAnimator(AnimatorSceneryObjectMove&& animatorMove)
{
	animatorMove.parentSceneryObject_->addAnimator(std::move(animatorMove));
}

void Scenery::addAnimator(AnimatorSceneryObjectRotate&& animatorRotate)
{
	animatorRotate.parentSceneryObject_->addAnimator(std::move(animatorRotate));
}

void Scenery::addAnimator(AnimatorSceneryObjectScale&& animatorScale)
{
	animatorScale.parentSceneryObject_->addAnimator(std::move(animatorScale));
}

void Scenery::resetAnimators() noexcept
{
	for (Character& character : displayedCharacters_)
		character.resetAnimators();

	for (SceneryObject& sceneryObject : displayedSceneryObjects_)
		sceneryObject.resetAnimators();
}

QString Scenery::getBackgroundAssetImageName() const noexcept
{
	return backgroundAssetImageName_;
}

const AssetImage* Scenery::getBackgroundAssetImage() const noexcept
{
	return backgroundAssetImage_;
}

AssetImage* Scenery::getBackgroundAssetImage() noexcept
{
	return backgroundAssetImage_;
}

void Scenery::setBackgroundAssetImage(const QString& backgroundAssetImageName, AssetImage* backgroundAssetImage) noexcept
{
	if (backgroundAssetImage)
	{
		if (backgroundAssetImage->name != backgroundAssetImageName)
		{
			qCritical() << NovelLib::ErrorType::AssetImageInvalid << "AssetImage's name missmatch (backgroundAssetImageName=\"" + backgroundAssetImageName + "\", backgroundAssetImage->name=\"" + backgroundAssetImage->name + "\")";
			return;
		}
	}
	else backgroundAssetImage = AssetManager::getInstance().getAssetImageSceneryBackground(backgroundAssetImageName);

	if (!backgroundAssetImage)
	{
		qCritical() << NovelLib::ErrorType::AssetImageMissing << "Background AssetImage \"" + backgroundAssetImageName + "\" does not exist";
		return;
	}
	backgroundAssetImageName_ = backgroundAssetImageName;
	backgroundAssetImage_     = backgroundAssetImage;
	errorCheck(true);
}

const std::vector<Character>* Scenery::getDisplayedCharacters() const noexcept
{
	return &displayedCharacters_;
}

const Character* Scenery::getDisplayedCharacter(const QString& characterName) const
{
	return NovelLib::listGet(displayedCharacters_, characterName, "Character", NovelLib::ErrorType::CharacterMissing);
}

Character* Scenery::getDisplayedCharacter(const QString& characterName)
{
	return NovelLib::listGet(displayedCharacters_, characterName, "Character", NovelLib::ErrorType::CharacterMissing);
}

void Scenery::setDisplayedCharacters(const std::vector<Character>& characters) noexcept
{
	displayedCharacters_ = characters;
}

Character* Scenery::insertDisplayedCharacter(uint index, const Character& character)
{
	return NovelLib::listInsert(displayedCharacters_, index, character, "Character", NovelLib::ErrorType::CharacterInvalid);
}

Character* Scenery::addDisplayedCharacter(const Character& character)
{
	return NovelLib::listAdd(displayedCharacters_, character, "Character", NovelLib::ErrorType::CharacterInvalid);
}

Character* Scenery::addDisplayedCharacter(Character&& character)
{
	return NovelLib::listAdd(displayedCharacters_, std::move(character), "Character", NovelLib::ErrorType::CharacterInvalid);
}

bool Scenery::removeDisplayedCharacter(const QString& characterName)
{
	return NovelLib::listRemove(displayedCharacters_, characterName, "Character", NovelLib::ErrorType::CharacterMissing);
}

void Scenery::clearDisplayedCharacters() noexcept
{
	displayedCharacters_.clear();
}

const std::vector<SceneryObject>* Scenery::getDisplayedSceneryObjects() const noexcept
{
	return &displayedSceneryObjects_;
}

const SceneryObject* Scenery::getDisplayedSceneryObject(const QString& sceneryObjectName) const
{
	return NovelLib::listGet(displayedSceneryObjects_, sceneryObjectName, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing);
}

SceneryObject* Scenery::getDisplayedSceneryObject(const QString& sceneryObjectName)
{
	return NovelLib::listGet(displayedSceneryObjects_, sceneryObjectName, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing);
}

void Scenery::setDisplayedSceneryObjects(const std::vector<SceneryObject>& sceneryObjects) noexcept
{
	displayedSceneryObjects_ = sceneryObjects;
}

SceneryObject* Scenery::insertDisplayedSceneryObject(uint index, const SceneryObject& sceneryObject)
{
	return NovelLib::listInsert(displayedSceneryObjects_, index, sceneryObject, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing);
}

SceneryObject* Scenery::addDisplayedSceneryObject(const SceneryObject& sceneryObject)
{
	return NovelLib::listAdd(displayedSceneryObjects_, sceneryObject, "SceneryObject", NovelLib::ErrorType::SceneryObjectInvalid);
}

SceneryObject* Scenery::addDisplayedSceneryObject(SceneryObject&& sceneryObject)
{
	return NovelLib::listAdd(displayedSceneryObjects_, sceneryObject, "SceneryObject", NovelLib::ErrorType::SceneryObjectInvalid);
}

bool Scenery::removeDisplayedSceneryObject(const QString& sceneryObjectName)
{
	return NovelLib::listRemove(displayedSceneryObjects_, sceneryObjectName, "SceneryObject", NovelLib::ErrorType::SceneryObjectInvalid);
}

void Scenery::clearDisplayedSceneryObject() noexcept
{
	displayedSceneryObjects_.clear();
}

const std::vector<Sound>* Scenery::getSounds() const noexcept
{
	return &sounds_;
}

const Sound* Scenery::getSound(const QString& soundName) const
{
	//TODO: Sound errors
	return NovelLib::listGet(sounds_, soundName, "Sound");
}

Sound* Scenery::getSound(const QString& soundName)
{
	//TODO: Sound errors
	return NovelLib::listGet(sounds_, soundName, "Sound");
}

void Scenery::setSounds(const std::vector<Sound>& sounds) noexcept
{
	sounds_ = sounds;
}

Sound* Scenery::insertSound(uint index, const Sound& sound)
{
	//TODO: Sound errors
	return NovelLib::listInsert(sounds_, index, sound, "Sound");
}

Sound* Scenery::addSound(const Sound& sound)
{
	//TODO: Sound errors
	return NovelLib::listAdd(sounds_, sound, "Sound");
}

Sound* Scenery::addSound(Sound&& sound)
{
	//return nullptr;
	//TODO: Sound errors
	return NovelLib::listAdd(sounds_, std::move(sound), "Sound");
}

bool Scenery::removeSound(const QString& soundName)
{
	//return true;
	//TODO: Sound errors
	return NovelLib::listRemove(sounds_, soundName, "Sound");
}

void Scenery::clearSounds() noexcept
{
	sounds_.clear();
}