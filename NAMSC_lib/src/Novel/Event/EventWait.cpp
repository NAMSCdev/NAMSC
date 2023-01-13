#include "Novel/Event/EventWait.h"

#include "Novel/Data/Scene.h"

EventWait::EventWait(Scene* const parentScene) noexcept
	: Event(parentScene)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(EventWait& first, EventWait& second) noexcept
{
	using std::swap;
	swap(static_cast<Event&>(first), static_cast<Event&>(second));
	swap(first.waitTime, second.waitTime);
	swap(first.onRun_,   second.onRun_);
}

EventWait::EventWait(Scene* const parentScene, const QString& label, uint waitTime, std::vector<std::unique_ptr<Action>>&& actions)
	: Event(parentScene, label, std::move(actions)), 
	waitTime(waitTime)
{
	errorCheck(true);
}

void EventWait::setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const uint& waitTime)> onRun) noexcept
{ 
	onRun_ = onRun; 
}

void EventWait::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	dataStream >> waitTime;
	errorCheck();
}

void EventWait::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << waitTime;
}

//  MEMBER_FIELD_SECTION_CHANGE END

EventWait::EventWait(EventWait&& obj) noexcept
	: Event(obj.parentScene)
{
	swap(*this, obj);
}

void EventWait::acceptVisitor(EventVisitor* visitor)
{ 
	visitor->visitEventWait(this);
}

NovelLib::SerializationID EventWait::getType() const noexcept 
{ 
	return NovelLib::SerializationID::EventWait; 
}