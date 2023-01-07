#include "Novel/Data/Novel.h"

#include "Helpers.h"
#include <QDirIterator>

Novel& Novel::getInstance()
{
	static Novel novelSingleton;
	return novelSingleton;
}

bool Novel::checkForErrors(bool bComprehensive) const
{
	bool bError = false;

	for (const std::pair<const QString, Voice>& voice : voices_)
		bError |= voice.second.checkForErrors(bComprehensive);

	for (const std::pair<const QString, SceneryObject>& defaultSceneryObject : sceneryObjectDefaults_)
		bError |= defaultSceneryObject.second.checkForErrors(bComprehensive);

	for (const std::pair<const QString, Character>& defaultCharacter : characterDefaults_)
		bError |= defaultCharacter.second.checkForErrors(bComprehensive);

	for (const std::pair<const QString, Scene>& scene : scenes_)
		bError |= scene.second.checkForErrors(bComprehensive);

	bError |= stateAtSceneBeginning_.checkForErrors();
	bError |= state_.checkForErrors();
	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);

	return bError;
}

void Novel::loadNovel(uint slot, bool createNew)
{
	loadNovelEssentials();
	//NovelSettings::load();
	/*loadChapters();*/ if (createNew || !loadState(slot)) newState(slot);
	loadAssetsDefinitions();
	//loadVoices();
	loadDefaultSceneryObjectsDefinitions(); loadDefaultCharacterDefinitions();
	loadScenes();
}

void Novel::run()
{
	if (!scenes_.contains(state_.sceneName))
	{
		qCritical() << NovelLib::ErrorType::SaveCritical << "The save is corrupted. It tries to run a Scene \"" + state_.sceneName + "\" that does not exist!";
		return;
	}

	getScene(state_.sceneName)->run();
}

void Novel::update()
{
	if (!scenes_.contains(state_.sceneName))
	{
		qCritical() << NovelLib::ErrorType::SaveCritical << "The save is corrupted. It tries to update a Scene \"" + state_.sceneName + "\" that does not exist!";
		return;
	}

	getScene(state_.sceneName)->update();
}

void Novel::end()
{
	if (!scenes_.contains(state_.sceneName))
	{
		qCritical() << NovelLib::ErrorType::SaveCritical << "The save is corrupted. It tries to end a Scene \"" + state_.sceneName + "\" that does not exist!";
		return;
	}

	for (std::pair<const QString, Scene>& scene : scenes_)
		scene.second.end();
}

