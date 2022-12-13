#pragma once

#include "Novel/Data/Audio/MusicPlaylist.h"
#include "Novel/Data/Audio/Sound.h"
#include "Novel/Data/Visual/Scenery/Character.h"

/// All the media managed by the library
struct Scenery final
{
	Scenery()                                 = default;
	Scenery(const QString& backgroundAssetImageName, const MusicPlaylist& musicPlaylist, const std::unordered_map<QString, Character>& displayedCharacters, const std::unordered_map<QString, SceneryObject>& displayedSceneryObjects, const std::unordered_map<QString, Sound>& sounds);
	Scenery(const Scenery& obj)               = default;
	Scenery& operator=(Scenery obj) noexcept;
	bool operator==(const Scenery& obj) const = default;
	bool operator!=(const Scenery& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error A Character in `defaultVoice_`/`assetImage_` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const;

	void run();
	/// \todo Manage Sounds
	void update(uint elapsedTime);

	/// Ensures Assets amd Sounds are loaded and if not - loads them
	void ensureResourcesAreLoaded();

	void addAnimator(AnimatorSceneryObjectColor&& animatorColor);
	void addAnimator(AnimatorSceneryObjectFade&& animatorFade);
	void addAnimator(AnimatorSceneryObjectMove&& animatorMove);
	void addAnimator(AnimatorSceneryObjectRotate&& animatorRotate);
	void addAnimator(AnimatorSceneryObjectScale&& animatorScale);

	/// \todo Add **Persistence To New Event** mechanism
	void resetAnimators() noexcept;

	const AssetImage* getBackgroundAssetImage() const noexcept;
	AssetImage* getBackgroundAssetImage() noexcept;
	QString getBackgroundAssetImageName() const noexcept;
	void setBackgroundAssetImage(const QString& assetImageName, AssetImage* assetImage = nullptr) noexcept;

	const std::unordered_map<QString, Character>* getDisplayedCharacters() const noexcept;
	void setDisplayedCharacters(const std::unordered_map<QString, Character>& sceneryObjects) noexcept;
	const Character* getDisplayedCharacter(const QString& characterName) const noexcept;
	Character* getDisplayedCharacter(const QString& characterName) noexcept;
	void setDisplayedCharacter(const QString& characterName, const Character& character) noexcept;
	bool removeDisplayedCharacter(const QString& characterName) noexcept;

	const std::unordered_map<QString, SceneryObject>* getDisplayedSceneryObjects() const noexcept;
	void setDisplayedSceneryObjects(const std::unordered_map<QString, SceneryObject>& sceneryObjects) noexcept;
	const SceneryObject* getDisplayedSceneryObject(const QString& sceneryObjectName) const noexcept;
	SceneryObject* getDisplayedSceneryObject(const QString& sceneryObjectName) noexcept;
	void setDisplayedSceneryObject(const QString& sceneryObjectName, const SceneryObject& sceneryObject) noexcept;
	bool removeDisplayedSceneryObject(const QString& sceneryObjectName) noexcept;

	const std::unordered_map<QString, Sound>* getSounds() const noexcept;
	void setSounds(const std::unordered_map<QString, Sound>& sounds) noexcept;
	const Sound* getSound(const QString& soundName) const noexcept;
	Sound* getSound(const QString& soundName) noexcept;
	void setSound(const QString& soundName, const Sound& sound) noexcept;
	bool removeSound(const QString& soundName) noexcept;

	MusicPlaylist musicPlaylist;

private:
	QString     backgroundAssetImageName_ = "";
	AssetImage* backgroundAssetImage_     = nullptr;

	std::unordered_map<QString, Character>     displayedCharacters_;

	std::unordered_map<QString, SceneryObject> displayedSceneryObjects_;

	/// Sounds that haven't been played yet, but they are supossed to be played at some point in time
	/// `void update()` should remove already played ones
	std::unordered_map<QString, Sound> sounds_;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};