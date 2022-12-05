#include "Novel/Event/EventChoice.h"

#include "Novel/Data/Scene.h"

EventChoice::EventChoice(Scene* const parentScene) noexcept
	: Event(parentScene)
{
}

EventChoice::EventChoice(Scene* const parentScene, const QString label, const Translation& menuText, const std::vector<Choice>& choices)
	: Event(parentScene, label), menuText_(menuText), choices(choices)
{
	checkForErrors(true);
}

EventChoice::EventChoice(Scene* const parentScene, const QString label, const Translation& menuText, const std::vector<Choice>& choices, std::vector<std::unique_ptr<Action>>&& actions)
	: Event(parentScene, label, std::move(actions)), menuText_(menuText), choices(choices)
{
	checkForErrors(true);
}

EventChoice& EventChoice::operator=(const EventChoice& obj) noexcept
{
	if (this == &obj) return *this;

	Event::operator=(obj);
	//onRun_    = obj.onRun_;
	menuText_ = obj.menuText_;
	choices   = obj.choices;

	return *this;
}

bool EventChoice::operator==(const EventChoice& obj) const noexcept
{
	if (this == &obj) return true;

	return 	Event::operator==(obj)     &&
			menuText_ == obj.menuText_ &&
			choices   == obj.choices;
}

bool EventChoice::checkForErrors(bool bComprehensive) const
{
	bool bError = Event::checkForErrors(bComprehensive);

	for (const Choice& choice : choices)
		bError |= choice.checkForErrors(bComprehensive);

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in EventChoice::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << getIndex();

	return bError;
}

void EventChoice::run()
{
}

void EventChoice::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, Translation* text, std::vector<Choice>* choices)> onRun) noexcept
{ 
	onRun_ = onRun; 
}

void EventChoice::setMenuText(const Translation& menuText) noexcept
{ 
	menuText_ = menuText; 
}

Translation* EventChoice::getMenuText() noexcept
{
	return &menuText_;
}

const Translation* EventChoice::getMenuText() const noexcept
{ 
	return &menuText_; 
}

void EventChoice::acceptVisitor(EventVisitor* visitor)
{ 
	visitor->visitEventChoice(this);
}

NovelLib::SerializationID EventChoice::getType() const noexcept 
{ 
	return NovelLib::SerializationID::EventChoice; 
}

void EventChoice::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);

	dataStream >> menuText_;

	uint choicesSize;
	dataStream >> choicesSize;
	for (uint i = 0u; i != choicesSize; ++i)
	{
		Choice choice;
		dataStream >> choice;
		choices.push_back(std::move(choice));
	}
	checkForErrors();
}

void EventChoice::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);

	dataStream << menuText_ << choices.size();
	for (const Choice& choice : choices)
		dataStream << choice;
}