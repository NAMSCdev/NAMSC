#include "pvnLib/Novel/Event/EventEndIf.h"

#include "pvnLib/Novel/Data/Scene.h"
#include "pvnLib/Novel/Event/EventIf.h"

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

EventEndIf::EventEndIf(Scene* const parentScene, const QString& label, EventIf* const partner)
	: Event(parentScene, label),
	partner_(partner)
{
	errorCheck(true);
}

EventEndIf::EventEndIf(const EventEndIf& obj) noexcept
	: Event(obj.parentScene, obj.label, obj.actions_),
	partner_(obj.partner_)
{
}

bool EventEndIf::operator==(const EventEndIf& obj) const noexcept
{
	if (this == &obj)
		return true;

	return actions_ == obj.actions_ && 
		   partner_ == obj.partner_;
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
	//partner_ = dynamic_cast<EventIf*>(parentScene->getEvent(index));

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

EventEndIf& EventEndIf::operator=(EventEndIf obj) noexcept
{
	if (this == &obj) return *this;

	std::swap(*this, obj);

	return *this;
}

void EventEndIf::acceptVisitor(EventVisitor* visitor) 
{ 
	visitor->visitEventEndIf(this);
}

NovelLib::SerializationID EventEndIf::getType() const noexcept 
{ 
	return NovelLib::SerializationID::EventEndIf; 
}