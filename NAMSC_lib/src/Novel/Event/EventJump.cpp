#include "Novel/Event/EventJump.h"

#include "Novel/Data/Scene.h"

EventJump::EventJump(Scene* const parentScene) noexcept
	: Event(parentScene)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(EventJump& first, EventJump& second) noexcept
{
	using std::swap;
	swap(static_cast<Event&>(first), static_cast<Event&>(second));
	swap(first.jumpToSceneName, second.jumpToSceneName);
	swap(first.condition,       second.condition);
	swap(first.onRun_,          second.onRun_);
}

EventJump::EventJump(Scene* const parentScene, const QString& label, const QString& jumpToSceneName, const QString& condition)
	: Event(parentScene, label),
	jumpToSceneName(jumpToSceneName),
	condition(condition)
{
	errorCheck(true);
}

EventJump::EventJump(const EventJump& obj) noexcept
	: Event(obj.parentScene, obj.label, obj.actions_),
	jumpToSceneName(obj.jumpToSceneName),
	condition(obj.condition),
	onRun_(obj.onRun_)
{
}

bool EventJump::operator==(const EventJump& obj) const noexcept
{
	if (this == &obj)
		return true;

	return actions_        == obj.actions_        &&
		   jumpToSceneName == obj.jumpToSceneName &&
		   condition       == obj.condition;
}

void EventJump::setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const QString& jumpToSceneName, const QString& condition)> onRun) noexcept
{ 
	onRun_ = onRun; 
}

void EventJump::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	dataStream >> jumpToSceneName >> condition;

	errorCheck();
}

void EventJump::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << jumpToSceneName << condition;
}

//  MEMBER_FIELD_SECTION_CHANGE END

EventJump::EventJump(EventJump&& obj) noexcept
	: Event(obj.parentScene)
{
	swap(*this, obj);
}

EventJump& EventJump::operator=(EventJump obj) noexcept
{
	if (this == &obj) return *this;

	swap(*this, obj);

	return *this;
}

void EventJump::acceptVisitor(EventVisitor* visitor) 
{
	visitor->visitEventJump(this);
}

NovelLib::SerializationID EventJump::getType() const noexcept 
{ 
	return NovelLib::SerializationID::EventJump; 
}