#pragma once

#include "Novel/Data/Audio/MusicPlaylist.h"
#include "Novel/Data/Audio/Sound.h"
#include "Novel/Data/Visual/Scenery/Character.h"

class SceneWidget;

/// All the media managed by the library
class Scenery final
{
	/// Swap trick
	friend void swap(Scenery& first, Scenery& second) noexcept;
public:
	Scenery()                                 noexcept = default;
	/// \param backgroundAssetImage Copies the AssetImage pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization
	explicit Scenery(const QString& backgroundAssetImageName, const MusicPlaylist& musicPlaylist = MusicPlaylist(), const std::vector<Character>& displayedCharacters = std::vector<Character>(), const std::vector<SceneryObject>& displayedSceneryObjects = std::vector<SceneryObject>(), const std::vector<Sound>& sounds = std::vector<Sound>(), AssetImage* backgroundAssetImage = nullptr);
	Scenery(const Scenery& obj)               noexcept = default;
	Scenery(Scenery&& obj)                    noexcept = default;
	///This one needs to be optimized at the cost of strong exception safety, as it is frequently assigned during gameplay (so the performance is a priority here)
	///No swap trick to avoid containers reallocation
	Scenery& operator=(const Scenery& obj)    noexcept = default;
	bool operator==(const Scenery& obj) const noexcept;
	bool operator!=(const Scenery& obj) const noexcept = default;

	/// \exception Error A Character in `defaultVoice_`/`assetImage_` is invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const;

	void run();

	/// \todo Manage Sounds
	void update(uint elapsedTime);

	void render(SceneWidget* sceneWidget);

	/// Ensures Assets and Sounds are loaded and if not - loads them
	void ensureResourcesAreLoaded();

	void addAnimator(AnimatorSceneryObjectColor&&  animatorColor);
	void addAnimator(AnimatorSceneryObjectFade&&   animatorFade);
	void addAnimator(AnimatorSceneryObjectMove&&   animatorMove);
	void addAnimator(AnimatorSceneryObjectRotate&& animatorRotate);
	void addAnimator(AnimatorSceneryObjectScale&&  animatorScale);

	/// \todo Add **Persistence To New Event** mechanism
	void resetAnimators() noexcept;

	QString getBackgroundAssetImageName()       const noexcept;
	const AssetImage* getBackgroundAssetImage() const noexcept;
	AssetImage*       getBackgroundAssetImage()       noexcept;
	void setBackgroundAssetImage(const QString& backgroundAssetImageName, AssetImage* backgroundAssetImage = nullptr) noexcept;

	const std::vector<Character>* getDisplayedCharacters() const noexcept;
	const Character* getDisplayedCharacter(const QString& characterName) const;
	Character*       getDisplayedCharacter(const QString& characterName);
	void setDisplayedCharacters(const std::vector<Character>& characters) noexcept;
	Character* insertDisplayedCharacter(uint index, const Character& character);
	Character* addDisplayedCharacter(const Character& character);
	Character* addDisplayedCharacter(Character&& character);
	bool removeDisplayedCharacter(const QString& characterName);
	void clearDisplayedCharacters() noexcept;

	const std::vector<SceneryObject>* getDisplayedSceneryObjects() const noexcept;
	const SceneryObject* getDisplayedSceneryObject(const QString& sceneryObjectName) const;
	SceneryObject*       getDisplayedSceneryObject(const QString& sceneryObjectName);
	void setDisplayedSceneryObjects(const std::vector<SceneryObject>& sceneryObjects) noexcept;
	SceneryObject* insertDisplayedSceneryObject(uint index, const SceneryObject& sceneryObject);
	SceneryObject* addDisplayedSceneryObject(const SceneryObject& sceneryObject);
	SceneryObject* addDisplayedSceneryObject(SceneryObject&& sceneryObject);
	bool removeDisplayedSceneryObject(const QString& sceneryObjectName);
	void clearDisplayedSceneryObject() noexcept;

	const std::vector<Sound>* getSounds() const noexcept;
	const Sound* getSound(const QString& soundName) const;
	Sound*       getSound(const QString& soundName);
	void setSounds(const std::vector<Sound>& sounds) noexcept;
	Sound* insertSound(uint index, const Sound& sound);
	Sound* addSound(const Sound& sound);
	Sound* addSound(Sound&& sound);
	bool removeSound(const QString& soundName);
	void clearSounds() noexcept;

	MusicPlaylist musicPlaylist;

private:
	QString     backgroundAssetImageName_ = "";
	AssetImage* backgroundAssetImage_     = nullptr;

	std::vector<Character>     displayedCharacters_;

	std::vector<SceneryObject> displayedSceneryObjects_;

	/// Sounds that haven't been played yet, but they are supossed to be played at some point in time
	/// `void update()` should remove already played ones
	std::vector<Sound> sounds_;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};