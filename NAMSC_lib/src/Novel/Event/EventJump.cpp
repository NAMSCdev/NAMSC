#include "Novel/Event/EventJump.h"

#include "Novel/Data/Scene.h"

EventJump::EventJump(Scene* const parentScene) noexcept
	: Event(parentScene)
{
}

EventJump::EventJump(Scene* const parentScene, const QString& label, const QString& jumpToSceneName, const QString& condition)
	: Event(parentScene, label), jumpToSceneName(jumpToSceneName), condition(condition)
{
	checkForErrors(true);
}

EventJump::EventJump(Scene* const parentScene, const QString& label, const QString& jumpToSceneName, const QString& condition, std::vector<std::unique_ptr<Action>>&& actions)
	: Event(parentScene, label, std::move(actions)), jumpToSceneName(jumpToSceneName), condition(condition)
{
	checkForErrors(true);
}

EventJump& EventJump::operator=(const EventJump& obj) noexcept
{
	if (this == &obj) return *this;

	Event::operator=(obj);
	//onRun_          = obj.onRun_;
	jumpToSceneName = obj.jumpToSceneName;
	condition       = obj.condition;

	return *this;
}

bool EventJump::operator==(const EventJump& obj) const noexcept
{
	if (this == &obj) return true;

	return 	Event::operator==(obj)         &&
			jumpToSceneName == obj.jumpToSceneName &&
			condition   == obj.condition;
}

bool EventJump::checkForErrors(bool bComprehensive) const
{
	bool bError = Event::checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		if (jumpToSceneName == "")
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::JumpInvalid << "EventJump is missing a jumpToSceneName";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "An Error occurred in EventJump::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << getIndex();

	return bError;
}

void EventJump::run()
{
}

void EventJump::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QString jumpToSceneName, QString condition)> onRun) noexcept
{ 
	onRun_ = onRun; 
}

void EventJump::acceptVisitor(EventVisitor* visitor) 
{
	visitor->visitEventJump(this);
}

NovelLib::SerializationID EventJump::getType() const noexcept 
{ 
	return NovelLib::SerializationID::EventJump; 
}

void EventJump::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	dataStream >> jumpToSceneName >> condition;
	checkForErrors();
}

void EventJump::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << jumpToSceneName << condition;
}