void Novel::syncWithSave() noexcept
{
	if (!scenes_.contains(state_.sceneName))
	{
		qCritical() << NovelLib::ErrorType::SaveCritical << "The save is corrupted. Tried to synchronize the Novel with the Save in the slot" << state_.saveSlot;
		return;
	}

	for (std::pair<const QString, Scene>& scene : scenes_)
		scene.second.syncWithSave();
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

const std::unordered_map<QString, Voice>* Novel::getVoices() const noexcept
{
	return &voices_;
}

void Novel::setVoices(const std::unordered_map<QString, Voice>& voices) noexcept
{
	voices_ = voices;
}

const Voice* Novel::getVoice(const QString& voiceName) const noexcept
{
	return NovelLib::getFromNamedMap(voices_, voiceName, "Voice");
}

Voice* Novel::getVoice(const QString& voiceName) noexcept
{
	return NovelLib::getFromNamedMap(voices_, voiceName, "Voice");
}

void Novel::setVoice(const QString& voiceName, const Voice& voice) noexcept
{
	voices_[voiceName] = voice;
}

bool Novel::removeVoice(const QString& voiceName)
{
	return NovelLib::removeFromNamedMap(voices_, voiceName, "Voice");
}

void Novel::clearVoices()
{
	voices_.clear();
}

SceneWidget* Novel::getSceneWidget()
{
	return &sceneWidget_;
}

const std::unordered_map<QString, SceneryObject>* Novel::getSceneryObjectDefaults() const noexcept
{
	return &sceneryObjectDefaults_;
}

void Novel::setDefaultSceneryObjects(const std::unordered_map<QString, SceneryObject>& sceneryObjects) noexcept
{
	sceneryObjectDefaults_ = sceneryObjects;
}

const SceneryObject* Novel::getDefaultSceneryObject(const QString& sceneryObjectName) const noexcept
{                                                                                             
	return NovelLib::getFromNamedMap(sceneryObjectDefaults_, sceneryObjectName, "SceneryObject");
}

SceneryObject* Novel::getDefaultSceneryObject(const QString& sceneryObjectName) noexcept
{
	return NovelLib::getFromNamedMap(sceneryObjectDefaults_, sceneryObjectName, "SceneryObject");
}

void Novel::setDefaultSceneryObject(const QString& sceneryObjectName, const SceneryObject& sceneryObject) noexcept
{
	sceneryObjectDefaults_[sceneryObjectName] = sceneryObject;
}

bool Novel::removeDefaultSceneryObject(const QString& sceneryObjectName)
{
	return NovelLib::removeFromNamedMap(sceneryObjectDefaults_, sceneryObjectName, "SceneryObject");
}

void Novel::clearDefaultSceneryObject()
{
	sceneryObjectDefaults_.clear();
}

const std::unordered_map<QString, Character>* Novel::getCharacterDefaults() const noexcept
{
	return &characterDefaults_;
}

void Novel::setDefaultCharacters(const std::unordered_map<QString, Character>& characters) noexcept
{
	characterDefaults_ = characters;
}

const Character* Novel::getDefaultCharacter(const QString& characterName) const noexcept
{
	return NovelLib::getFromNamedMap(characterDefaults_, characterName, "Character");
}

Character* Novel::getDefaultCharacter(const QString& characterName) noexcept
{
	return NovelLib::getFromNamedMap(characterDefaults_, characterName, "Character");
}

void Novel::setDefaultCharacter(const QString& characterName, const Character& character) noexcept
{
	characterDefaults_[characterName] = character;
}

bool Novel::removeDefaultCharacter(const QString& characterName)
{
	return NovelLib::removeFromNamedMap(characterDefaults_, characterName, "Character");
}

void Novel::clearDefaultCharacters() noexcept
{
	characterDefaults_.clear();
}

const std::unordered_map<QString, Chapter>* Novel::getChapters() const noexcept
{
	return &chapters_;
}

void Novel::setChapters(const std::unordered_map<QString, Chapter>& chapters) noexcept
{
	chapters_ = chapters;
}

const Chapter* Novel::getChapter(const QString& chapterName) const noexcept
{
	return NovelLib::getFromNamedMap(chapters_, chapterName, "Chapter");
}

Chapter* Novel::getChapter(const QString& chapterName) noexcept
{
	return NovelLib::getFromNamedMap(chapters_, chapterName, "Chapter");
}

void Novel::setChapter(const QString& chapterName, const Chapter& chapter) noexcept
{
	chapters_[chapterName] = chapter;
}

bool Novel::removeChapter(const QString& chapterName)
{
	return NovelLib::removeFromNamedMap(chapters_, chapterName, "Chapter");
}

void Novel::clearChapters() noexcept
{
	chapters_.clear();
}

const std::unordered_map<QString, Scene>* Novel::getScenes() const noexcept
{
	return &scenes_;
}

void Novel::setScenes(const std::unordered_map<QString, Scene>& scenes) noexcept
{
	scenes_ = scenes;
}

const Scene* Novel::getScene(const QString& sceneName) const noexcept
{
	return NovelLib::getFromNamedMap(scenes_, sceneName, "Scene");
}

Scene* Novel::getScene(const QString& sceneName) noexcept
{
	return NovelLib::getFromNamedMap(scenes_, sceneName, "Scene");
}

void Novel::addScene(const QString& sceneName, Scene&& scene) noexcept
{
	scenes_.emplace(sceneName, std::move(scene));
}

bool Novel::removeScene(const QString& sceneName)
{
	return NovelLib::removeFromNamedMap(scenes_, sceneName, "Scene");
}

void Novel::clearScene()
{
	scenes_.clear();
}

const NovelState* Novel::getStateAtSceneBeginning() noexcept
{
	return &stateAtSceneBeginning_;
}

void Novel::ensureResourcesAreLoaded()
{
}

void Novel::loadAssetsDefinitions()
{
	QDirIterator it("Assets", QStringList() << "*.png", QDir::Files, QDirIterator::Subdirectories);
	while (it.hasNext())
		qDebug() << it.next();
}

void Novel::saveAssetsDefinitions()
{

}

void Novel::loadChapters()
{
}

void Novel::saveChapters()
{
}

void Novel::loadDefaultCharacterDefinitions()
{
}

void Novel::saveDefaultCharacterDefinitions()
{
}

void Novel::loadDefaultSceneryObjectsDefinitions()
{
}

void Novel::saveDefaultSceneryObjectsDefinitions()
{
}

void Novel::loadNovelEssentials()
{
	QString novelTitle = "Пан Тадеуш: реальная история";

	QString defaultScene = "start";
	QDataStream dataStream("Novel\\novelMeta.bin");
	//dataStream << ;
}

void Novel::saveNovelEssentials()
{
	QDataStream dataStream("Novel\\novelMeta.bin");
	//dataStream >> ;
}

void Novel::loadScenes()
{
}

void Novel::saveScenes()
{
}

void Novel::loadVoices()
{
}

void Novel::saveVoices()
{
}

void Novel::newState(uint slot)
{
	state_ = NovelState::reset(slot);
}

bool Novel::loadState(uint slot)
{
	state_ = std::move(NovelState::load(slot));
	return true;
}

void Novel::saveState()
{
	state_.save();
}
