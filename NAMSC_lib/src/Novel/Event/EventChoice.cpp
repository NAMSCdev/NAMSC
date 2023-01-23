#include "Novel/Event/EventChoice.h"

#include "Novel/Data/Scene.h"
#include "Helpers.h"

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
	swap(first.choices_,  second.choices_);
	swap(first.onRun_,    second.onRun_);
}

EventChoice::EventChoice(Scene* const parentScene, const QString& label, const Translation& menuText)
	: Event(parentScene, label),
	menuText_(menuText)
{
	errorCheck(true);
}

EventChoice::EventChoice(const EventChoice& obj) noexcept
	: Event(obj.parentScene, obj.label, obj.actions_),
	menuText_(obj.menuText_),
	choices_(obj.choices_),
	onRun_(obj.onRun_)
{
	for (const Choice& choice : obj.choices_)
	{
		choices_.emplace_back(this);
		choices_.back() = choice;
	}
}

EventChoice& EventChoice::operator=(const EventChoice& obj) noexcept
{
	if (this == &obj) return *this;

	label     = obj.label;
	onRun_    = obj.onRun_;
	menuText_ = obj.menuText_;

	for (const Choice& choice : obj.choices_)
	{
		choices_.emplace_back(this);
		choices_.back() = choice;
	}

	return *this;
}

bool EventChoice::operator==(const EventChoice& obj) const noexcept
{
	if (this == &obj)
		return true;

	return actions_  == obj.actions_  &&
		   menuText_ == obj.menuText_ &&
		   choices_  == obj.choices_;
}

void EventChoice::setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const Translation* const translation, const std::vector<Choice>* const choices)> onRun) noexcept
{
	onRun_ = onRun;
}

void EventChoice::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	uint choicesSize;
	dataStream >> menuText_ >> choicesSize;
	for (size_t i = 0u; i != choicesSize; ++i)
	{
		Choice choice(this);
		dataStream >> choice;
		choices_.push_back(std::move(choice));
	}

	errorCheck();
}

void EventChoice::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);

	dataStream << menuText_ << static_cast<uint>(choices_.size());
	for (const Choice& choice : choices_)
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

const std::vector<Choice>* EventChoice::getChoices() const noexcept
{
	return &choices_;
}

const Choice* EventChoice::getChoice(uint index) const
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(choices_, index, "Choice", NovelLib::ErrorType::ChoiceMissing, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

Choice* EventChoice::getChoice(uint index)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(choices_, index, "Choice", NovelLib::ErrorType::ChoiceMissing, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

const std::vector<Choice>* EventChoice::setChoices(const std::vector<Choice>& choices) noexcept
{
	return &(choices_ = choices);
}

const std::vector<Choice>* EventChoice::setChoices(std::vector<Choice>&& choices) noexcept
{
	return &(choices = std::move(choices));
}

Choice* EventChoice::addChoice(const Choice& choice)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listAdd(choices_, choice, "Choice", NovelLib::ErrorType::ChoiceInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

Choice* EventChoice::addChoice(Choice&& choice)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listAdd(choices_, std::move(choice), "Choice", NovelLib::ErrorType::ChoiceInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

Choice* EventChoice::insertChoice(uint index, const Choice& choice)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listInsert(choices_, index, choice, "Choice", NovelLib::ErrorType::ChoiceInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

Choice* EventChoice::insertChoice(uint index, Choice&& choice)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listInsert(choices_, index, std::move(choice), "Choice", NovelLib::ErrorType::ChoiceInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

Choice* EventChoice::reinsertChoice(uint index, uint newIndex)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listReinsert(choices_, index, newIndex, "Choice", NovelLib::ErrorType::ChoiceMissing, NovelLib::ErrorType::ChoiceInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

bool EventChoice::removeChoice(uint index)
{
	return NovelLib::Helpers::listRemove(choices_, index, "Choice", NovelLib::ErrorType::ChoiceMissing, "Event", QString::number(getIndex()), "Scene", parentScene->name);
}

void EventChoice::clearChoices() noexcept
{
	choices_.clear();
}

void EventChoice::acceptVisitor(EventVisitor* visitor)
{ 
	visitor->visitEventChoice(this);
}

NovelLib::SerializationID EventChoice::getType() const noexcept 
{ 
	return NovelLib::SerializationID::EventChoice; 
}