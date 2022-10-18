#include "Global.h"
#include "Novel/Data/Novel.h"
#include "Novel/Action/Stat/ActionStatChange.h"
#include "Novel/Action/Stat/ActionStatVisibilityChange.h"

void ActionStat::syncWithSave()
{
	stat = Novel::getInstance().getNovelState()->getStat(this->statName);
}

void ActionStatChange::run()
{
	Action::run();
}

void ActionStatVisibilityChange::run()
{
	Action::run();
}

