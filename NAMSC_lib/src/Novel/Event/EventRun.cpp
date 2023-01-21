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

	for (std::shared_ptr<Action>& action : actions_)
		action->run();
}

void Event::end()
{
	for (std::shared_ptr<Action>& action : actions_)
		action->end();
}

void Event::update()
{
	for (std::shared_ptr<Action>& action : actions_)
		action->update();
}

void Event::syncWithSave()
{
	for (std::shared_ptr<Action>& action : actions_)
		action->syncWithSave();
}

void Choice::run()
{
}

void EventChoice::run()
{
	Novel& novel = Novel::getInstance();

	Event::run();

	if (!choices_.empty())
		emit novel.pendEventChoiceDisplay(choices_);
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
	
	if (!sentences_.empty())
		emit novel.pendEventDialogueDisplay(sentences_, NovelState::getCurrentlyLoadedState()->sentenceID);
}

void EventInput::run()
{
	Event::run();
}

void EventInput::syncWithSave()
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