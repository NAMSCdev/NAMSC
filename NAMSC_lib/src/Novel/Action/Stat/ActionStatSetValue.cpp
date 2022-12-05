#include "Novel/Action/Stat/ActionStatSetValue.h"

#include "Novel/Data/Scene.h"

ActionStatSetValue::ActionStatSetValue(Event* const parentEvent, Scene* const parentScene) noexcept
	: ActionStat(parentEvent, parentScene)
{
}

ActionStatSetValue::ActionStatSetValue(Event* const parentEvent, Scene* const parentScene, const QString& statName, const QString& expression)
	: ActionStat(parentEvent, parentScene, statName), expression(expression)
{
	checkForErrors(true);
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
		qDebug() << "Error occurred in ActionStatSetValue::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}

void ActionStatSetValue::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, Stat* stat, QString expression)> onRun) noexcept
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