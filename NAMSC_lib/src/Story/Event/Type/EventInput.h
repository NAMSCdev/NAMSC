#pragma once
#include "Global.h"

#include "Story/Event/Event.h"
#include "Story/Event/Type/EventJump.h"

///Waits for an input from the Player
class EventInput final : public Event
{
public:
	EventInput() = default;
	EventInput(unsigned sceneID, unsigned executionOrder, QString &&inputStat, bool bDigitsOnly = false, long long min = 0, long long max = 1000, unsigned minCharacters = 1, bool bStatRelated = true,
		QString &&logicalExpression = "", 
			unsigned successJumpSceneId = 0, unsigned successJumpExecutionOrder = 0, QString &&successCondition = "",
		unsigned failureJumpSceneId = 0, unsigned failureJumpExecutionOrder = 0, QString &&failureCondition = "", 
			int tries = -1, QString &&label = "") :
			Event(sceneID, executionOrder, move(label)), inputStat(move(inputStat)), bDigitsOnly(bDigitsOnly), min(min), max(max), minCharacters(minCharacters), bStatRelated(bStatRelated), 
		logicalExpression(move(logicalExpression)), 
			successJump(0, 0, successJumpSceneId, successJumpExecutionOrder, move(successCondition)),
		failureJump(0, 0, failureJumpSceneId, failureJumpExecutionOrder, move(failureCondition)),
			tries(tries) {}

	///Executes Event's logic
	void			run			() override;

	///Accepts EventVisitor
	void			accept		(EventVisitor* visitor) override	{ visitor->visitEventInput(this); }

protected:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID			getType		() const override			{ return SerializationID::EventInput; }

	///The ActionInput will store the entered text (or number if it is set to be DigitsOnly) inside this Stat if it is set
	QString			inputStat;

	///The only way to insert a value into an IntStat is to set this to [true]. You can still insert a DigitsOnly text into a StringStat
	bool			bDigitsOnly		= false;

	///Min and max, when [bDigitsOnly] is [true]
	long long		min		= 0,
			max		= 1000;
		
	///Minimum characters for the input, can be zero, but by defaut is 1
	unsigned		minCharacters			= 1;

	///[optional] Enable logical expressions instead of stat manipulation and perform an ActionJump on success or failure
	bool			bStatRelated			= true;

	///[optional] The expresion to be evaluated after the Player entered the text (and pressed the Enter)
	QString			logicalExpression;

	///[optional] Perform jump depending on [logicExpression] evaluation
	EventJump		successJump,
			failureJump;

	///[optional] -1 is unlimited tries to enter the text, so basically until [logicExpression] evaluates to [true]
	int		tries			= -1;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override
	{
		Event::serializableLoad(dataStream);

		dataStream >> inputStat >> bDigitsOnly >> min >> max >> minCharacters >> bStatRelated >> logicalExpression >> successJump >> failureJump >> tries;
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override
	{
		Event::serializableSave(dataStream);

		dataStream << inputStat << bDigitsOnly << min << max << minCharacters << bStatRelated << logicalExpression << successJump << failureJump << tries;
	}
};
