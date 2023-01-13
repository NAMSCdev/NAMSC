#include "Novel/Action/Stat/ActionStatSetValue.h"

#include "Novel/Data/Scene.h"

ActionStatSetValue::ActionStatSetValue(Event* const parentEvent) noexcept
	: ActionStat(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionStatSetValue& first, ActionStatSetValue& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(dynamic_cast<ActionStat&>(first), dynamic_cast<ActionStat&>(second));
	swap(first.expression, second.expression);
	swap(first.onRun_,     second.onRun_);
}

ActionStatSetValue::ActionStatSetValue(Event* const parentEvent, const QString& statName, const QString& expression, Stat* stat)
	: ActionStat(parentEvent, statName, stat), 
	expression(expression)
{
	errorCheck(true);
}

//deleted
//ActionStatSetValue::ActionStatSetValue(const ActionStatSetValue& obj) noexcept
//	: ActionStat(obj.parentEvent, obj.statName_, obj.stat_), 
//	expression(obj.expression), 
//	onRun_(obj.onRun_)
//{
//}

//deleted
//bool ActionStatSetValue::operator==(const ActionStatSetValue& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return ActionStat::operator==(obj)  &&
//		   expression == obj.expression;
//}

void ActionStatSetValue::setOnRunListener(std::function<void(const Event* const parentEvent, const Stat* const stat, const QString& expression)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionStatSetValue::serializableLoad(QDataStream& dataStream)
{
	ActionStat::serializableLoad(dataStream);
	dataStream >> expression;
	errorCheck();
}

void ActionStatSetValue::serializableSave(QDataStream& dataStream) const
{
	ActionStat::serializableSave(dataStream);
	dataStream << expression;
}

//  MEMBER_FIELD_SECTION_CHANGE END

ActionStatSetValue::ActionStatSetValue(ActionStatSetValue&& obj) noexcept
	: ActionStat(obj.parentEvent)
{
	swap(*this, obj);
}

//deleted
//ActionStatSetValue& ActionStatSetValue::operator=(ActionStatSetValue obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

void ActionStatSetValue::acceptVisitor(ActionVisitor* visitor)
{
	visitor->visitActionStatSetValue(this);
}

NovelLib::SerializationID ActionStatSetValue::getType() const noexcept
{
	return NovelLib::SerializationID::ActionStatSetValue;
}