#include "Novel/Data/Novel.h"

#include <QDirIterator>

void NovelSettings::load()
{
	
}

void Novel::loadNovel(uint slot, bool createNew)
{
	//loadNovelEssentials();
	//NovelSettings::load();
	/*loadChapters();*/ if (createNew || !loadState(slot)) newState(slot);
	loadAssetsDefinitions();
	//loadVoices();
	loadDefaultSceneryObjectsDefinitions(); loadDefaultCharacterDefinitions();
	loadScenes();
}

void Novel::saveNovel(uint slot)
{
	// NOTE - todo remove NOTE when done
	// Loads the entire Novel from multiple files in a stage-based fashion to ensure the objects can setup pointers to the data from previous stage:
	// 1 - loading NovelSettings and NovelEssentials
	// 2 - loading NovelState (Stats and current Scenery) and Chapters
	// 3 - loading Assets Definitions (no Resources loaded)
	// 4 - loading Voices
	// 5 - loading SceneryObjects and Characters Definitions
	// 6 - loading Scenes

	saveScenes();
	saveDefaultSceneryObjectsDefinitions();
	saveDefaultCharacterDefinitions();
	saveVoices();
	//saveAssetsDefinitions();

	saveChapters();
	saveState();

	saveNovelEssentials();
	// todo saveNovelSettings();
}

void Novel::ensureResourcesAreLoaded()
{
}

void Novel::loadAssetsDefinitions()
{
	QDirIterator it(NovelSettings::getInstance().novelDir.path() + "/game/Assets", QStringList() << "*.png" << "*.jpg" << "*.jpeg", QDir::Files, QDirIterator::Subdirectories);
	while (it.hasNext()) {
		auto relPath = NovelSettings::getInstance().novelDir.relativeFilePath(it.next());
		AssetManager::getInstance().addAssetImageSceneryBackground(relPath, 0, 0, relPath);
		AssetManager::getInstance().addAssetImageSceneryObject(relPath, 0, 0, relPath);
	}
}

// empty for now
void Novel::saveAssetsDefinitions()
{
	//QDir assetsDir = QDir::currentPath();
	//assetsDir.mkpath("game\\Assets");
	//AssetManager::getInstance().saveAllAssetsDefinitions();
}

void Novel::loadChapters()
{
	QDirIterator it(NovelSettings::getInstance().novelDir.path() + "/game/Chapters", QStringList(), QDir::Files, QDirIterator::Subdirectories);
	while (it.hasNext()) {
		QFile serializedFile(it.next());
		serializedFile.open(QIODeviceBase::ReadOnly);

		QDataStream dataStream(&serializedFile);

		Chapter chapter;
		dataStream >> chapter;
		setChapter(chapter);
	}
}

void Novel::saveChapters()
{
	QDir chaptersDir = NovelSettings::getInstance().novelDir;
	chaptersDir.mkpath(NovelSettings::getInstance().novelDir.path() + "/game/Chapters");

	for (const std::pair<const QString, Chapter>& defaultChapterPair : chapters_)
	{
		const Chapter& defaultChapter = defaultChapterPair.second;
		QFile serializedFile(chaptersDir.path() + "/game/Chapters" + defaultChapter.name);
		serializedFile.open(QIODeviceBase::WriteOnly);

		QDataStream dataStream(&serializedFile);
		dataStream << defaultChapter;
	}
}

void Novel::loadDefaultCharacterDefinitions()
{
	QDirIterator it(NovelSettings::getInstance().novelDir.path() + "/game/Characters", QStringList(), QDir::Files, QDirIterator::Subdirectories);
	while (it.hasNext()) {
		QFile serializedFile(it.next());
		serializedFile.open(QIODeviceBase::ReadOnly);

		QDataStream dataStream(&serializedFile);

		Character character;
		dataStream >> character;
		setDefaultCharacter(character);
	}
}

void Novel::saveDefaultCharacterDefinitions()
{
	QDir charactersDir = NovelSettings::getInstance().novelDir;
	charactersDir.mkpath("game/Characters");

	for (const std::pair<QString, Character>& defaultCharacterPair : characterDefaults_)
	{
		const SceneryObject& defaultCharacter = defaultCharacterPair.second;
		QFile serializedFile(charactersDir.path() + "/game/Characters/" + defaultCharacter.name);
		serializedFile.open(QIODeviceBase::WriteOnly);

		QDataStream dataStream(&serializedFile);
		dataStream << defaultCharacter;
	}
}

