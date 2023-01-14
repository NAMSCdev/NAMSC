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

EventJump::EventJump(Scene* const parentScene, const QString& label, const QString& jumpToSceneName, const QString& condition, std::vector<std::unique_ptr<Action>>&& actions)
	: Event(parentScene, label, std::move(actions)),
	jumpToSceneName(jumpToSceneName),
	condition(condition)
{
	errorCheck(true);
}

EventJump::EventJump(EventJump&& obj) noexcept
	: Event(obj.parentScene)
{
	swap(*this, obj);
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

void EventJump::acceptVisitor(EventVisitor* visitor) 
{
	visitor->visitEventJump(this);
}

NovelLib::SerializationID EventJump::getType() const noexcept 
{ 
	return NovelLib::SerializationID::EventJump; 
}