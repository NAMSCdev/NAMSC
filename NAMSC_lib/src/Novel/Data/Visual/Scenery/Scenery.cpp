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

Scenery::Scenery(const QString& backgroundAssetImageName, const MusicPlaylist& musicPlaylist, const std::unordered_map<QString, Character>& displayedCharacters, const std::unordered_map<QString, SceneryObject>& displayedSceneryObjects, const std::unordered_map<QString, Sound>& sounds, AssetImage* backgroundAssetImage)
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
		//TODO: check safety
		QString& name = character.name;
		displayedCharacters_[name] = std::move(character);
	}

	for (size_t i = 0; i != displayedSceneryObjectsSize; ++i)
	{
		SceneryObject sceneryObject;
		dataStream >> sceneryObject;
		QString& name = sceneryObject.name;
		displayedSceneryObjects_[name] = std::move(sceneryObject);
	}

	for (size_t i = 0; i != soundsSize; ++i)
	{
		Sound sound;
		dataStream >> sound;
		QString& name = sound.name;
		sounds_[name] = std::move(sound);
	}

	errorCheck();
}

void Scenery::serializableSave(QDataStream& dataStream) const
{
	dataStream << backgroundAssetImageName_ << musicPlaylist;
	dataStream << displayedCharacters_.size() << displayedSceneryObjects_.size() << sounds_.size();
	for (const std::pair<const QString, Character>& character : displayedCharacters_)
		dataStream << character.second;
	for (const std::pair<const QString, SceneryObject>& sceneryObject : displayedSceneryObjects_)
		dataStream << sceneryObject.second;
	for (const std::pair <const QString, Sound>& sound : sounds_)
		dataStream << sound.second;
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
	for (std::pair<const QString, Character>& character : displayedCharacters_)
		character.second.resetAnimators();

	for (std::pair<const QString, SceneryObject>& sceneryObject : displayedSceneryObjects_)
		sceneryObject.second.resetAnimators();
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

const std::unordered_map<QString, Character>* Scenery::getDisplayedCharacters() const noexcept
{
	return &displayedCharacters_;
}

const Character* Scenery::getDisplayedCharacter(const QString& characterName) const
{
	return NovelLib::getFromNamedMap(displayedCharacters_, characterName, "Character", NovelLib::ErrorType::CharacterMissing);
}

Character* Scenery::getDisplayedCharacter(const QString& characterName)
{
	return NovelLib::getFromNamedMap(displayedCharacters_, characterName, "Character", NovelLib::ErrorType::CharacterMissing);
}

void Scenery::setDisplayedCharacters(const std::unordered_map<QString, Character>& characters) noexcept
{
	displayedCharacters_ = characters;
}

Character* Scenery::setDisplayedCharacter(const QString& characterName, const Character& character)
{
	return NovelLib::setInNamedMap(displayedCharacters_, characterName, character, "Character", NovelLib::ErrorType::CharacterInvalid);
}

Character* Scenery::renameDisplayedCharacter(const QString& oldName, const QString& newName)
{
	return NovelLib::renameInNamedMap(displayedCharacters_, oldName, newName, "Character", NovelLib::ErrorType::CharacterMissing, NovelLib::ErrorType::CharacterInvalid);
}

bool Scenery::removeDisplayedCharacter(const QString& characterName)
{
	return NovelLib::removeFromNamedMap(displayedCharacters_, characterName, "Character", NovelLib::ErrorType::CharacterMissing);
}

void Scenery::clearDisplayedCharacters() noexcept
{
	displayedCharacters_.clear();
}

const std::unordered_map<QString, SceneryObject>* Scenery::getDisplayedSceneryObjects() const noexcept
{
	return &displayedSceneryObjects_;
}

const SceneryObject* Scenery::getDisplayedSceneryObject(const QString& sceneryObjectName) const
{
	return NovelLib::getFromNamedMap(displayedSceneryObjects_, sceneryObjectName, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing);
}

SceneryObject* Scenery::getDisplayedSceneryObject(const QString& sceneryObjectName)
{
	return NovelLib::getFromNamedMap(displayedSceneryObjects_, sceneryObjectName, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing);
}

void Scenery::setDisplayedSceneryObjects(const std::unordered_map<QString, SceneryObject>& sceneryObjects) noexcept
{
	displayedSceneryObjects_ = sceneryObjects;
}

SceneryObject* Scenery::setDisplayedSceneryObject(const QString& sceneryObjectName, const SceneryObject& sceneryObject)
{
	return NovelLib::setInNamedMap(displayedSceneryObjects_, sceneryObjectName, sceneryObject, "SceneryObject", NovelLib::ErrorType::SceneryObjectInvalid);
}

SceneryObject* Scenery::renameDisplayedSceneryObject(const QString& oldName, const QString& newName)
{
	return NovelLib::renameInNamedMap(displayedSceneryObjects_, oldName, newName, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing, NovelLib::ErrorType::SceneryObjectInvalid);

}

bool Scenery::removeDisplayedSceneryObject(const QString& sceneryObjectName)
{
	return NovelLib::removeFromNamedMap(displayedSceneryObjects_, sceneryObjectName, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing);
}

void Scenery::clearDisplayedSceneryObject() noexcept
{
	displayedSceneryObjects_.clear();
}

const std::unordered_map<QString, Sound>* Scenery::getSounds() const noexcept
{
	return &sounds_;
}

const Sound* Scenery::getSound(const QString& soundName) const
{
	//TODO: Sound errors
	return NovelLib::getFromNamedMap(sounds_, soundName, "Sound");
}

Sound* Scenery::getSound(const QString& soundName)
{
	//TODO: Sound errors
	return NovelLib::getFromNamedMap(sounds_, soundName, "Sound");
}

void Scenery::setSounds(const std::unordered_map<QString, Sound>& sounds) noexcept
{
	sounds_ = sounds;
}

Sound* Scenery::setSound(const QString& soundName, const Sound& sound)
{
	//TODO: Sound errors
	return NovelLib::setInNamedMap(sounds_, soundName, sound, "Sound");
}

Sound* Scenery::renameSound(const QString& oldName, const QString& newName)
{
	//TODO: Sound errors
	return NovelLib::renameInNamedMap(sounds_, oldName, newName, "Sound");
}

bool Scenery::removeSound(const QString& soundName)
{
	//TODO: Sound errors
	return NovelLib::getFromNamedMap(sounds_, soundName, "Sound");
}

void Scenery::clearSounds() noexcept
{
	sounds_.clear();
}