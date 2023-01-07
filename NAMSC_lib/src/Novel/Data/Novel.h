﻿#pragma once

#include <QElapsedTimer>

#include "Novel/Data/NovelSettings.h"
#include "Novel/Data/Save/NovelState.h"
#include "Novel/Data/Scene.h"
#include "Novel/Data/Text/Voice.h"
#include "Novel/Data/Visual/Scenery/Character.h"
#include "Novel/Data/Visual/Scenery/Scenery.h"
#include "Novel/Widget/SceneWidget.h"

/// The entire Visual Novel
/// **Singleton**
class Novel final : public NovelFlowInterface
{
	friend NovelSettings;
	friend NovelState;
public:
	static Novel& getInstance();

	Novel()                        = default;
	Novel(const Novel&)            = delete;
	Novel& operator=(const Novel&) = delete;

	bool checkForErrors(bool bComprehensive = false) const override;

	/// Loads the entire Novel from multiple files in a stage-based fashion to ensure the objects can setup pointers to the data from previous stage:
	/// 1 - loading NovelSettings and NovelEssentials
	/// 2 - loading NovelState (Stats and current Scenery) and Chapters
	/// 3 - loading Assets Definitions (no Resources loaded)
	/// 4 - loading Voices
	/// 5 - loading SceneryObjects and Characters Definitions
	/// 6 - loading Scenes
	void loadNovel(uint slot, bool createNew);

	/// Creates a new NovelState (resets the old one, if exists) and loads it into the SaveSlot
	void newState(uint slot);
	/// Loads Player's NovelState from a SaveFile in the given SaveSlot
	bool loadState(uint slot);
	/// Saves Player's NovelState to a SaveFile in the current SaveSlot
	void saveState();

	void run() override;
	void update() override;
	void end() override;

	void syncWithSave() noexcept override;

	QString nextFreeChapterName() const noexcept;
	QString nextFreeSceneName() const noexcept;

	const std::unordered_map<QString, Chapter>* getChapters() const noexcept;
	void setChapters(const std::unordered_map<QString, Chapter>& chapters) noexcept;
	const Chapter* getChapter(const QString& chapterName) const noexcept;
	Chapter* getChapter(const QString& chapterName) noexcept;
	void setChapter(const QString& chapterName, const Chapter& chapter) noexcept;
	//TODO: add exceptions
	bool removeChapter(const QString& chapterName);
	void clearChapters() noexcept;

	const std::unordered_map<QString, Character>* getCharacterDefaults() const noexcept;
	void setDefaultCharacters(const std::unordered_map<QString, Character>& characters) noexcept;
	const Character* getDefaultCharacter(const QString& characterName) const noexcept;
	Character* getDefaultCharacter(const QString& characterName) noexcept;
	void setDefaultCharacter(const QString& characterName, const Character& character) noexcept;
	//TODO: add exceptions
	bool removeDefaultCharacter(const QString& characterName);
	void clearDefaultCharacters() noexcept;

	const std::unordered_map<QString, SceneryObject>* getSceneryObjectDefaults() const noexcept;
	void setDefaultSceneryObjects(const std::unordered_map<QString, SceneryObject>& sceneryObjects) noexcept;
	const SceneryObject* getDefaultSceneryObject(const QString& sceneryObjectName) const noexcept;
	SceneryObject* getDefaultSceneryObject(const QString& sceneryObjectName) noexcept;
	void setDefaultSceneryObject(const QString& sceneryObjectName, const SceneryObject& sceneryObject) noexcept;
	//TODO: add exceptions
	bool removeDefaultSceneryObject(const QString& sceneryObjectName);
	void clearDefaultSceneryObject();

	const std::unordered_map<QString, Scene>* getScenes() const noexcept;
	void setScenes(const std::unordered_map<QString, Scene>& scenes) noexcept;
	const Scene* getScene(const QString& sceneName) const noexcept;
	Scene* getScene(const QString& sceneName) noexcept;
	/// Also corrects jumps to Scenes that theirs index changed
	void addScene(const QString& sceneName, Scene&& scene) noexcept;
	/// Also corrects jumps to Scenes that theirs index changed
	//TODO: add exceptions
	bool removeScene(const QString& sceneName);
	void clearScene();

	const std::unordered_map<QString, Voice>* getVoices() const noexcept;
	void setVoices(const std::unordered_map<QString, Voice>& voices) noexcept;
	const Voice* getVoice(const QString& voiceName) const noexcept;
	Voice* getVoice(const QString& voiceName) noexcept;
	void setVoice(const QString& voiceName, const Voice& voice) noexcept;
	//TODO: add exceptions
	bool removeVoice(const QString& voiceName);
	void clearVoices();

	SceneWidget* getSceneWidget();

	const NovelState* getStateAtSceneBeginning() noexcept;
	
	QString novelTitle   = "Пан Тадеуш: реальная история";

	QString defaultScene = "start";

private:
	//It is supposed to be empty
	void ensureResourcesAreLoaded() override;

	/// \todo implement this
	void loadAssetsDefinitions();
	void saveAssetsDefinitions();
	//Doesn't hold any Resources, so there is no distinguishment between Definition and Resource
	/// \todo implement this
	void loadChapters();
	void saveChapters();
	void loadDefaultCharacterDefinitions();
	void saveDefaultCharacterDefinitions();

	void loadDefaultSceneryObjectsDefinitions();
	void saveDefaultSceneryObjectsDefinitions();

	void loadNovelEssentials();
	void saveNovelEssentials();

	/// \todo implement this
	void loadScenes();
	void saveScenes();

	//Doesn't hold any Resources, so there is no distinguishment between Definition and Resource
	/// \todo implement this
	void loadVoices();
	void saveVoices();

	std::unordered_map<QString, Chapter> chapters_;
	std::unordered_map<QString, Character> characterDefaults_;
	std::unordered_map<QString, SceneryObject> sceneryObjectDefaults_;
	std::unordered_map<QString, Scene> scenes_;
	std::unordered_map<QString, Voice> voices_;

	/// This one refers to the beginning of the current Scene, as the Novel will always be saved at this point if the User chooses to save
	/// It is preferred to replay the last Scene, so the User does not lose the context of the Novel upon loading, as this contains Media changes that will not be journalized anywhere else
	NovelState stateAtSceneBeginning_;

	/// Contains current the player's progression, including changes made past the beginning of the Scene
	NovelState state_;

	/// Calculates time since the Save was loaded
	QElapsedTimer novelStartElapsedTimer_;

	/// Renders the Scene (its Scenery)
	SceneWidget sceneWidget_;
};