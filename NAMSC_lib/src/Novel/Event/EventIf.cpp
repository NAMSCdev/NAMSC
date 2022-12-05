#include "Novel/Event/EventIf.h"

#include "Novel/Data/Scene.h"

EventIf::EventIf(Scene* const parentScene) noexcept
	: Event(parentScene)
{
}

EventIf::EventIf(Scene* const parentScene, const QString& label, const QString& condition, std::vector<std::unique_ptr<Action>>&& actions)
	: Event(parentScene, label, std::move(actions)), condition(condition)
{
	checkForErrors(true);
}

EventIf& EventIf::operator=(const EventIf& obj) noexcept
{
	if (this == &obj) return *this;

	Event::operator=(obj);
	//onRun_    = obj.onRun_;
	condition = obj.condition;

	return *this;
}

bool EventIf::operator==(const EventIf& obj) const noexcept
{
	if (this == &obj) return true;

	return 	Event::operator==(obj)    &&
			condition == obj.condition;
}

bool EventIf::checkForErrors(bool bComprehensive) const
{
	bool bError = Event::checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		//todo check condition
		return false;
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "An Error occurred in EventIf::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << getIndex();

	return bError;
}

void EventIf::run()
{
}

void EventIf::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QString condition)> onRun) noexcept
{
	onRun_ = onRun; 
}

void EventIf::acceptVisitor(EventVisitor* visitor)
{
	visitor->visitEventIf(this);
}

NovelLib::SerializationID EventIf::getType() const noexcept
{ 
	return NovelLib::SerializationID::EventIf;
}

void EventIf::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	dataStream >> condition;
	checkForErrors();
}

void EventIf::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << condition;
}