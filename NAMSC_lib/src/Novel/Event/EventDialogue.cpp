#include "Novel/Event/EventDialogue.h"

#include "Novel/Data/Scene.h"

EventDialogue::EventDialogue(Scene* const parentScene) noexcept
	: Event(parentScene)
{
}

EventDialogue::EventDialogue(Scene* const parentScene, const QString& label, const std::vector<Sentence>& sentences)
	: Event(parentScene, label), sentences(sentences)
{
	checkForErrors(true);
}

EventDialogue::EventDialogue(Scene* const parentScene, const QString& label, const std::vector<Sentence>& sentences, std::vector<std::unique_ptr<Action>>&& actions)
	: Event(parentScene, label, std::move(actions)), sentences(sentences)
{
	checkForErrors(true);
}

EventDialogue& EventDialogue::operator=(const EventDialogue& obj) noexcept
{
	if (this == &obj) return *this;

	Event::operator=(obj);
	onRun_    = obj.onRun_;
	sentences = obj.sentences;

	return *this;
}

bool EventDialogue::operator==(const EventDialogue& obj) const noexcept
{
	if (this == &obj) return true;

	return 	Event::operator==(obj) &&
			sentences == obj.sentences;
}

bool EventDialogue::checkForErrors(bool bComprehensive) const
{
	bool bError = Event::checkForErrors(bComprehensive);

	for (const Sentence& sentence : sentences)
		bError |= sentence.checkForErrors(bComprehensive);

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	 if (bError)
		qDebug() << "An Error occurred in EventDialogue::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << getIndex();

	return bError;
}

void EventDialogue::run()
{
}

void EventDialogue::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, std::vector<Sentence>* sentences)> onRun) noexcept
{ 
	onRun_ = onRun; 
}

void EventDialogue::acceptVisitor(EventVisitor* visitor)
{ 
	visitor->visitEventDialogue(this); 
}

NovelLib::SerializationID EventDialogue::getType() const noexcept
{ 
	return NovelLib::SerializationID::EventDialogue; 
}

void EventDialogue::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	uint sentencesSize = 0;
	dataStream >> sentencesSize;

	for (unsigned i = 0; i != sentencesSize; ++i)
	{
		Sentence sentence(this, parentScene_);
		dataStream >> sentence;
		sentences.push_back(std::move(sentence));
	}

	checkForErrors();
}

void EventDialogue::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << sentences.size();

	for (const Sentence& sentence: sentences)
		dataStream << sentence;
}