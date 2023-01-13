#include "Novel/Event/EventEndIf.h"

#include "Novel/Data/Scene.h"
#include "Novel/Event/EventIf.h"

EventEndIf::EventEndIf(Scene* const parentScene) noexcept
	: Event(parentScene)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(EventEndIf& first, EventEndIf& second) noexcept
{
	using std::swap;
	swap(static_cast<Event&>(first), static_cast<Event&>(second));
	swap(first.partner_, second.partner_);
	swap(first.onRun_,   second.onRun_);
}

EventEndIf::EventEndIf(Scene* const parentScene, const QString& label, EventIf* const partner, std::vector<std::unique_ptr<Action>>&& actions)
	: Event(parentScene, label, std::move(actions)),
	partner_(partner)
{
	errorCheck(true);
}

void EventEndIf::setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const EventIf* const partner)> onRun) noexcept
{ 
	onRun_ = onRun;
}

void EventEndIf::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	uint index;
	dataStream >> index;
	partner_ = dynamic_cast<EventIf*>(parentScene->getEvent(index));
	errorCheck();
}

void EventEndIf::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << partner_->getIndex();
}

//  MEMBER_FIELD_SECTION_CHANGE END

EventEndIf::EventEndIf(EventEndIf&& obj) noexcept
	: Event(obj.parentScene)
{
	swap(*this, obj);
}

void EventEndIf::acceptVisitor(EventVisitor* visitor) 
{ 
	visitor->visitEventEndIf(this);
}

NovelLib::SerializationID EventEndIf::getType() const noexcept 
{ 
	return NovelLib::SerializationID::EventEndIf; 
}