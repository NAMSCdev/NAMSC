#include "Novel/Event/EventChoice.h"

#include "Novel/Data/Scene.h"

EventChoice::EventChoice(Scene* const parentScene) noexcept
	: Event(parentScene)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(EventChoice& first, EventChoice& second) noexcept
{
	using std::swap;
	swap(static_cast<Event&>(first), static_cast<Event&>(second));
	swap(first.menuText_, second.menuText_);
	swap(first.choices,   second.choices);
	swap(first.onRun_,    second.onRun_);
}

EventChoice::EventChoice(Scene* const parentScene, const QString& label, const Translation& menuText, const std::vector<Choice>& choices, std::vector<std::unique_ptr<Action>>&& actions)
	: Event(parentScene, label, std::move(actions)),
	menuText_(menuText),
	choices(choices)
{
	errorCheck(true);
}

void EventChoice::setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const Translation* const text, const std::vector<Choice>* const choices)> onRun) noexcept
{
	onRun_ = onRun;
}

void EventChoice::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	uint choicesSize = 0;
	dataStream >> choicesSize;

	for (unsigned i = 0; i != choicesSize; ++i)
	{
		Choice choice(this);
		dataStream >> choice;
		choices.push_back(std::move(choice));
	}

	errorCheck();
}

void EventChoice::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << choices.size();

	for (const Choice& choice : choices)
		dataStream << choice;
}

//  MEMBER_FIELD_SECTION_CHANGE END

EventChoice::EventChoice(EventChoice&& obj) noexcept
	: EventChoice(obj.parentScene)
{
	swap(*this, obj);
}

const Translation* EventChoice::getMenuText() const noexcept
{
	return &menuText_;
}

Translation* EventChoice::getMenuText() noexcept
{
	return &menuText_;
}

void EventChoice::setMenuText(const Translation& menuText) noexcept
{
	menuText_ = menuText;
}

void EventChoice::acceptVisitor(EventVisitor* visitor)
{ 
	visitor->visitEventChoice(this);
}

NovelLib::SerializationID EventChoice::getType() const noexcept 
{ 
	return NovelLib::SerializationID::EventChoice; 
}