void Novel::loadDefaultSceneryObjectsDefinitions()
{
	QDirIterator it(NovelSettings::getInstance().novelDir.path() + "/game/Objects", QStringList(), QDir::Files, QDirIterator::Subdirectories);
	while (it.hasNext()) {
		QFile serializedFile(it.next());
		serializedFile.open(QIODeviceBase::ReadOnly);

		QDataStream dataStream(&serializedFile);

		SceneryObject sceneryObject;
		dataStream >> sceneryObject;
		setDefaultSceneryObject(sceneryObject);
	}
}

void Novel::saveDefaultSceneryObjectsDefinitions()
{
	QDir objectDir = NovelSettings::getInstance().novelDir;
	objectDir.mkpath("game/Objects");

	for (const std::pair<QString, SceneryObject>& defaultSceneryObjectPair : sceneryObjectDefaults_)
	{
		const SceneryObject& defaultSceneryObject = defaultSceneryObjectPair.second;
		QFile serializedFile(objectDir.path() +  "/game/Objects/" + defaultSceneryObject.name);
		serializedFile.open(QIODeviceBase::WriteOnly);

		QDataStream dataStream(&serializedFile);
		dataStream << defaultSceneryObject;
	}
}

void Novel::loadNovelEssentials()
{
	QString novelTitle = "Пан Тадеуш: реальная история";

	QString defaultScene = "start";
	QDataStream dataStream("Novel\\novelMeta.bin");
	//dataStream << ;
}

// todo saveNovelEssentials
void Novel::saveNovelEssentials()
{
	QDataStream dataStream("Novel\\novelMeta.bin");
	//dataStream >> ;
}

void Novel::loadScenes()
{
	QDirIterator it(NovelSettings::getInstance().novelDir.path() + "/game/Scenes", QStringList(), QDir::Files, QDirIterator::Subdirectories);
	while (it.hasNext()) {
		auto val = it.next();
		QFile serializedFile(val);
		serializedFile.open(QIODeviceBase::ReadOnly);

		QDataStream dataStream(&serializedFile);

		qint64 dataPos = serializedFile.pos();

		QString sceneName;
		dataStream >> sceneName;

		qDebug() << "Hello: " << serializedFile.seek(dataPos);

		dataStream >> *addScene(std::move(Scene(sceneName)));
		//QString sceneName = scene.name;
		//addScene(std::move(scene));
	}
}

void Novel::saveScenes()
{
	QDir scenesDir = NovelSettings::getInstance().novelDir;
	scenesDir.mkpath("game/Scenes");

	for (const std::pair<const QString, Scene>& scenePair : scenes_)
	{
		const Scene& scene = scenePair.second;
		QFile serializedFile(scenesDir.path() + "/game/Scenes/" + scene.name);
		serializedFile.open(QIODeviceBase::WriteOnly);

		QDataStream dataStream(&serializedFile);
		dataStream << scene;
	}
}

void Novel::loadVoices()
{
	QDirIterator it(NovelSettings::getInstance().novelDir.path() + "/game/Voices", QStringList(), QDir::Files, QDirIterator::Subdirectories);
	while (it.hasNext()) {
		QFile serializedFile(it.next());
		serializedFile.open(QIODeviceBase::ReadOnly);

		QDataStream dataStream(&serializedFile);

		Voice voice;
		dataStream >> voice;
		setVoice(voice);
	}
}

void Novel::saveVoices()
{
	QDir voicesDir = NovelSettings::getInstance().novelDir;
	voicesDir.mkpath("game/Voices");

	for (const std::pair<const QString, Voice>& voicePair : voices_)
	{
		const Voice& voice = voicePair.second;
		QFile serializedFile(voicesDir.path() + "\\game\\Voices\\" + voice.name);
		serializedFile.open(QIODeviceBase::WriteOnly);

		QDataStream dataStream(&serializedFile);
		dataStream << voice;
	}
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

void Scene::ensureResourcesAreLoaded()
{
	const NovelState* currentState = NovelState::getCurrentlyLoadedState();
	uint              eventID      = currentState->eventID;

	if (eventID >= events_.size())
	{
		qCritical() << NovelLib::ErrorType::SaveCritical << "Tried to end an Event past the `events_` container's size (" << eventID << ">=" << events_.size() << ") in a Scene \"" + name + '\"';
		return;
	}

	events_[eventID]->ensureResourcesAreLoaded();
}