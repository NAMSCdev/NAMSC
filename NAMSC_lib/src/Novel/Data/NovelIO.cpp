#include "Novel/Data/Novel.h"

#include <QDirIterator>

void NovelSettings::load()
{
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