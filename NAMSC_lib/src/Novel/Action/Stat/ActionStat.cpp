#include "Novel/Action/Stat/ActionStat.h"

#include "Novel/Data/Save/NovelState.h"
#include "Novel/Data/Scene.h"

ActionStat::ActionStat(Event* const parentEvent) noexcept
	: Action(parentEvent)
{
}

ActionStat::ActionStat(Event* const parentEvent, const QString& statName)
	: Action(parentEvent), statName_(statName)
{
	checkForErrors(true);
}

ActionStat& ActionStat::operator=(const ActionStat& obj) noexcept
{
	if (this == &obj) return *this;

	Action::operator=(obj);
	statName_ = obj.statName_;
	stat_     = obj.stat_;

	return *this;
}

bool ActionStat::operator==(const ActionStat& obj) const noexcept
{
	if (this == &obj) return true;

	return	Action::operator==(obj)    &&
			statName_ == obj.statName_;//&&
			//stat_     == obj.stat_;
}

bool ActionStat::checkForErrors(bool bComprehensive) const
{
	bool bError = Action::checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		if (NovelState::getCurrentlyLoadedState()->getStat(statName_) == nullptr)
		{
			bError = true;
			qCritical() << NovelLib::ErrorType::StatInvalid << "No valid Stat assigned. Was it deleted and not replaced?";
			if (statName_ != "")
				qCritical() << NovelLib::ErrorType::StatMissing << "Stat \"" + statName_ + "\" does not exist. Definition file might be corrupted";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	//if (bError)
	//	qDebug() << "Error occurred in ActionStat::checkForErrors of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();
	return bError;
}

void ActionStat::syncWithSave() noexcept
{
	stat_ = NovelState::getCurrentlyLoadedState()->getStat(statName_);
	if (stat_ == nullptr)
		qCritical() << NovelLib::ErrorType::StatMissing << "Stat \"" + statName_ + "\" does not exist";
}

const Stat* ActionStat::getStat() const noexcept
{
	return stat_;
}

Stat* ActionStat::getStat() noexcept
{ 
	return stat_; 
}

QString ActionStat::getStatName() const noexcept 
{ 
	return statName_; 
}

void ActionStat::setStat(const QString& statName) noexcept
{
	Stat* newStat = nullptr;
	newStat = NovelState::getCurrentlyLoadedState()->getStat(statName);
	if (newStat == nullptr)
		qCritical() << NovelLib::ErrorType::StatMissing << "Stat \"" + statName + "\" does not exist";
	else
	{
		statName_ = statName;
		stat_ = newStat;
		checkForErrors(true);
	}
}

void ActionStat::serializableLoad(QDataStream& dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> statName_;

	//stat_ = NovelState::getCurrentlyLoadedState()->getStat(statName_);
	//if (stat_ == nullptr)
	//	qCritical() << NovelLib::ErrorType::StatMissing << "Stat \"" + statName_ + "\" does not exist. Definition file might be corrupted";
	//checkForErrors();
}

void ActionStat::serializableSave(QDataStream& dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << statName_;
}