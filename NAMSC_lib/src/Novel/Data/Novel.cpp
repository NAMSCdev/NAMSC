#include "Novel/Data/Novel.h"

#include "Helpers.h"
#include <QDirIterator>

Novel& Novel::getInstance()
{
	static Novel novelSingleton;
	return novelSingleton;
}

QString Novel::nextFreeChapterName() const noexcept
{
	for (uint i = 0; i != chapters_.size(); ++i)
	{
		QString checked = "Chapter " + QString::number(i + 1);
		if (!chapters_.contains(checked))
			return checked;
	}
	return "Scene " + QString::number(chapters_.size() + 1);
}

QString Novel::nextFreeSceneName() const noexcept
{
	for (uint i = 0; i != scenes_.size(); ++i)
	{
		QString checked = "Scene " + QString::number(i + 1);
		if (!scenes_.contains(checked))
			return checked;
	}
	return "Scene " + QString::number(scenes_.size() + 1);
}

SceneWidget* Novel::createSceneWidget()
{
	sceneWidget_ = new SceneWidget(nullptr);
	connect(this,         &Novel::pendBackgroundDisplay,     sceneWidget_, &SceneWidget::displayBackground);
	connect(this,         &Novel::pendSceneryObjectsDisplay, sceneWidget_, &SceneWidget::displaySceneryObjects);
	connect(this,         &Novel::pendCharactersDisplay,     sceneWidget_, &SceneWidget::displayCharacters);
	connect(this,         &Novel::pendEventChoiceDisplay,    sceneWidget_, &SceneWidget::displayEventChoice);
	connect(this,         &Novel::pendEventDialogueDisplay,  sceneWidget_, &SceneWidget::displayEventDialogue);
	connect(sceneWidget_, &SceneWidget::pendNovelEnd,        this,         &Novel::end);
	connect(sceneWidget_, &SceneWidget::pendChoiceRun,       this,         &Novel::choiceRun);

	return sceneWidget_;
}

SceneWidget* Novel::getSceneWidget()
{
	return sceneWidget_;
}

const std::unordered_map<QString, Chapter>* Novel::getChapters() const noexcept
{
	return &chapters_;
}

const Chapter* Novel::getChapter(const QString& name) const
{
	return NovelLib::Helpers::mapGet(chapters_, name, "Chapter", NovelLib::ErrorType::ChapterMissing);
}

Chapter* Novel::getChapter(const QString& name)
{
	return NovelLib::Helpers::mapGet(chapters_, name, "Chapter", NovelLib::ErrorType::ChapterMissing);
}

const std::unordered_map<QString, Chapter>* Novel::setChapters(const std::unordered_map<QString, Chapter>& chapters) noexcept
{
	return &(chapters_ = chapters);
}

const std::unordered_map<QString, Chapter>* Novel::setChapters(std::unordered_map<QString, Chapter>&& chapters) noexcept
{
	return &(chapters_ = std::move(chapters));
}

Chapter* Novel::setChapter(const Chapter& chapter) noexcept
{
 	return NovelLib::Helpers::mapSet(chapters_, chapter, "Chapter", NovelLib::ErrorType::ChapterInvalid);
}

Chapter* Novel::setChapter(Chapter&& chapter) noexcept
{
	return NovelLib::Helpers::mapSet(chapters_, std::move(chapter), "Chapter", NovelLib::ErrorType::ChapterInvalid);
}

Chapter* Novel::renameChapter(const QString& oldName, const QString& newName)
{
	return NovelLib::Helpers::mapRename(chapters_, oldName, newName, "Chapter", NovelLib::ErrorType::ChapterMissing, NovelLib::ErrorType::ChapterInvalid);
}

bool Novel::removeChapter(const QString& name)
{
	return NovelLib::Helpers::mapRemove(chapters_, name, "Chapter", NovelLib::ErrorType::ChapterMissing);
}

void Novel::clearChapters() noexcept
{
	chapters_.clear();
}

const std::unordered_map<QString, Character>* Novel::getDefaultCharacters() const noexcept
{
	return &characterDefaults_;
}

