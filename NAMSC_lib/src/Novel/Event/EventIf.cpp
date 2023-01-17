#include "Novel/Event/EventIf.h"

#include "Novel/Data/Scene.h"

EventIf::EventIf(Scene* const parentScene) noexcept
	: Event(parentScene)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(EventIf& first, EventIf& second) noexcept
{
	using std::swap;
	swap(static_cast<Event&>(first), static_cast<Event&>(second));
	swap(first.condition, second.condition);
	swap(first.onRun_,    second.onRun_);
}

EventIf::EventIf(Scene* const parentScene, const QString& label, const QString& condition)
	: Event(parentScene, label),
	condition(condition)
{
	errorCheck(true);
}

void EventIf::setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const QString& condition)> onRun) noexcept
{
	onRun_ = onRun; 
}

void EventIf::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	dataStream >> condition;

	errorCheck();
}

void EventIf::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << condition;
}

//  MEMBER_FIELD_SECTION_CHANGE END

EventIf::EventIf(EventIf&& obj) noexcept
	: Event(obj.parentScene)
{
	swap(*this, obj);
}

void EventIf::acceptVisitor(EventVisitor* visitor)
{
	visitor->visitEventIf(this);
}

NovelLib::SerializationID EventIf::getType() const noexcept
{ 
	return NovelLib::SerializationID::EventIf;
}