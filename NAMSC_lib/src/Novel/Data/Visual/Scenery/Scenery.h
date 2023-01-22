#pragma once

#include "Novel/Data/Audio/MusicPlaylist.h"
#include "Novel/Data/Audio/Sound.h"
#include "Novel/Data/Visual/Scenery/Character.h"

class SceneWidget;
class Scene;

/// All the media managed by the library
class Scenery final
{
	/// Swap trick
	friend void swap(Scenery& first, Scenery& second) noexcept;
public:
	explicit Scenery(const Scene* const parentScene) noexcept;
	/// \param backgroundAssetImage Copies the AssetImage pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization
	Scenery(const Scene* const parentScene, const QString& backgroundAssetImageName, const MusicPlaylist& musicPlaylist = MusicPlaylist(), const std::vector<Character>& displayedCharacters = std::vector<Character>(), const std::vector<SceneryObject>& displayedSceneryObjects = std::vector<SceneryObject>(), const std::vector<Sound>& sounds = std::vector<Sound>(), AssetImage* backgroundAssetImage = nullptr);
	Scenery(const Scenery& obj)               noexcept;
	Scenery(Scenery&& obj)                    noexcept;
	///This one needs to be optimized at the cost of strong exception safety, as it is frequently assigned during gameplay (so the performance is a priority here)
	///No swap trick to avoid containers reallocation
	Scenery& operator=(const Scenery& obj)    noexcept;
	bool operator==(const Scenery& obj) const noexcept;
	bool operator!=(const Scenery& obj) const noexcept = default;

	/// \exception Error A Character in `defaultVoice_`/`assetImage_` is invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const;

	void run();

	/// \todo Manage Sounds
	void update(uint elapsedTime);

	void render(SceneWidget* sceneWidget) const;

	/// Ensures Assets and Sounds are loaded and if not - loads them
	void ensureResourcesAreLoaded();

	void addAnimator(AnimatorSceneryObjectColor&&  animatorColor);
	void addAnimator(AnimatorSceneryObjectFade&&   animatorFade);
	void addAnimator(AnimatorSceneryObjectMove&&   animatorMove);
	void addAnimator(AnimatorSceneryObjectRotate&& animatorRotate);
	void addAnimator(AnimatorSceneryObjectScale&&  animatorScale);

	/// \todo Add **Persistence To New Event** mechanism
	void resetAnimators() noexcept;

	//TODO: ADD PARENTS BASED ON THE NOVEL STATE!

	QString getBackgroundAssetImageName()       const noexcept;
	const AssetImage* getBackgroundAssetImage() const noexcept;
	AssetImage*       getBackgroundAssetImage()       noexcept;
	void setBackgroundAssetImage(const QString& backgroundAssetImageName, AssetImage* backgroundAssetImage = nullptr) noexcept;

	const std::vector<Character>* getDisplayedCharacters() const noexcept;
	const Character* getDisplayedCharacter(uint index)     const;
	Character*       getDisplayedCharacter(uint index);
	const Character* getDisplayedCharacter(const QString& characterName) const;
	Character*       getDisplayedCharacter(const QString& characterName);
	const std::vector<Character>* setDisplayedCharacters(const std::vector<Character>& characters) noexcept;
	const std::vector<Character>* setDisplayedCharacters(std::vector<Character>&& characters)      noexcept;
	Character* insertDisplayedCharacter(uint index, const Character& character);
	Character* insertDisplayedCharacter(uint index, Character&& character);
	Character* reinsertDisplayedCharacter(uint index, uint newIndex);
	Character* addDisplayedCharacter(const Character& character);
	Character* addDisplayedCharacter(Character&& character);
	bool removeDisplayedCharacter(const QString& characterName);
	bool removeDisplayedCharacter(uint index);
	void clearDisplayedCharacters() noexcept;

	const std::vector<SceneryObject>* getDisplayedSceneryObjects() const noexcept;
	/// \exception Error Tried to get a SceneryObject past the `displayedSceneryObjects_` container's size
	const SceneryObject* getDisplayedSceneryObject(uint index)     const;
	/// \exception Error Tried to get a SceneryObject past the `displayedSceneryObjects_` container's size
	SceneryObject*       getDisplayedSceneryObject(uint index);
	const SceneryObject* getDisplayedSceneryObject(const QString& sceneryObjectName) const;
	SceneryObject*       getDisplayedSceneryObject(const QString& sceneryObjectName);
	const std::vector<SceneryObject>* setDisplayedSceneryObjects(const std::vector<SceneryObject>& sceneryObjects) noexcept;
	const std::vector<SceneryObject>* setDisplayedSceneryObjects(std::vector<SceneryObject>&& sceneryObjects)      noexcept;
	/// \exception Error Tried to insert a SceneryObject past the `displayedSceneryObjects_` container's size
	SceneryObject* insertDisplayedSceneryObject(uint index, const SceneryObject& sceneryObject);
	/// \exception Error Tried to insert a SceneryObject past the `displayedSceneryObjects_` container's size
	SceneryObject* insertDisplayedSceneryObject(uint index, SceneryObject&& sceneryObject);
	/// \exception Error Tried to reinsert a SceneryObject past the `displayedSceneryObjects_` container's size
	SceneryObject* reinsertDisplayedSceneryObject(uint index, uint newIndex);
	SceneryObject* addDisplayedSceneryObject(const SceneryObject& sceneryObject);
	SceneryObject* addDisplayedSceneryObject(SceneryObject&& sceneryObject);
	/// \exception Error Tried to remove a SceneryObject past the `displayedSceneryObjects_` container's size
	bool removeDisplayedSceneryObject(uint index);
	bool removeDisplayedSceneryObject(const QString& sceneryObjectName);
	void clearDisplayedSceneryObject() noexcept;

	const std::vector<Sound>* getSounds() const noexcept;
	/// \exception Error Tried to get a Sound past the `sounds_` container's size
	const Sound* getSound(uint index)     const;
	/// \exception Error Tried to get a Sound past the `sounds_` container's size
	Sound*       getSound(uint index);
	/// \exception Error Could not find a Sound with this name
	const Sound* getSound(const QString& soundName) const;
	/// \exception Error Could not find a Sound with this name
	Sound*       getSound(const QString& soundName);
	const std::vector<Sound>* setSounds(const std::vector<Sound>& sounds) noexcept;
	const std::vector<Sound>* setSounds(std::vector<Sound>&& sounds)      noexcept;
	//Sounds should be custom sorted
	/// \exception Error Tried to insert a Sound past the `sounds_` container's size
	//Sound* insertSound(uint index, const Sound& sound);
	/// \exception Error Tried to insert a Sound past the `sounds_` container's size
	//Sound* insertSound(uint index, Sound&& sound);
	/// \exception Error Tried to reinsert a Sound past the `sounds_` container's size
	//Sound* reinsertSound(uint index, uint newIndex);
	Sound* addSound(const Sound& sound);
	Sound* addSound(Sound&& sound);
	/// \exception Error Tried to remove a Sound past the `sounds_` container's size
	bool removeSound(uint index);
	/// \exception Error Could not find a Sound with this name
	bool removeSound(const QString& soundName);
	void clearSounds() noexcept;

	MusicPlaylist      musicPlaylist;
	const Scene* const parentScene = nullptr;
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