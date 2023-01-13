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
	connect(this, &Novel::pendChangeBackground, sceneWidget_, &SceneWidget::changeBackground);
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

const Chapter* Novel::getChapter(const QString& chapterName) const
{
	return NovelLib::getFromNamedMap(chapters_, chapterName, "Chapter", NovelLib::ErrorType::ChapterMissing);
}

Chapter* Novel::getChapter(const QString& chapterName)
{
	return NovelLib::getFromNamedMap(chapters_, chapterName, "Chapter", NovelLib::ErrorType::ChapterMissing);
}

void Novel::setChapters(const std::unordered_map<QString, Chapter>& chapters) noexcept
{
	chapters_ = chapters;
}

Chapter* Novel::setChapter(const QString& chapterName, const Chapter& chapter)
{
 	return NovelLib::setInNamedMap(chapters_, chapterName, chapter, "Chapter", NovelLib::ErrorType::ChapterInvalid);
}

Chapter* Novel::renameChapter(const QString& oldName, const QString& newName)
{
	return NovelLib::renameInNamedMap(chapters_, oldName, newName, "Chapter", NovelLib::ErrorType::ChapterMissing, NovelLib::ErrorType::ChapterInvalid);
}

bool Novel::removeChapter(const QString& chapterName)
{
	return NovelLib::removeFromNamedMap(chapters_, chapterName, "Chapter", NovelLib::ErrorType::ChapterMissing);
}

void Novel::clearChapters() noexcept
{
	chapters_.clear();
}

const std::unordered_map<QString, Character>* Novel::getCharacterDefaults() const noexcept
{
	return &characterDefaults_;
}

const Character* Novel::getDefaultCharacter(const QString& characterName) const
{
	return NovelLib::getFromNamedMap(characterDefaults_, characterName, "Character", NovelLib::ErrorType::CharacterMissing);
}

Character* Novel::getDefaultCharacter(const QString& characterName)
{
	return NovelLib::getFromNamedMap(characterDefaults_, characterName, "Character", NovelLib::ErrorType::CharacterMissing);
}

void Novel::setDefaultCharacters(const std::unordered_map<QString, Character>& characters) noexcept
{
	characterDefaults_ = characters;
}

Character* Novel::setDefaultCharacter(const QString& characterName, const Character& character)
{
	return NovelLib::setInNamedMap(characterDefaults_, characterName, character, "Character", NovelLib::ErrorType::CharacterInvalid);
}

Character* Novel::renameDefaultCharacter(const QString& oldName, const QString& newName)
{
	return NovelLib::renameInNamedMap(characterDefaults_, oldName, newName, "Character", NovelLib::ErrorType::CharacterMissing, NovelLib::ErrorType::CharacterInvalid);
}

bool Novel::removeDefaultCharacter(const QString& characterName)
{
	return NovelLib::removeFromNamedMap(characterDefaults_, characterName, "Character", NovelLib::ErrorType::CharacterMissing);
}

void Novel::clearDefaultCharacters() noexcept
{
	characterDefaults_.clear();
}

const std::unordered_map<QString, SceneryObject>* Novel::getSceneryObjectDefaults() const noexcept
{
	return &sceneryObjectDefaults_;
}

const SceneryObject* Novel::getDefaultSceneryObject(const QString& sceneryObjectName) const
{
	return NovelLib::getFromNamedMap(sceneryObjectDefaults_, sceneryObjectName, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing);
}

SceneryObject* Novel::getDefaultSceneryObject(const QString& sceneryObjectName)
{
	return NovelLib::getFromNamedMap(sceneryObjectDefaults_, sceneryObjectName, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing);
}

void Novel::setDefaultSceneryObjects(const std::unordered_map<QString, SceneryObject>& sceneryObjects) noexcept
{
	sceneryObjectDefaults_ = sceneryObjects;
}

SceneryObject* Novel::setDefaultSceneryObject(const QString& sceneryObjectName, const SceneryObject& sceneryObject)
{
	return NovelLib::setInNamedMap(sceneryObjectDefaults_, sceneryObjectName, sceneryObject, "SceneryObject", NovelLib::ErrorType::SceneryObjectInvalid);
}

SceneryObject* Novel::renameDefaultSceneryObject(const QString& oldName, const QString& newName)
{
	return NovelLib::renameInNamedMap(sceneryObjectDefaults_, oldName, newName, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing, NovelLib::ErrorType::SceneryObjectInvalid);
}

bool Novel::removeDefaultSceneryObject(const QString& sceneryObjectName)
{
	return NovelLib::removeFromNamedMap(sceneryObjectDefaults_, sceneryObjectName, "SceneryObject", NovelLib::ErrorType::SceneryObjectMissing);
}

void Novel::clearDefaultSceneryObject() noexcept
{
	sceneryObjectDefaults_.clear();
}

const std::unordered_map<QString, Scene>* Novel::getScenes() const noexcept
{
	return &scenes_;
}

const Scene* Novel::getScene(const QString& sceneName) const
{
	//TODO: Scene errors
	return NovelLib::getFromNamedMap(scenes_, sceneName, "Scene");
}

Scene* Novel::getScene(const QString& sceneName)
{
	//TODO: Scene errors
	return NovelLib::getFromNamedMap(scenes_, sceneName, "Scene");
}

Scene* Novel::addScene(const QString& sceneName, Scene&& scene)
{
	//TODO: Scene errors
	return NovelLib::addToNamedMap(scenes_, sceneName, std::move(scene), "Scene");
}

Scene* Novel::renameScene(const QString& oldName, const QString& newName)
{
	//TODO: Scene errors
	return NovelLib::renameInNamedMap(scenes_, oldName, newName, "Scene");
}

bool Novel::removeScene(const QString& sceneName)
{
	//TODO: Scene errors
	return NovelLib::removeFromNamedMap(scenes_, sceneName, "Scene");
}

void Novel::clearScene() noexcept
{
	scenes_.clear();
}

const std::unordered_map<QString, Voice>* Novel::getVoices() const noexcept
{
	return &voices_;
}
const Voice* Novel::getVoice(const QString& voiceName) const
{
	return NovelLib::getFromNamedMap(voices_, voiceName, "Voice", NovelLib::ErrorType::VoiceMissing);
}

Voice* Novel::getVoice(const QString& voiceName)
{
	return NovelLib::getFromNamedMap(voices_, voiceName, "Voice", NovelLib::ErrorType::VoiceMissing);
}

void Novel::setVoices(const std::unordered_map<QString, Voice>& voices) noexcept
{
	voices_ = voices;
}

Voice* Novel::setVoice(const QString& voiceName, const Voice& voice)
{
	return NovelLib::setInNamedMap(voices_, voiceName, voice, "Voice", NovelLib::ErrorType::VoiceInvalid);
}

Voice* Novel::renameVoice(const QString& oldName, const QString& newName)
{
	return NovelLib::renameInNamedMap(voices_, oldName, newName, "Voice", NovelLib::ErrorType::VoiceMissing, NovelLib::ErrorType::VoiceInvalid);
}

bool Novel::removeVoice(const QString& voiceName)
{
	return NovelLib::removeFromNamedMap(voices_, voiceName, "Voice", NovelLib::ErrorType::VoiceMissing);
}

void Novel::clearVoices() noexcept
{
	voices_.clear();
}

const NovelState* Novel::getStateAtSceneBeginning() noexcept
{
	return &stateAtSceneBeginning_;
}