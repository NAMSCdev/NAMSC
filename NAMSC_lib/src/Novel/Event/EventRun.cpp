#include "Novel/Event/EventAll.h"
#include "Novel/Data/Novel.h"

void Event::run()
{
	Novel&          novel       = Novel::getInstance();
	SceneWidget*    sceneWidget = novel.getSceneWidget();
	QGraphicsScene* scene       = nullptr;
	if (sceneWidget)
		scene = sceneWidget->scene();
	if (!scene)
		return;

	scene->clear();
	ensureResourcesAreLoaded();

	scenery.render(sceneWidget);

	for (std::unique_ptr<Action>& action : actions_)
		action->run();
}

void Event::end()
{
	for (std::unique_ptr<Action>& action : actions_)
		action->end();
}

void Event::update()
{
	for (std::unique_ptr<Action>& action : actions_)
		action->update();
}

void Event::syncWithSave() noexcept
{
	for (std::unique_ptr<Action>& action : actions_)
		action->syncWithSave();
}

void Choice::run()
{
}

void EventChoice::run()
{
	Novel& novel = Novel::getInstance();

	Event::run();

	if (!choices.empty())
		emit novel.pendEventChoiceDisplay(choices);
}

void EventDialogue::run()
{
	Novel& novel             = Novel::getInstance();
	SceneWidget* sceneWidget = novel.getSceneWidget();
	QGraphicsScene* scene    = nullptr;
	if (sceneWidget)
		scene = sceneWidget->scene();
	if (!scene)
		return;

	Event::run();
	
	if (!sentences.empty())
		emit novel.pendEventDialogueDisplay(sentences, NovelState::getCurrentlyLoadedState()->sentenceID);
}

void EventInput::run()
{
	Event::run();
}

void EventInput::syncWithSave() noexcept
{
}

void EventIf::run()
{
	Event::run();
}

void EventEndIf::run()
{
	Event::run();
}

void EventJump::run()
{
	Event::run();
}

void EventWait::run()
{
	Event::run();
} 