#pragma once

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
class Novel final : public QObject, public NovelFlowInterface
{
	Q_OBJECT
	friend NovelSettings;
	friend NovelState;
public:
	static Novel& getInstance();

	Novel(const Novel&)            noexcept = delete;
	Novel(Novel&&)                 noexcept = delete;
	Novel& operator=(const Novel&) noexcept = delete;

	bool errorCheck(bool bComprehensive = false) const override;

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

	void run()    override;
	void update() override;
	void end()    override;

	void syncWithSave() noexcept override;

	QString nextFreeChapterName() const noexcept;
	QString nextFreeSceneName()   const noexcept;

	const std::unordered_map<QString, Chapter>* getChapters() const noexcept;
	const Chapter* getChapter(const QString& chapterName)     const;
	Chapter*       getChapter(const QString& chapterName);
	void setChapters(const std::unordered_map<QString, Chapter>& chapters) noexcept;
	Chapter* setChapter(const QString& chapterName, const Chapter& chapter);
	Chapter* renameChapter(const QString& oldName, const QString& newName);
	bool removeChapter(const QString& chapterName);
	void clearChapters() noexcept;

	const std::unordered_map<QString, Character>* getCharacterDefaults() const noexcept;
	const Character* getDefaultCharacter(const QString& characterName)   const;
	Character*       getDefaultCharacter(const QString& characterName);
	void setDefaultCharacters(const std::unordered_map<QString, Character>& characters) noexcept;
	Character* setDefaultCharacter(const QString& characterName, const Character& character);
	Character* renameDefaultCharacter(const QString& oldName, const QString& newName);
	bool removeDefaultCharacter(const QString& characterName);
	void clearDefaultCharacters() noexcept;

	const std::unordered_map<QString, SceneryObject>* getSceneryObjectDefaults()   const noexcept;
	const SceneryObject* getDefaultSceneryObject(const QString& sceneryObjectName) const;
	SceneryObject*       getDefaultSceneryObject(const QString& sceneryObjectName);
	void setDefaultSceneryObjects(const std::unordered_map<QString, SceneryObject>& sceneryObjects) noexcept;
	SceneryObject* setDefaultSceneryObject(const QString& sceneryObjectName, const SceneryObject& sceneryObject);
	SceneryObject* renameDefaultSceneryObject(const QString& oldName, const QString& newName);
	bool removeDefaultSceneryObject(const QString& sceneryObjectName);
	void clearDefaultSceneryObject() noexcept;

	const std::unordered_map<QString, Scene>* getScenes() const noexcept;
	const Scene* getScene(const QString& sceneName)       const;
	Scene*       getScene(const QString& sceneName);
	/// Takes ownership of the Scene
	/// Also corrects jumps to Scenes that theirs index changed
	Scene* addScene(const QString& sceneName, Scene&& scene);
	Scene* renameScene(const QString& oldName, const QString& newName);
	/// Also corrects jumps to Scenes that theirs index changed
	bool removeScene(const QString& sceneName);
	void clearScene() noexcept;

	const std::unordered_map<QString, Voice>* getVoices() const noexcept;
	const Voice* getVoice(const QString& voiceName)       const;
	Voice*       getVoice(const QString& voiceName);
	void setVoices(const std::unordered_map<QString, Voice>& voices) noexcept;
	Voice* setVoice(const QString& voiceName, const Voice& voice);
	Voice* renameVoice(const QString& oldName, const QString& newName);
	bool removeVoice(const QString& voiceName);
	void clearVoices() noexcept;

	/// Needs to be created after QApplication 
	/// It should be deleted by the QWidget it will be assigned to, instead of manually
	SceneWidget* createSceneWidget();
	SceneWidget* getSceneWidget();

	const NovelState* getStateAtSceneBeginning() noexcept;
	
	QString novelTitle   = "Пан Тадеуш: реальная история";

	QString defaultScene = "start";

signals:
	void pendChangeBackground(const QImage* img);

private:
	//Nothing can create the Novel, but its methods
	Novel() = default;

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

	std::unordered_map<QString, Chapter>       chapters_;
	std::unordered_map<QString, Character>     characterDefaults_;
	std::unordered_map<QString, SceneryObject> sceneryObjectDefaults_;
	std::unordered_map<QString, Scene>         scenes_;
	std::unordered_map<QString, Voice>         voices_;

	/// This one refers to the beginning of the current Scene, as the Novel will always be saved at this point if the User chooses to save
	/// It is preferred to replay the last Scene, so the User does not lose the context of the Novel upon loading, as this contains Media changes that will not be journalized anywhere else
	NovelState stateAtSceneBeginning_;

	/// Contains current the player's progression, including changes made past the beginning of the Scene
	NovelState state_;

	/// Calculates time since the Save was loaded
	QElapsedTimer novelStartElapsedTimer_;

	/// Renders the Scene (its Scenery)
	SceneWidget* sceneWidget_;
};