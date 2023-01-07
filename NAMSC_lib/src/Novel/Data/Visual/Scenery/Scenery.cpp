#include "Novel/Data/Visual/Scenery/Scenery.h"

#include "Novel/Data/Asset/AssetManager.h"
#include "Novel/Data/Novel.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectColor.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectFade.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectMove.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectRotate.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectScale.h"
#include <Helpers.h>

Scenery::Scenery(const QString& backgroundAssetImageName, const MusicPlaylist& musicPlaylist, const std::unordered_map<QString, Character>& displayedCharacters, const std::unordered_map<QString, SceneryObject>& displayedSceneryObjects, const std::unordered_map<QString, Sound>& sounds)
	: backgroundAssetImageName_(backgroundAssetImageName),
	  musicPlaylist(musicPlaylist), 
	  displayedCharacters_(displayedCharacters), 
	  displayedSceneryObjects_(displayedSceneryObjects), 
	  sounds_(sounds)
{
	backgroundAssetImage_ = AssetManager::getInstance().getAssetImageSceneryBackground(backgroundAssetImageName_);
	checkForErrors(true);
}

Scenery& Scenery::operator=(Scenery obj) noexcept
{
	if (this == &obj) return *this;

	std::swap(this->backgroundAssetImageName_, obj.backgroundAssetImageName_);
	std::swap(this->musicPlaylist,             obj.musicPlaylist);
	std::swap(this->displayedCharacters_,      obj.displayedCharacters_);
	std::swap(this->displayedSceneryObjects_,  obj.displayedSceneryObjects_);
	std::swap(this->sounds_,                   obj.sounds_);

	return *this; 
}

bool Scenery::checkForErrors(bool bComprehensive) const
{
	bool bError = false;

	bError |= musicPlaylist.checkForErrors(bComprehensive);

	for (const std::pair<const QString, Character>& character : displayedCharacters_)
		bError |= character.second.checkForErrors(bComprehensive);

	for (const std::pair<const QString, SceneryObject>& sceneryObject : displayedSceneryObjects_)
		bError |= sceneryObject.second.checkForErrors(bComprehensive);
	
	for (const std::pair<const QString, Sound>& sound : sounds_)
		bError |= sound.second.checkForErrors(bComprehensive);
	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in Scenery::checkForErrors";

	return bError;
}

void Scenery::run()
{
	for (std::pair<const QString, Character>& character : displayedCharacters_)
		character.second.run();

	for (std::pair<const QString, SceneryObject>& sceneryObject : displayedSceneryObjects_)
		sceneryObject.second.run();
}

/// \todo Manage Sounds

void Scenery::update(uint elapsedTime)
{
	for (std::pair<const QString, Character>& character : displayedCharacters_)
		character.second.update(elapsedTime);

	for (std::pair<const QString, SceneryObject>& sceneryObject : displayedSceneryObjects_)
		sceneryObject.second.update(elapsedTime);
}

void Scenery::ensureResourcesAreLoaded()
{
	for (std::pair<const QString, Character>& character : displayedCharacters_)
		character.second.ensureResourcesAreLoaded();

	for (std::pair<const QString, SceneryObject>& sceneryObject : displayedSceneryObjects_)
		sceneryObject.second.ensureResourcesAreLoaded();

	//todo: add QSoundEffect from Widget
	for (std::pair<const QString, Sound>& sound : sounds_)
		if (!sound.second.isLoaded())
			sound.second.load();
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
	for (std::pair<const QString, Character>& character : displayedCharacters_)
		character.second.resetAnimators();

	for (std::pair<const QString, SceneryObject>& sceneryObject : displayedSceneryObjects_)
		sceneryObject.second.resetAnimators();
}

const AssetImage* Scenery::getBackgroundAssetImage() const noexcept
{
	return backgroundAssetImage_;
}

AssetImage* Scenery::getBackgroundAssetImage() noexcept
{
	return backgroundAssetImage_;
}

QString Scenery::getBackgroundAssetImageName() const noexcept
{
	return backgroundAssetImageName_;
}

void Scenery::setBackgroundAssetImage(const QString& assetImageName, AssetImage* assetImage) noexcept
{
	if (assetImage != nullptr)
	{
		backgroundAssetImageName_ = assetImageName;
		backgroundAssetImage_     = assetImage;
		checkForErrors(true);
		return;
	}

	AssetImage* newAssetImage = nullptr;
	newAssetImage = AssetManager::getInstance().getAssetImageSceneryBackground(assetImageName);
	if (newAssetImage == nullptr)
		qCritical() << NovelLib::ErrorType::AssetImageMissing << "AssetImage \"" + assetImageName + "\" does not exist";
	else
	{
		backgroundAssetImageName_ = assetImageName;
		backgroundAssetImage_     = newAssetImage;
		checkForErrors(true);
	}
}

