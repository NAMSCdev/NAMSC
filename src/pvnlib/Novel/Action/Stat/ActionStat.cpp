#include "pvnLib/Novel/Action/Stat/ActionStat.h"

#include "pvnLib/Novel/Data/Save/NovelState.h"
#include "pvnLib/Novel/Data/Scene.h"

ActionStat::~ActionStat() = default;

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionStat& first, ActionStat& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<Action&>(first), static_cast<Action&>(second));
	swap(first.statName_, second.statName_);
	swap(first.stat_,     second.stat_);
}

ActionStat::ActionStat(Event* const parentEvent, const QString& statName, std::shared_ptr<Stat> stat)
	: Action(parentEvent), 
	statName_(statName), 
	stat_(stat)
{
}

bool ActionStat::operator==(const ActionStat& obj) const noexcept
{
	if (this == &obj) return true;

	return statName_ == obj.statName_;//&&
		   //stat_     == obj.stat_;
}

void ActionStat::serializableLoad(QDataStream& dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> statName_;
}

void ActionStat::serializableSave(QDataStream& dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << statName_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

QString ActionStat::getStatName() const noexcept
{
	return statName_;
}

const std::shared_ptr<Stat> ActionStat::getStat() const noexcept
{
	return stat_;
}

std::shared_ptr<Stat> ActionStat::getStat() noexcept
{ 
	return stat_; 
}

void ActionStat::setStat(const QString& statName, std::shared_ptr<Stat> stat) noexcept
{
	if (stat)
	{
		if (stat->name != statName)
		{
			qCritical() << NovelLib::ErrorType::StatInvalid << "Stat's name missmatch (statName=\"" + statName + "\", stat->name=\"" + stat->name + "\")";
			return;
		}
	}
	else stat = NovelState::getCurrentlyLoadedState()->getStat(statName);
	
	if (!stat)
	{
		qCritical() << NovelLib::ErrorType::StatMissing << "Stat \"" + statName + "\" does not exist";
		return;
	}

	statName_ = statName;
	stat_     = stat;
	errorCheck(true);
}