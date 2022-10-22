#include "Global.h"
#include "Novel/Data/Novel.h"
#include "Novel/Action/Stat/ActionStatChange.h"
#include "Novel/Action/Stat/ActionStatVisibility.h"

void ActionStatChange::run()
{
	Action::run();
}

void ActionStatVisibilityChange::run()
{
	Action::run();
}




void ActionStat::syncWithSave()
{
	stat = Novel::getInstance().getCurrentState()->getStat(this->statName);
}

//`bool checkForErrors()` that needs access to the Novel
inline bool ActionStat::checkForErrors() const
{
	try
	{
		//Check if name is undefined
		if (statName == "")
		{
			qDebug() << "No Stat assigned. Was it deleted and not replaced?";
			return true;
		}
		const Stat* stat = Novel::getInstance().getCurrentState()->getStat(statName);
		//Check if there is an object with this name in the AssetManager's container 
		if (stat == nullptr)
		{
			qDebug() << "Stat \"" + statName + "\" could not be found. Definition file might be corrupted.";
			return true;
		}
	}
	catch (...)
	{
		return false;
	}

	return false;
}