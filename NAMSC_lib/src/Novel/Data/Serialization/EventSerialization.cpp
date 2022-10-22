#pragma once
#include "Novel/Event/EventsAll.h"
#include "Novel/Action/ActionsAll.h"
#include "Novel/Data/Novel.h"

void Event::serializableLoad(QDataStream& dataStream)
{
	dataStream >> label >> executionOrder;

	uint actionsSize;
	dataStream >> actionsSize;
	for (uint i = 0u; i != actionsSize; ++i)
	{
		SerializationID type;
		dataStream >> type;

		Action* action;
		switch (type)
		{
		case SerializationID::ActionChangeMusic:
			action = new ActionChangeMusic();
			break;
		case SerializationID::ActionPlaySound:
			action = new ActionPlaySound();
			break;
		case SerializationID::ActionStatHide: 
			action = new ActionStatHide();
			break;
		case SerializationID::ActionStatVisibility: 
			action = new ActionStatVisibility();
			break;
		case SerializationID::ActionStatChange: 
			action = new ActionStatChange();
			break;
		case SerializationID::ActionEffectBlur: 
			action = new ActionEffectBlur();
			break;
		case SerializationID::ActionEffectDistort: 
			action = new ActionEffectDistort();
			break;
		case SerializationID::ActionEffectGlow: 
			action = new ActionEffectGlow();
			break;
		case SerializationID::ActionFilterBlur: 
			action = new ActionFilterBlur();
			break;
		case SerializationID::ActionFilterBrightness: 
			action = new ActionFilterBrightness();
			break;
		case SerializationID::ActionFilterDilation:
			action = new ActionFilterDilation();
			break;
		case SerializationID::ActionFilterErosion:
			action = new ActionFilterErosion();
			break;
		case SerializationID::ActionFilterHue:
			action = new ActionFilterHue();
			break;
		case SerializationID::ActionFilterNegative:
			action = new ActionFilterNegative();
			break;
		case SerializationID::ActionFilterSaturation:
			action = new ActionFilterSaturation();
			break;
		case SerializationID::ActionCharLive2DAnim:
			action = new ActionCharLive2DAnim();
			break;
		case SerializationID::ActionSceneryObjectAnimMove:
			action = new ActionSceneryObjectAnimMove();
			break;
		case SerializationID::ActionSceneryObjectAnimScale:
			action = new ActionSceneryObjectAnimScale();
			break;
		case SerializationID::ActionSceneryObjectAnimRotate:
			action = new ActionSceneryObjectAnimRotate();
			break;
		case SerializationID::ActionSceneryObjectAnimColor:
			action = new ActionSceneryObjectAnimColor();
			break;
		case SerializationID::ActionSceneryObjectVisibility:
			action = new ActionSceneryObjectVisibility();
			break;
		case SerializationID::ActionSceneryObjectImageChange:   
			action = new ActionSceneryObjectImageChange();
			break;
		case SerializationID::ActionSetBackground:
			action = new ActionSetBackground();
			break;
		default:
			//TODO: throw some Exception
			break;
		}
		dataStream >> *action;
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

	uint choicesSize;
	dataStream >> choicesSize;
	for (uint i = 0u; i != choicesSize; ++i)
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

void EventJump::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << jumpSceneId << jumpExecutionOrder << condition;
}

//This constructor is a special guest here, because it needs to grab a Voice from Novel, which is impossible in header file due to looping
EventNarrate::EventNarrate(uint executionOrder, QString&& label, QVector<Sentence>&& speech, QString&& voiceName) :
	Event(executionOrder, move(label)), speech(move(speech)), voiceName(move(voiceName))
{
	voice = Novel::getInstance().findVoice(this->voiceName);
}

void EventNarrate::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	dataStream >> speech >> voiceName;

	voice = Novel::getInstance().findVoice(this->voiceName);
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

//This constructor is a special guest here, because it needs to grab a Voice from Novel, which is impossible in header file due to looping
EventSpeak::EventSpeak(uint executionOrder, QString&& label, QVector<Sentence>&& speech, QString&& voice, QString&& characterName, QString&& displayedName) :
	EventNarrate(executionOrder, move(label), move(speech), move(voiceName)), characterName(move(characterName)), displayedName(move(displayedName)) 
{
	character = Novel::getInstance().findCharacter(characterName);
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

void EventWait::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << waitTime;
}