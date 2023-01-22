#include "Novel/Data/Novel.h"

#include "Novel/Event/EventChoice.h"

void Novel::run()
{
	getScene(state_.sceneName)->run();
}

void Novel::update()
{
	getScene(state_.sceneName)->update();
}

void Novel::choiceRun(uint choiceID)
{
	//Safety check first
	Scene*       scene       = getScene(state_.sceneName);
	EventChoice* eventChoice = dynamic_cast<EventChoice*>(scene->getEvent(state_.eventID).get());

	if (!eventChoice)
		qCritical() << NovelLib::ErrorType::Critical << "Tried to run a Choice, while the current Event is not of an EventChoice type";

	eventChoice->getChoice(choiceID)->run();
}

void Novel::end()
{
	getScene(state_.sceneName)->end();
}

void Novel::syncWithSave()
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

	getEvent(currentState->eventID)->run();
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

	if ((currentState->eventID + 1) < events_.size())
	{
		++currentState->eventID;
		run();
	}
}

void Scene::syncWithSave()
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