const Character* Novel::getDefaultCharacter(const QString& name) const
{
	return NovelLib::Helpers::mapGet(characterDefaults_, name, "Character", NovelLib::ErrorType::CharacterMissing);
}

Character* Novel::getDefaultCharacter(const QString& name)
{
	return NovelLib::Helpers::mapGet(characterDefaults_, name, "Character", NovelLib::ErrorType::CharacterMissing);
}

const std::unordered_map<QString, Character>* Novel::setDefaultCharacters(const std::unordered_map<QString, Character>& characters) noexcept
{
	return &(characterDefaults_ = characters);
}

const std::unordered_map<QString, Character>* Novel::setDefaultCharacters(std::unordered_map<QString, Character>&& characters) noexcept
{
	return &(characterDefaults_ = std::move(characters));
}

Character* Novel::setDefaultCharacter(const Character& character) noexcept
{
	return NovelLib::Helpers::mapSet(characterDefaults_, character, "Character", NovelLib::ErrorType::CharacterInvalid);
}

Character* Novel::setDefaultCharacter(Character&& character) noexcept
{

	return NovelLib::Helpers::mapSet(characterDefaults_, std::move(character), "Character", NovelLib::ErrorType::CharacterInvalid);
}

Character* Novel::renameDefaultCharacter(const QString& oldName, const QString& newName)
{
	return NovelLib::Helpers::mapRename(characterDefaults_, oldName, newName, "Character", NovelLib::ErrorType::CharacterMissing, NovelLib::ErrorType::CharacterInvalid);
}

bool Novel::removeDefaultCharacter(const QString& name)
{
	return NovelLib::Helpers::mapRemove(characterDefaults_, name, "Character", NovelLib::ErrorType::CharacterMissing);
}

void Novel::clearDefaultCharacters() noexcept
{
	characterDefaults_.clear();
}

const std::unordered_map<QString, SceneryObject>* Novel::getDefaultSceneryObjects() const noexcept
{
	return &sceneryObjectDefaults_;
}

const SceneryObject* Novel::getDefaultSceneryObject(const QString& name) const
{
	return NovelLib::Helpers::mapGet(sceneryObjectDefaults_, name, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing);
}

SceneryObject* Novel::getDefaultSceneryObject(const QString& name)

{
	return NovelLib::Helpers::mapGet(sceneryObjectDefaults_, name, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing);
}

const std::unordered_map<QString, SceneryObject>* Novel::setDefaultSceneryObjects(const std::unordered_map<QString, SceneryObject>& sceneryObjects) noexcept
{
	return &(sceneryObjectDefaults_ = sceneryObjects);
}

const std::unordered_map<QString, SceneryObject>* Novel::setDefaultSceneryObjects(std::unordered_map<QString, SceneryObject>&& sceneryObjects) noexcept
{
	return &(sceneryObjectDefaults_ = std::move(sceneryObjects));
}

SceneryObject* Novel::setDefaultSceneryObject(const SceneryObject& sceneryObject) noexcept
{
	return NovelLib::Helpers::mapSet(sceneryObjectDefaults_, sceneryObject, "SceneryObject", NovelLib::ErrorType::SceneryObjectInvalid);
}

SceneryObject* Novel::setDefaultSceneryObject(SceneryObject&& sceneryObject) noexcept
{
	return NovelLib::Helpers::mapSet(sceneryObjectDefaults_, std::move(sceneryObject), "SceneryObject", NovelLib::ErrorType::SceneryObjectInvalid);
}

SceneryObject* Novel::renameDefaultSceneryObject(const QString& oldName, const QString& newName)
{
	return NovelLib::Helpers::mapRename(sceneryObjectDefaults_, oldName, newName, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing, NovelLib::ErrorType::SceneryObjectInvalid);
}

bool Novel::removeDefaultSceneryObject(const QString& name)
{
	return NovelLib::Helpers::mapRemove(sceneryObjectDefaults_, name, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing);
}

void Novel::clearDefaultSceneryObject() noexcept
{
	sceneryObjectDefaults_.clear();
}

