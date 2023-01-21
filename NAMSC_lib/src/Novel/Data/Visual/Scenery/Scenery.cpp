#include "Novel/Data/Visual/Scenery/Scenery.h"

#include "Novel/Data/Asset/AssetManager.h"
#include "Novel/Data/Novel.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectColor.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectFade.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectMove.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectRotate.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectScale.h"
#include "Helpers.h"

Scenery::Scenery(const Scene* const parentScene) noexcept
	: parentScene(parentScene)
{
}

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

Scenery::Scenery(const Scene* const parentScene, const QString& backgroundAssetImageName, const MusicPlaylist& musicPlaylist, const std::vector<Character>& displayedCharacters, const std::vector<SceneryObject>& displayedSceneryObjects, const std::vector<Sound>& sounds, AssetImage* backgroundAssetImage)
	: parentScene(parentScene),
	backgroundAssetImageName_(backgroundAssetImageName),
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

Scenery::Scenery(const Scenery& obj) noexcept
	: parentScene(obj.parentScene),
	backgroundAssetImageName_(obj.backgroundAssetImageName_),
	musicPlaylist(obj.musicPlaylist),
	displayedCharacters_(obj.displayedCharacters_),
	displayedSceneryObjects_(obj.displayedSceneryObjects_),
	sounds_(obj.sounds_),
	backgroundAssetImage_(obj.backgroundAssetImage_)
{
}

Scenery& Scenery::operator=(const Scenery& obj) noexcept
{
	if (this == &obj)
		return *this;

	backgroundAssetImageName_ = obj.backgroundAssetImageName_;
	musicPlaylist             = obj.musicPlaylist;
	displayedCharacters_      = obj.displayedCharacters_;
	displayedSceneryObjects_  = obj.displayedSceneryObjects_;
	sounds_                   = obj.sounds_;
	backgroundAssetImage_     = obj.backgroundAssetImage_;

	return *this;
}

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

Scenery::Scenery(Scenery&& obj) noexcept
	: Scenery(obj.parentScene)
{
	swap(*this, obj);
}

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

