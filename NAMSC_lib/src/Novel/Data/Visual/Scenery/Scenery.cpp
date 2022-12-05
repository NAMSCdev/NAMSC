#include "Novel/Data/Visual/Scenery/Scenery.h"

#include "Novel/Data/Asset/AssetManager.h"
#include "Novel/Data/Novel.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectColor.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectFade.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectMove.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectRotate.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectScale.h"
#include <Helpers.h>

Scenery::Scenery(const QString& backgroundAssetImageName, const MusicPlaylist& musicPlaylist, const QHash<QString, Character>& displayedCharacters, const QHash<QString, SceneryObject>& displayedSceneryObjects, const QHash<QString, Sound>& sounds)
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

	std::swap(*this, obj);
	
	return *this; 
}

bool Scenery::checkForErrors(bool bComprehensive) const
{
	bool bError = false;

	bError |= musicPlaylist.checkForErrors(bComprehensive);

	for (const Character& character : displayedCharacters_)
		bError |= character.checkForErrors(bComprehensive);

	for (const SceneryObject& sceneryObject : displayedSceneryObjects_)
		bError |= sceneryObject.checkForErrors(bComprehensive);
	
	for (const Sound& sound : sounds_)
		bError |= sound.checkForErrors(bComprehensive);
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
	for (Character& character : displayedCharacters_)
		character.run();

	for (SceneryObject& sceneryObject : displayedSceneryObjects_)
		sceneryObject.run();
}

/// \todo Manage Sounds

void Scenery::update(uint elapsedTime)
{
	for (Character& character : displayedCharacters_)
		character.update(elapsedTime);

	for (SceneryObject& sceneryObject : displayedSceneryObjects_)
		sceneryObject.update(elapsedTime);
}

void Scenery::ensureResourcesAreLoaded()
{
	for (Character& character : displayedCharacters_)
		character.ensureResourcesAreLoaded();

	for (SceneryObject& sceneryObject : displayedSceneryObjects_)
		sceneryObject.ensureResourcesAreLoaded();

	//todo: add QSoundEffect from Widget
	for (Sound& sound : sounds_)
		if (!sound.isLoaded())
			sound.load();
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
		qCritical() << this << NovelLib::ErrorType::AssetImageMissing << "AssetImage \"" << assetImageName << "\" does not exist";
	else
	{
		backgroundAssetImageName_ = assetImageName;
		backgroundAssetImage_     = newAssetImage;
		checkForErrors(true);
	}
}

const QHash<QString, Character>* Scenery::getDisplayedCharacters() const noexcept
{
	return &displayedCharacters_;
}

void Scenery::setDisplayedCharacters(const QHash<QString, Character>& characters) noexcept
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

void Scenery::setDisplayedCharacter(const QString& characterName, const Character& character) noexcept
{
	displayedCharacters_[characterName] = character;
}

bool Scenery::removeDisplayedCharacter(const QString& characterName) noexcept
{
	return NovelLib::removeFromNamedMap(displayedCharacters_, characterName, "Character");
}

const QHash<QString, SceneryObject>* Scenery::getDisplayedSceneryObjects() const noexcept
{
	return &displayedSceneryObjects_;
}

void Scenery::setDisplayedSceneryObjects(const QHash<QString, SceneryObject>& sceneryObjects) noexcept
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

void Scenery::setDisplayedSceneryObject(const QString& sceneryObjectName, const SceneryObject& sceneryObject) noexcept
{
	displayedSceneryObjects_[sceneryObjectName] = sceneryObject;
}

bool Scenery::removeDisplayedSceneryObject(const QString& sceneryObjectName) noexcept
{
	return NovelLib::removeFromNamedMap(displayedSceneryObjects_, sceneryObjectName, "SceneryObject");
}

const QHash<QString, Sound>* Scenery::getSounds() const noexcept
{
	return &sounds_;
}

void Scenery::setSounds(const QHash<QString, Sound>& sounds) noexcept
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
	for (const Character& character : displayedCharacters_)
		dataStream << character;
	for (const SceneryObject& sceneryObject : displayedSceneryObjects_)
		dataStream << sceneryObject;
	for (const Sound& sound : sounds_)
		dataStream << sound;
}