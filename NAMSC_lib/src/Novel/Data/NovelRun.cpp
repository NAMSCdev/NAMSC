#include "Novel/Data/Novel.h"

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

void Scene::run()
{
	const NovelState* currentState = NovelState::getCurrentlyLoadedState();
	uint eventID = currentState->eventID;

	if (eventID >= events_.size())
	{
		qCritical() << NovelLib::ErrorType::SaveCritical << "Tried to run an Event past the `events_` container's size (" << eventID << ">=" << events_.size() << ") in a Scene \"" + name + '\"';
		return;
	}

	events_[eventID]->run();
}

void Scene::update()
{
	const NovelState* currentState = NovelState::getCurrentlyLoadedState();
	uint eventID = currentState->eventID;

	if (eventID >= events_.size())
	{
		qCritical() << NovelLib::ErrorType::SaveCritical << "Tried to update an Event past the `events_` container's size (" << eventID << ">=" << events_.size() << ") in a Scene \"" + name + '\"';
		return;
	}

	events_[eventID]->update();
}

void Scene::end()
{
	NovelState* currentState = NovelState::getCurrentlyLoadedState();

	QString currentScene = currentState->sceneName;
	if (currentState->eventID >= events_.size())
	{
		qCritical() << NovelLib::ErrorType::SaveCritical << "Tried to end an Event past the `events_` container's size (" << currentState->eventID << ">=" << events_.size() << ") in a Scene \"" + name + '\"';
		return;
	}

	getEvent(currentState->eventID)->end();
	if (currentScene == currentState->sceneName)
		if (++(currentState->eventID) < events_.size())
			getEvent(currentState->eventID)->run();
}

void Scene::syncWithSave() noexcept
{
	const NovelState* currentState = NovelState::getCurrentlyLoadedState();
	uint eventID = currentState->eventID;

	if (eventID >= events_.size())
	{
		qCritical() << NovelLib::ErrorType::SaveCritical << "Tried to synchronize an Event past the `events_` container's size (" << eventID << ">=" << events_.size() << ") with the Save in the slot" << currentState->saveSlot << "in a Scene \"" + name + '\"';
		return;
	}

	events_[eventID]->syncWithSave();
}