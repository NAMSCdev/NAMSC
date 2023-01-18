#include "Novel/Event/EventDialogue.h"

#include "Novel/Data/Scene.h"

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
}

EventDialogue::EventDialogue(Scene* const parentScene, const QString& label, const std::vector<Sentence>& sentences)
	: Event(parentScene, label), 
	sentences(sentences)
{
	errorCheck(true);
}

void EventDialogue::setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const std::vector<Sentence>* const sentences)> onRun) noexcept
{ 
	onRun_ = onRun; 
}

void EventDialogue::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	uint sentencesSize;
	dataStream >> sentencesSize;
	for (uint i = 0u; i != sentencesSize; ++i)
	{
		Sentence sentence(this);
		dataStream >> sentence;
		sentences.push_back(std::move(sentence));
	}

	errorCheck();
}

void EventDialogue::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << static_cast<uint>(sentences.size());

	for (const Sentence& sentence : sentences)
		dataStream << sentence;
}

//  MEMBER_FIELD_SECTION_CHANGE END

EventDialogue::EventDialogue(EventDialogue&& obj) noexcept
	: Event(obj.parentScene)
{
	swap(*this, obj);
}

void EventDialogue::acceptVisitor(EventVisitor* visitor)
{ 
	visitor->visitEventDialogue(this); 
}

NovelLib::SerializationID EventDialogue::getType() const noexcept
{ 
	return NovelLib::SerializationID::EventDialogue; 
}