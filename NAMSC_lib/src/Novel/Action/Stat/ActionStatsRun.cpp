#include "Novel/Action/Stat/ActionStatSetValue.h"

#include "Novel/Data/Save/NovelState.h"
#include "Novel/Data/Scene.h"

void ActionStat::syncWithSave() noexcept
{
	stat_ = NovelState::getCurrentlyLoadedState()->getStat(statName_);
	if (stat_ == nullptr)
		qCritical() << NovelLib::ErrorType::StatMissing << "Stat \"" + statName_ + "\" does not exist";
}

void ActionStatSetValue::run()
{
	//qDebug() << "ActionStatSetValue::run in Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();
	ActionStat::run();	
	if (stat_ == nullptr)
		syncWithSave();

	//todo: evaluator magic here
	//stat_->setValueFromString(expression);

	//TODO: pointer to the changed object
	onRun_(parentEvent, stat_, expression);
}