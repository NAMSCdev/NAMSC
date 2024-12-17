#include "pvnLib/Novel/Event/EventAll.h"
#include "pvnLib/Novel/Data/Novel.h"

void Event::ensureResourcesAreLoaded()
{
	for (std::shared_ptr<Action>& action : actions_)
		action->ensureResourcesAreLoaded();

	scenery.ensureResourcesAreLoaded();
}