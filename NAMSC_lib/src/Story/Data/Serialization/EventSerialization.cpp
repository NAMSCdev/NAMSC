#pragma once
#include "Story/Event/EventsAll.h"
#include "Story/Data/Story.h"

void Event::serializableLoad(QDataStream& dataStream)
{

	dataStream >> label >> executionOrder;
	unsigned actionsSize;
	dataStream >> actionsSize;
	for (unsigned i = 0u; i != actionsSize; ++i)
	{
		SerializationID type;
		dataStream >> type;

		Action* action;
		switch (type)
		{
		default:
			dddd;
			break;
		}
		actions.emplace_back(action);
	}
}

void Event::serializableSave(QDataStream& dataStream) const
{
	dataStream << getType() << label << executionOrder;
	for (const uPtr<Action>& action : actions)
		action->serializableSave(dataStream);
}

void EventChoice::Choice::ChoiceDisplayOptions::serializableLoad(QDataStream& dataStream)
{
	dataStream >> fontName >> fontSize >> bHideIfConditionNotMet;
}
void EventChoice::Choice::ChoiceDisplayOptions::serializableSave(QDataStream& dataStream) const
{
	dataStream << fontName << fontSize << bHideIfConditionNotMet;
}

void EventChoice::Choice::serializableLoad(QDataStream& dataStream)
{

	dataStream >> label >> text >> condition >> jump >> choiceDisplayOptions;
}

void EventChoice::Choice::serializableSave(QDataStream& dataStream) const
{

	dataStream << label << text << condition << jump << choiceDisplayOptions;
}

void EventChoice::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);

	dataStream >> text;

	unsigned choicesSize;
	dataStream >> choicesSize;
	for (unsigned i = 0u; i != choicesSize; ++i)
	{
		Choice choice;
		dataStream >> choice;
		choices.push_back(move(choice));
	}
}

void EventChoice::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);

	dataStream << text << choices.size();
	for (const Choice& choice : choices)
		dataStream << choice;
}

void EventEndIf::serializableLoad(QDataStream& dataStream) 
{
	Event::serializableLoad(dataStream);
}

void EventEndIf::serializableSave(QDataStream& dataStream) const 
{
	Event::serializableSave(dataStream);
}

void EventIf::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);

	dataStream >> condition;
}

void EventIf::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);

	dataStream << condition;
}

void EventInput::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);

	dataStream >> inputStat >> bDigitsOnly >> min >> max >> minCharacters >> bStatRelated >> logicalExpression >> successJump >> failureJump >> tries;
}

void EventInput::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);

	dataStream << inputStat << bDigitsOnly << min << max << minCharacters << bStatRelated << logicalExpression << successJump << failureJump << tries;
}

void EventJump::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);

	dataStream >> jumpSceneId >> jumpExecutionOrder >> condition;
}
///Saving an object to a binary file
void EventJump::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);

	dataStream << jumpSceneId << jumpExecutionOrder << condition;
}

//This constructor is a special guest here, because it needs to grab a Voice from Story, which is impossible in header file due to looping
EventNarrate::EventNarrate(unsigned executionOrder, QString&& label, QVector<Sentence>&& speech, QString&& voiceName) :
	Event(executionOrder, move(label)), speech(move(speech)), voiceName(move(voiceName))
{
	voice = Story::getInstance().findVoice(this->voiceName);
}

void EventNarrate::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);

	dataStream >> speech >> voiceName;
	voice = Story::getInstance().findVoice(this->voiceName);
}

void EventNarrate::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);

	dataStream << speech << voiceName;
}

void EventSpeak::serializableLoad(QDataStream& dataStream)
{
	EventNarrate::serializableLoad(dataStream);

	dataStream >> characterName >> displayedName;
}

EventSpeak::EventSpeak(unsigned executionOrder, QString&& label, QVector<Sentence>&& speech, QString&& voice, QString&& characterName, QString&& displayedName) :
	EventNarrate(executionOrder, move(label), move(speech), move(voiceName)), characterName(move(characterName)), displayedName(move(displayedName)) 
{
	character = Story::getInstance().findCharacter(characterName);
}

void EventSpeak::serializableSave(QDataStream& dataStream) const
{
	EventNarrate::serializableSave(dataStream);

	dataStream << characterName << displayedName;
}

void EventWait::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);

	dataStream >> waitTime;
}
///Saving an object to a binary file
void EventWait::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);

	dataStream << waitTime;
}