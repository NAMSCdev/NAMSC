#include "Novel/Event/EventWait.h"

#include "Novel/Data/Scene.h"

EventWait::EventWait(Scene* const parentScene) noexcept
	: Event(parentScene)
{
}

EventWait::EventWait(Scene* const parentScene, const QString& label, uint waitTime)
	: Event(parentScene, label), waitTime(waitTime)
{
	checkForErrors(true);
}

EventWait::EventWait(Scene* const parentScene, const QString& label, uint waitTime, std::vector<std::unique_ptr<Action>>&& actions)
	: Event(parentScene, label, std::move(actions)), waitTime(waitTime)
{
	checkForErrors(true);
}

EventWait& EventWait::operator=(const EventWait& obj) noexcept
{
	if (this == &obj) return *this;

	Event::operator=(obj);
	//onRun_   = obj.onRun_;
	waitTime = obj.waitTime;

	return *this;
}

bool EventWait::operator==(const EventWait& obj) const noexcept
{
	if (this == &obj) return true;

	return 	Event::operator==(obj)  &&
			waitTime == obj.waitTime;
}

bool EventWait::checkForErrors(bool bComprehensive) const
{
	bool bError = Event::checkForErrors(bComprehensive);

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	//if (bError)
	//	qDebug() << "An Error occurred in EventWait::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << getIndex();

	return bError;
}

void EventWait::run()
{
}

void EventWait::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, uint waitTime)> onRun) noexcept
{ 
	onRun_ = onRun; 
}

void EventWait::acceptVisitor(EventVisitor* visitor)
{ 
	visitor->visitEventWait(this);
}

NovelLib::SerializationID EventWait::getType() const noexcept 
{ 
	return NovelLib::SerializationID::EventWait; 
}

void EventWait::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	dataStream >> waitTime;
	checkForErrors();
}

void EventWait::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << waitTime;
}