const std::unordered_map<QString, Character>* Scenery::getDisplayedCharacters() const noexcept
{
	return &displayedCharacters_;
}

void Scenery::setDisplayedCharacters(const std::unordered_map<QString, Character>& characters) noexcept
{
	displayedCharacters_ = characters;
}

const Character* Scenery::getDisplayedCharacter(const QString& characterName) const noexcept
{
	return NovelLib::getFromNamedMap(displayedCharacters_, characterName, "Character");
}

Character* Scenery::getDisplayedCharacter(const QString& characterName) noexcept
{
	return NovelLib::getFromNamedMap(displayedCharacters_, characterName, "Character");
}

Character* Scenery::setDisplayedCharacter(const QString& characterName, const Character& character) noexcept
{
	return &(displayedCharacters_[characterName] = character);
}

bool Scenery::removeDisplayedCharacter(const QString& characterName) noexcept
{
	return NovelLib::removeFromNamedMap(displayedCharacters_, characterName, "Character");
}

const std::unordered_map<QString, SceneryObject>* Scenery::getDisplayedSceneryObjects() const noexcept
{
	return &displayedSceneryObjects_;
}

void Scenery::setDisplayedSceneryObjects(const std::unordered_map<QString, SceneryObject>& sceneryObjects) noexcept
{
	displayedSceneryObjects_ = sceneryObjects;
}

const SceneryObject* Scenery::getDisplayedSceneryObject(const QString& sceneryObjectName) const noexcept
{
	return NovelLib::getFromNamedMap(displayedSceneryObjects_, sceneryObjectName, "SceneryObject");
}

SceneryObject* Scenery::getDisplayedSceneryObject(const QString& sceneryObjectName) noexcept
{
	return NovelLib::getFromNamedMap(displayedSceneryObjects_, sceneryObjectName, "SceneryObject");
}

SceneryObject* Scenery::setDisplayedSceneryObject(const QString& sceneryObjectName, const SceneryObject& sceneryObject) noexcept
{
	return &(displayedSceneryObjects_[sceneryObjectName] = sceneryObject);
}

bool Scenery::removeDisplayedSceneryObject(const QString& sceneryObjectName) noexcept
{
	return NovelLib::removeFromNamedMap(displayedSceneryObjects_, sceneryObjectName, "SceneryObject");
}

const std::unordered_map<QString, Sound>* Scenery::getSounds() const noexcept
{
	return &sounds_;
}

void Scenery::setSounds(const std::unordered_map<QString, Sound>& sounds) noexcept
{
	sounds_ = sounds;
}

const Sound* Scenery::getSound(const QString& soundName) const noexcept
{
	return NovelLib::getFromNamedMap(sounds_, soundName, "Sound");
}

Sound* Scenery::getSound(const QString& soundName) noexcept
{
	return NovelLib::getFromNamedMap(sounds_, soundName, "Sound");
}

void Scenery::setSound(const QString& soundName, const Sound& sound) noexcept
{
	sounds_[soundName] = sound;
}

bool Scenery::removeSound(const QString& soundName) noexcept
{
	return NovelLib::getFromNamedMap(sounds_, soundName, "Sound");
}

void Scenery::serializableLoad(QDataStream& dataStream)
{
	dataStream >> backgroundAssetImageName_ >> musicPlaylist;
	uint displayedCharactersSize, displayedSceneryObjectsSize, soundsSize;
	dataStream >> displayedCharactersSize >> displayedSceneryObjectsSize >> soundsSize;
	for (uint i = 0; i != displayedCharactersSize; ++i)
	{
		Character character;
		dataStream >> character;
		displayedCharacters_[character.name] = std::move(character);
	}

	for (uint i = 0; i != displayedSceneryObjectsSize; ++i)
	{
		SceneryObject sceneryObject;
		dataStream >> sceneryObject;
		displayedSceneryObjects_[sceneryObject.name] = std::move(sceneryObject);
	}

	for (uint i = 0; i != soundsSize; ++i)
	{
		Sound sound;
		dataStream >> sound;
		sounds_[sound.name] = std::move(sound);
	}

	checkForErrors();
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