const Character* Scenery::getDisplayedCharacter(uint index) const
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(displayedCharacters_, index, "Character", NovelLib::ErrorType::CharacterMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

Character* Scenery::getDisplayedCharacter(uint index)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(displayedCharacters_, index, "Character", NovelLib::ErrorType::CharacterMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

const Character* Scenery::getDisplayedCharacter(const QString& characterName) const
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(displayedCharacters_, characterName, "Character", NovelLib::ErrorType::CharacterMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

Character* Scenery::getDisplayedCharacter(const QString& characterName)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(displayedCharacters_, characterName, "Character", NovelLib::ErrorType::CharacterMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

const std::vector<Character>* Scenery::setDisplayedCharacters(const std::vector<Character>& characters) noexcept
{
	return &(displayedCharacters_ = characters);
}

const std::vector<Character>* Scenery::setDisplayedCharacters(std::vector<Character>&& characters) noexcept
{
	return &(displayedCharacters_ = std::move(characters));
}

Character* Scenery::insertDisplayedCharacter(uint index, const Character& character)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listInsert(displayedCharacters_, index, character, "Character", NovelLib::ErrorType::CharacterInvalid, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

Character* Scenery::insertDisplayedCharacter(uint index, Character&& character)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listInsert(displayedCharacters_, index, std::move(character), "Character", NovelLib::ErrorType::CharacterInvalid, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

Character* Scenery::reinsertDisplayedCharacter(uint index, uint newIndex)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listReinsert(displayedCharacters_, index, newIndex, "Character", NovelLib::ErrorType::CharacterMissing, NovelLib::ErrorType::CharacterInvalid, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

Character* Scenery::addDisplayedCharacter(const Character& character)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listAdd(displayedCharacters_, character, "Character", NovelLib::ErrorType::CharacterInvalid, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

Character* Scenery::addDisplayedCharacter(Character&& character)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listAdd(displayedCharacters_, std::move(character), "Character", NovelLib::ErrorType::CharacterInvalid, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

bool Scenery::removeDisplayedCharacter(const QString& characterName)
{
	return NovelLib::Helpers::listRemove(displayedCharacters_, characterName, "Character", NovelLib::ErrorType::CharacterMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : ""));
}

bool Scenery::removeDisplayedCharacter(uint index)
{
	return NovelLib::Helpers::listRemove(displayedCharacters_, index, "Character", NovelLib::ErrorType::CharacterMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : ""));
}

void Scenery::clearDisplayedCharacters() noexcept
{
	displayedCharacters_.clear();
}

const std::vector<SceneryObject>* Scenery::getDisplayedSceneryObjects() const noexcept
{
	return &displayedSceneryObjects_;
}

const SceneryObject* Scenery::getDisplayedSceneryObject(uint index) const
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(displayedSceneryObjects_, index, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

SceneryObject* Scenery::getDisplayedSceneryObject(uint index)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(displayedSceneryObjects_, index, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

const SceneryObject* Scenery::getDisplayedSceneryObject(const QString& sceneryObjectName) const
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(displayedSceneryObjects_, sceneryObjectName, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

SceneryObject* Scenery::getDisplayedSceneryObject(const QString& sceneryObjectName)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(displayedSceneryObjects_, sceneryObjectName, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

const std::vector<SceneryObject>* Scenery::setDisplayedSceneryObjects(const std::vector<SceneryObject>& sceneryObjects) noexcept
{
	return &(displayedSceneryObjects_ = sceneryObjects);
}

const std::vector<SceneryObject>* Scenery::setDisplayedSceneryObjects(std::vector<SceneryObject>&& sceneryObjects) noexcept
{
	return &(displayedSceneryObjects_ = std::move(sceneryObjects));
}

SceneryObject* Scenery::insertDisplayedSceneryObject(uint index, const SceneryObject& sceneryObject)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listInsert(displayedSceneryObjects_, index, sceneryObject, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

SceneryObject* Scenery::insertDisplayedSceneryObject(uint index, SceneryObject&& sceneryObject)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listInsert(displayedSceneryObjects_, index, std::move(sceneryObject), "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

SceneryObject* Scenery::reinsertDisplayedSceneryObject(uint index, uint newIndex)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listReinsert(displayedSceneryObjects_, index, newIndex, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing, NovelLib::ErrorType::SceneryObjectInvalid, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

SceneryObject* Scenery::addDisplayedSceneryObject(const SceneryObject& sceneryObject)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listAdd(displayedSceneryObjects_, sceneryObject, "SceneryObject", NovelLib::ErrorType::SceneryObjectInvalid, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

SceneryObject* Scenery::addDisplayedSceneryObject(SceneryObject&& sceneryObject)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listAdd(displayedSceneryObjects_, sceneryObject, "SceneryObject", NovelLib::ErrorType::SceneryObjectInvalid, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

bool Scenery::removeDisplayedSceneryObject(const QString& sceneryObjectName)
{
	return NovelLib::Helpers::listRemove(displayedSceneryObjects_, sceneryObjectName, "SceneryObject", NovelLib::ErrorType::SceneryObjectInvalid, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : ""));
}

bool Scenery::removeDisplayedSceneryObject(uint index)
{
	return NovelLib::Helpers::listRemove(displayedSceneryObjects_, index, "SceneryObject", NovelLib::ErrorType::SceneryObjectInvalid, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : ""));
}

void Scenery::clearDisplayedSceneryObject() noexcept
{
	displayedSceneryObjects_.clear();
}

const std::vector<Sound>* Scenery::getSounds() const noexcept
{
	return &sounds_;
}

const Sound* Scenery::getSound(uint index) const
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(sounds_, index, "Sound", NovelLib::ErrorType::SoundMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

Sound* Scenery::getSound(uint index)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(sounds_, index, "Sound", NovelLib::ErrorType::SoundMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

const Sound* Scenery::getSound(const QString& soundName) const
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(sounds_, soundName, "Sound", NovelLib::ErrorType::SoundMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

Sound* Scenery::getSound(const QString& soundName)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(sounds_, soundName, "Sound", NovelLib::ErrorType::SoundMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

const std::vector<Sound>* Scenery::setSounds(const std::vector<Sound>& sounds) noexcept
{
	return &(sounds_ = sounds);
}

const std::vector<Sound>* Scenery::setSounds(std::vector<Sound>&& sounds) noexcept
{
	return &(sounds = std::move(sounds));
}

Sound* Scenery::addSound(const Sound& sound)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listAdd(sounds_, sound, "Sound", NovelLib::ErrorType::SoundInvalid, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

Sound* Scenery::addSound(Sound&& sound)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listAdd(sounds_, std::move(sound), "Sound", NovelLib::ErrorType::SoundInvalid, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : "")));
}

bool Scenery::removeSound(const QString& soundName)
{
	return NovelLib::Helpers::listRemove(sounds_, soundName, "Sound", NovelLib::ErrorType::SoundMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : ""));
}

bool Scenery::removeSound(uint index)
{
	return NovelLib::Helpers::listRemove(sounds_, index, "Sound", NovelLib::ErrorType::SoundMissing, (parentScene ? "Scene" : ""), (parentScene ? parentScene->name : ""));
}

void Scenery::clearSounds() noexcept
{
	sounds_.clear();
}