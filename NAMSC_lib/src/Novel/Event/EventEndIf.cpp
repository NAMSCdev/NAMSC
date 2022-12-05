#include "Novel/Event/EventEndIf.h"

#include "Novel/Data/Scene.h"

EventEndIf::EventEndIf(Scene* const parentScene) noexcept
	: Event(parentScene)
{
}

EventEndIf::EventEndIf(Scene* const parentScene, const QString& label, Event* const partner, std::vector<std::unique_ptr<Action>>&& actions)
	: Event(parentScene, label, std::move(actions)), partner_(partner)
{
	checkForErrors(true);
}

EventEndIf& EventEndIf::operator=(const EventEndIf& obj) noexcept
{
	if (this == &obj) return *this;

	Event::operator=(obj);
	//onRun_   = obj.onRun_;
	partner_ = obj.partner_;

	return *this;
}

bool EventEndIf::operator==(const EventEndIf& obj) const noexcept
{
	if (this == &obj) return true;

	return 	Event::operator==(obj)  &&
			partner_ == obj.partner_;
}

bool EventEndIf::checkForErrors(bool bComprehensive) const
{
	bool bError = Event::checkForErrors(bComprehensive);
	
	static auto errorChecker = [&](bool bComprehensive)
	{
		if (getIndex() <= partner_->getIndex())
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::General << "EventEndIf (" << getIndex() << ") has not a greater index that its partner EventIf (" << partner_->getIndex() << ')';
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in EventEndIf::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << getIndex();

	return bError;
}

void EventEndIf::run()
{
}

void EventEndIf::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, Event* partner)> onRun) noexcept
{ 
	onRun_ = onRun;
}

void EventEndIf::acceptVisitor(EventVisitor* visitor) 
{ 
	visitor->visitEventEndIf(this);
}

NovelLib::SerializationID EventEndIf::getType() const noexcept 
{ 
	return NovelLib::SerializationID::EventEndIf; 
}

void EventEndIf::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	uint index;
	dataStream >> index;
	partner_ = parentScene_->getEvent(index);
	checkForErrors();
}

void EventEndIf::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << partner_->getIndex();
}
