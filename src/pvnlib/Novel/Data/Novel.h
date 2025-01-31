#pragma once

#include <QElapsedTimer>

#include "pvnLib/Novel/Data/NovelSettings.h"
#include "pvnLib/Novel/Data/Save/NovelState.h"
#include "pvnLib/Novel/Data/Scene.h"
#include "pvnLib/Novel/Data/Text/Choice.h"
#include "pvnLib/Novel/Data/Text/Sentence.h"
#include "pvnLib/Novel/Data/Text/Voice.h"
#include "pvnLib/Novel/Data/Visual/Scenery/Character.h"
#include "pvnLib/Novel/Data/Visual/Scenery/Scenery.h"
#include "pvnLib/Novel/Widget/SceneWidget.h"

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

	void saveNovel(uint slot);

	/// Creates a new NovelState (resets the old one, if exists) and loads it into the SaveSlot
	void newState(uint slot);
	/// Loads Player's NovelState from a SaveFile in the given SaveSlot
	bool loadState(uint slot);
	/// Saves Player's NovelState to a SaveFile in the current SaveSlot
	void saveState();

	void syncWithSave() override;

	QString nextFreeChapterName() const noexcept;
	QString nextFreeSceneName()   const noexcept;

	const std::unordered_map<QString, Chapter>* getChapters() const noexcept;
	/// \exception Error Could not find a Chapter with this name
	const Chapter* getChapter(const QString& name) const;
	/// \exception Error Could not find a Chapter with this name
	Chapter*       getChapter(const QString& name);
	const std::unordered_map<QString, Chapter>* setChapters(const std::unordered_map<QString, Chapter>& chapters) noexcept;
	const std::unordered_map<QString, Chapter>* setChapters(std::unordered_map<QString, Chapter>&& chapters)      noexcept;
	Chapter* setChapter(const Chapter& chapter) noexcept;
	Chapter* setChapter(Chapter&& chapter)      noexcept;
	/// \exception Error Could not find a Chapter with `oldName`
	Chapter* renameChapter(const QString& oldName, const QString& newName);
	/// \exception Error Could not find a Chapter with this name
	bool removeChapter(const QString& name);
	void clearChapters() noexcept;

	const std::unordered_map<QString, Character>* getDefaultCharacters() const noexcept;
	/// \exception Error Could not find a Character with this name
	const Character* getDefaultCharacter(const QString& name) const;
	/// \exception Error Could not find a Character with this name
	Character*       getDefaultCharacter(const QString& name);
	const std::unordered_map<QString, Character>* setDefaultCharacters(const std::unordered_map<QString, Character>& characters) noexcept;
	const std::unordered_map<QString, Character>* setDefaultCharacters(std::unordered_map<QString, Character>&& characters)      noexcept;
	Character* setDefaultCharacter(const Character& character) noexcept;
	Character* setDefaultCharacter(Character&& character)      noexcept;
	/// \exception Error Could not find a Character with `oldName`
	Character* renameDefaultCharacter(const QString& oldName, const QString& newName);
	/// \exception Error Could not find a Character with this name
	bool removeDefaultCharacter(const QString& name);
	void clearDefaultCharacters() noexcept;

	const std::unordered_map<QString, SceneryObject>* getDefaultSceneryObjects() const noexcept;
	/// \exception Error Could not find a SceneryObject with this name
	const SceneryObject* getDefaultSceneryObject(const QString& name) const;
	/// \exception Error Could not find a SceneryObject with this name
	SceneryObject*       getDefaultSceneryObject(const QString& name);
	const std::unordered_map<QString, SceneryObject>* setDefaultSceneryObjects(const std::unordered_map<QString, SceneryObject>& sceneryObjects) noexcept;
	const std::unordered_map<QString, SceneryObject>* setDefaultSceneryObjects(std::unordered_map<QString, SceneryObject>&& sceneryObjects)      noexcept;
	SceneryObject* setDefaultSceneryObject(const SceneryObject& sceneryObject) noexcept;
	SceneryObject* setDefaultSceneryObject(SceneryObject&& sceneryObject)      noexcept;
	/// \exception Error Could not find a SceneryObject with `oldName`
	SceneryObject* renameDefaultSceneryObject(const QString& oldName, const QString& newName);
	/// \exception Error Could not find a SceneryObject with this name
	bool removeDefaultSceneryObject(const QString& name);
	void clearDefaultSceneryObject() noexcept;

	const std::unordered_map<QString, Scene>* getScenes() const noexcept;
	/// \exception Error Could not find a Scene with this name
	const Scene* getScene(const QString& name) const;
	/// \exception Error Could not find a Scene with this name
	Scene*       getScene(const QString& name);
	const std::unordered_map<QString, Scene>* setScenes(std::unordered_map<QString, Scene>&& scenes) noexcept;
	Scene* addScene(const Scene& scene) noexcept;
	Scene* addScene(Scene&& scene)      noexcept;
	/// \exception Error Could not find a Scene with `oldName`
	Scene* renameScene(const QString& oldName, const QString& newName);
	/// \exception Error Could not find a Scene with this name
	bool removeScene(const QString& name);
	void clearScenes() noexcept;

	const std::unordered_map<QString, Voice>* getVoices() const noexcept;
	/// \exception Error Could not find a Voice with this name
	const Voice* getVoice(const QString& name) const;
	/// \exception Error Could not find a Voice with this name
	Voice*       getVoice(const QString& name);
	const std::unordered_map<QString, Voice>* setVoices(const std::unordered_map<QString, Voice>& voices) noexcept;
	const std::unordered_map<QString, Voice>* setVoices(std::unordered_map<QString, Voice>&& voices)      noexcept;
	Voice* setVoice(const Voice& voice) noexcept;
	Voice* setVoice(Voice&& voice)      noexcept;
	/// \exception Error Could not find a Voice with `oldName`
	Voice* renameVoice(const QString& oldName, const QString& newName);
	/// \exception Error Could not find a Voice with this name
	bool removeVoice(const QString& name);
	void clearVoices() noexcept;

	void clearNovel() noexcept;

	/// Needs to be created after QApplication 
	/// It should be deleted by the QWidget it will be assigned to, instead of manually
	SceneWidget* createSceneWidget();
	SceneWidget* getSceneWidget();

	const NovelState* getStateAtSceneBeginning() noexcept;
	
	QString novelTitle   = "Пан Тадеуш: реальная история";

	QString defaultScene = "start";

public slots:
	void run()    override;
	void update() override;
	void choiceRun(uint choiceID);
	//Not a slot, but closely related to these above, so we place it here for clarity
public:
	void end()    override;

signals:
	void pendBackgroundDisplay(const QImage* img);
	void pendSceneryObjectsDisplay(const std::vector<SceneryObject>& sceneryObjects);
	void pendCharactersDisplay(const std::vector<Character>& characters);
	void pendEventDialogueDisplay(const std::vector<Sentence>& sentences, uint sentenceReadIndex);
	void pendEventChoiceDisplay(const QString& menuText, const std::vector<Choice>& choices);
	void pendSceneClear();

private:
	// Nothing can create the Novel, but its methods
	Novel() = default;

	// It is supposed to be empty
	void ensureResourcesAreLoaded() override;

	/// \todo implement this
	void loadAssetsDefinitions();
	void saveAssetsDefinitions();
	// Doesn't hold any Resources, so there is no distinguishment between Definition and Resource
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

	// Doesn't hold any Resources, so there is no distinguishment between Definition and Resource
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
	SceneWidget* sceneWidget_ = nullptr;
};