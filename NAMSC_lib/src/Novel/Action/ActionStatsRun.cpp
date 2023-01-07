#include "Novel/Action/Stat/ActionStatSetValue.h"

#include "Novel/Data/Save/NovelState.h"
#include "Novel/Data/Scene.h"

void ActionStatSetValue::run()
{
	qDebug() << "ActionStatSetValue::run in Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();
	ActionStat::run();	
	if (stat_ == nullptr)
		syncWithSave();

	//todo: evaluator magic here
	//stat_->setValueFromString(expression);

	onRun_(parentEvent, stat_, expression);
}