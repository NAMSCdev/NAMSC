#include "pvnLib/Novel/Event/EventDialogue.h"

#include "pvnLib/Novel/Data/Scene.h"
#include "pvnLib/Helpers.h"

EventDialogue::EventDialogue(Scene* const parentScene) noexcept
	: Event(parentScene)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(EventDialogue& first, EventDialogue& second) noexcept
{
	using std::swap;
	swap(static_cast<Event&>(first), static_cast<Event&>(second));
	swap(first.sentences_, second.sentences_);
	swap(first.onRun_,     second.onRun_);
}

EventDialogue::EventDialogue(Scene* const parentScene, const QString& label, const std::vector<Sentence>& sentences)
	: Event(parentScene, label), 
	sentences_(sentences)
{
	errorCheck(true);
}

EventDialogue::EventDialogue(const EventDialogue& obj) noexcept
	: Event(obj.parentScene, obj.label, obj.actions_),
	onRun_(obj.onRun_)
{
	for (const Sentence& sentence : obj.sentences_)
	{
		sentences_.emplace_back(this);
		sentences_.back() = sentence;
	}
}


EventDialogue& EventDialogue::operator=(const EventDialogue& obj) noexcept
{
	if (this == &obj) return *this;

	label  = obj.label;
	onRun_ = obj.onRun_;

	for (const Sentence& sentence : obj.sentences_)
	{
		sentences_.emplace_back(this);
		sentences_.back() = sentence;
	}

	return *this;
}

bool EventDialogue::operator==(const EventDialogue& obj) const noexcept
{
	if (this == &obj)
		return true;
	
	return actions_   == obj.actions_   && 
		   sentences_ == obj.sentences_;
}

void EventDialogue::setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const std::vector<Sentence>* const sentences)> onRun) noexcept
{ 
	onRun_ = onRun; 
}

void EventDialogue::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	uint sentences_Size;
	dataStream >> sentences_Size;
	for (uint i = 0u; i != sentences_Size; ++i)
	{
		Sentence sentence(this);
		dataStream >> sentence;
		sentences_.push_back(std::move(sentence));
	}

	errorCheck();
}

void EventDialogue::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << static_cast<uint>(sentences_.size());

	for (const Sentence& sentence : sentences_)
		dataStream << sentence;
}

//  MEMBER_FIELD_SECTION_CHANGE END

EventDialogue::EventDialogue(EventDialogue&& obj) noexcept
	: Event(obj.parentScene)
{
	swap(*this, obj);
}

const std::vector<Sentence>* EventDialogue::getSentences() const noexcept
{
	return &sentences_;
}

const Sentence* EventDialogue::getSentence(uint index) const
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(sentences_, index, "Sentence", NovelLib::ErrorType::SentenceMissing, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

Sentence* EventDialogue::getSentence(uint index)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listGet(sentences_, index, "Sentence", NovelLib::ErrorType::SentenceMissing, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

const std::vector<Sentence>* EventDialogue::setSentences(const std::vector<Sentence>& sentences) noexcept
{
	return &(sentences_ = sentences);
}

const std::vector<Sentence>* EventDialogue::setSentences(std::vector<Sentence>&& sentences) noexcept
{
	return &(sentences_ = std::move(sentences));
}

Sentence* EventDialogue::addSentence(const Sentence& sentence)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listAdd(sentences_, sentence, "Sentence", NovelLib::ErrorType::SentenceInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

Sentence* EventDialogue::addSentence(Sentence&& sentence)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listAdd(sentences_, std::move(sentence), "Sentence", NovelLib::ErrorType::SentenceInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

Sentence* EventDialogue::insertSentence(uint index, const Sentence& sentence)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listInsert(sentences_, index, sentence, "Sentence", NovelLib::ErrorType::SentenceInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

Sentence* EventDialogue::insertSentence(uint index, Sentence&& sentence)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listInsert(sentences_, index, std::move(sentence), "Sentence", NovelLib::ErrorType::SentenceInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

Sentence* EventDialogue::reinsertSentence(uint index, uint newIndex)
{
	return NovelLib::Helpers::itToPtr(NovelLib::Helpers::listReinsert(sentences_, index, newIndex, "Sentence", NovelLib::ErrorType::SentenceMissing, NovelLib::ErrorType::SentenceInvalid, "Event", QString::number(getIndex()), "Scene", parentScene->name));
}

bool EventDialogue::removeSentence(uint index)
{
	return NovelLib::Helpers::listRemove(sentences_, index, "Sentence", NovelLib::ErrorType::SentenceMissing, "Event", QString::number(getIndex()), "Scene", parentScene->name);
}

void EventDialogue::clearSentences() noexcept
{
	sentences_.clear();
}

void EventDialogue::acceptVisitor(EventVisitor* visitor)
{ 
	visitor->visitEventDialogue(this); 
}

NovelLib::SerializationID EventDialogue::getType() const noexcept
{ 
	return NovelLib::SerializationID::EventDialogue; 
}