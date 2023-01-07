#include "Novel/Action/Stat/ActionStatSetValue.h"

#include "Novel/Data/Scene.h"

ActionStatSetValue::ActionStatSetValue(Event* const parentEvent) noexcept
	: ActionStat(parentEvent)
{
}

ActionStatSetValue::ActionStatSetValue(Event* const parentEvent, const QString& statName, const QString& expression)
	: ActionStat(parentEvent, statName), expression(expression)
{
	checkForErrors(true);
}

ActionStatSetValue::ActionStatSetValue(const ActionStatSetValue& obj) noexcept
	: ActionStat(obj.parentEvent)
{
	//TODO: change to swap trick for more efficency
	*this = obj;
}

ActionStatSetValue& ActionStatSetValue::operator=(const ActionStatSetValue& obj) noexcept
{
	if (this == &obj) return *this;

	ActionStat::operator=(obj);
	//onRun_     = obj.onRun_;
	expression = obj.expression;

	return *this;
}

bool ActionStatSetValue::operator==(const ActionStatSetValue& obj) const noexcept
{
	if (this == &obj) return true;

	return	ActionStat::operator==(obj) &&
			expression == obj.expression;
}

bool ActionStatSetValue::checkForErrors(bool bComprehensive) const
{
	bool bError = ActionStat::checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		//TODO: check `expression` by trying to parse it with an evaluator
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionStatSetValue::checkForErrors of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

Action* ActionStatSetValue::clone() const
{
	ActionStatSetValue* clone = new ActionStatSetValue(*this);
	return clone;
}

void ActionStatSetValue::setOnRunListener(std::function<void(Event* const parentEvent, Stat* stat, QString expression)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionStatSetValue::acceptVisitor(ActionVisitor* visitor)
{
	visitor->visitActionStatSetValue(this);
}

NovelLib::SerializationID ActionStatSetValue::getType() const noexcept
{
	return NovelLib::SerializationID::ActionStatSetValue;
}

void ActionStatSetValue::serializableLoad(QDataStream& dataStream)
{
	ActionStat::serializableLoad(dataStream);
	dataStream >> expression;
	checkForErrors();
}

void ActionStatSetValue::serializableSave(QDataStream& dataStream) const
{
	ActionStat::serializableSave(dataStream);
	dataStream << expression;
}