const std::unordered_map<QString, Scene>* Novel::getScenes() const noexcept
{
	return &scenes_;
}

const Scene* Novel::getScene(const QString& name) const
{
	return NovelLib::Helpers::mapGet(scenes_, name, "Scene", NovelLib::ErrorType::SceneMissing);
}

Scene* Novel::getScene(const QString& name)
{
	return NovelLib::Helpers::mapGet(scenes_, name, "Scene", NovelLib::ErrorType::SceneMissing);
}

const std::unordered_map<QString, Scene>* Novel::setScenes(std::unordered_map<QString, Scene>&& scenes) noexcept
{
	return &(scenes_ = std::move(scenes));
}

Scene* Novel::addScene(const Scene& scene) noexcept
{
	return NovelLib::Helpers::mapSet(scenes_, scene, "Scene", NovelLib::ErrorType::SceneInvalid);
}

Scene* Novel::addScene(Scene&& scene) noexcept
{
	return NovelLib::Helpers::mapSet(scenes_, std::move(scene), "Scene", NovelLib::ErrorType::SceneInvalid);
}

Scene* Novel::renameScene(const QString& oldName, const QString& newName)
{
	return NovelLib::Helpers::mapRename(scenes_, oldName, newName, "Scene", NovelLib::ErrorType::SceneMissing, NovelLib::ErrorType::SceneInvalid);
}

bool Novel::removeScene(const QString& name)
{
	return NovelLib::Helpers::mapRemove(scenes_, name, "Scene", NovelLib::ErrorType::SceneMissing);
}

void Novel::clearScenes() noexcept
{
	scenes_.clear();
}

const std::unordered_map<QString, Voice>* Novel::getVoices() const noexcept
{
	return &voices_;
}

const Voice* Novel::getVoice(const QString& name) const
{
	return NovelLib::Helpers::mapGet(voices_, name, "Voice", NovelLib::ErrorType::VoiceMissing);
}

Voice* Novel::getVoice(const QString& name)
{
	return NovelLib::Helpers::mapGet(voices_, name, "Voice", NovelLib::ErrorType::VoiceMissing);
}

const std::unordered_map<QString, Voice>* Novel::setVoices(const std::unordered_map<QString, Voice>& voices) noexcept
{
	return &(voices_ = voices);
}

const std::unordered_map<QString, Voice>* Novel::setVoices(std::unordered_map<QString, Voice>&& voices) noexcept
{
	return &(voices_ = std::move(voices));
}

Voice* Novel::setVoice(const Voice& voice) noexcept
{
	return NovelLib::Helpers::mapSet(voices_, voice, "Voice", NovelLib::ErrorType::VoiceInvalid);
}

Voice* Novel::setVoice(Voice&& voice) noexcept
{
	return NovelLib::Helpers::mapSet(voices_, std::move(voice), "Voice", NovelLib::ErrorType::VoiceInvalid);
}

Voice* Novel::renameVoice(const QString& oldName, const QString& newName)
{
	return NovelLib::Helpers::mapRename(voices_, oldName, newName, "Voice", NovelLib::ErrorType::VoiceMissing, NovelLib::ErrorType::VoiceInvalid);
}

bool Novel::removeVoice(const QString& name)
{
	return NovelLib::Helpers::mapRemove(voices_, name, "Voice", NovelLib::ErrorType::VoiceMissing);
}

void Novel::clearVoices() noexcept
{
	voices_.clear();
}

void Novel::clearNovel() noexcept
{
	novelTitle   = "Пан Тадеуш: реальная история";
	defaultScene = "start";

	stateAtSceneBeginning_ = NovelState();
	state_                 = NovelState();
	novelStartElapsedTimer_.restart();
	sceneWidget_           = nullptr;

	clearChapters();
	clearDefaultCharacters();
	clearDefaultSceneryObject();
	clearScenes();
	clearVoices();
}

const NovelState* Novel::getStateAtSceneBeginning() noexcept
{
	return &stateAtSceneBeginning_;
}