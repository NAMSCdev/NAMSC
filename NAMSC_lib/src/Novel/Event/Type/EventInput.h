#pragma once
#include "Global.h"

#include "Novel/Event/Event.h"
#include "Novel/Event/Type/EventJump.h"

///Waits for an input from the Player
class EventInput final : public Event
{
public:
	EventInput() = default;
	EventInput(uint executionOrder, QString&& label, QString&& inputStat, bool bDigitsOnly, long long min, long long max, uint minCharacters, QString&& regex,
			   bool bStatRelated, QString&& logicalExpression, int tries, uint successJumpSceneId, uint successJumpExecutionOrder, QString&& successCondition,
			   uint failureJumpSceneId, uint failureJumpExecutionOrder, QString&& failureCondition) :
		Event(executionOrder, move(label)), inputStat(move(inputStat)), bDigitsOnly(bDigitsOnly), min(min), max(max), minCharacters(minCharacters), regex(move(regex)),
		bStatRelated(bStatRelated), logicalExpression(move(logicalExpression)), tries(tries),
		successJump(0, 0, successJumpSceneId, successJumpExecutionOrder, move(successCondition)),
		failureJump(0, 0, failureJumpSceneId, failureJumpExecutionOrder, move(failureCondition)) {}
	EventInput(const EventInput& obj) { *this = obj; }
	EventInput& operator=(const EventInput& obj)
	{
		if (this == &obj) return *this;

		Event::operator=(obj);
		inputStat         = obj.inputStat;
		bDigitsOnly       = obj.bDigitsOnly;
		min               = obj.min;
		max               = obj.max;
		minCharacters     = obj.minCharacters;
		regex             = obj.regex;
		bStatRelated      = obj.bStatRelated;
		logicalExpression = obj.logicalExpression;
		tries	          = obj.tries;
		successJump       = obj.successJump;
		failureJump       = obj.failureJump;

		return *this;
	}
	///Executes this Event's logic
	void run() override;

	///Accepts an EventVisitor
	void accept(EventVisitor* visitor) override	{ visitor->visitEventInput(this); }

	///Assigns a QPlainTextEdit, from which the text will be copied 
	///@todo Add REGEXValidator to the plainText
	void assignTextEditor(QPlainTextEdit* plainTextEdit) { this->textEdit = plainTextEdit; }

signals:
	///A Qt signal executing after the Event's `run()` if the input was accepted, allowing for data read (and write if it is a pointer)
	void onSuccess(QPlainTextEdit* textEdit, Stat* inputStat, bool bDigitsOnly, long long min, long long max, uint minCharacters, QString&& regex, bool bStatRelated, QString logicalExpression, int tries);

	///A Qt signal executing after the Event's `run()` if the input was rejected too many times, allowing for data read (and write if it is a pointer)
	void onFailure(QPlainTextEdit* textEdit, Stat* inputStat, bool bDigitsOnly, long long min, long long max, uint minCharacters, QString&& regex, bool bStatRelated, QString logicalExpression, int tries);

	///A Qt signal executing after the Event's `run()` if the input was rejected (less than `tries` times), allowing for data read (and write if it is a pointer)
	void onReject(QPlainTextEdit* textEdit, Stat* inputStat, bool bDigitsOnly, long long min, long long max, uint minCharacters, QString&& regex, bool bStatRelated, QString logicalExpression, int tries);

private:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID getType() const override { return SerializationID::EventInput; }

	///The ActionInput will store the entered text (or number if it is set to be DigitsOnly) inside this Stat if it is set
	QString	inputStat;

	///The only way to insert a value into an IntStat is to set this to [true]. You can still insert a DigitsOnly text into a StringStat
	bool bDigitsOnly = false;

	///Min and max, when [bDigitsOnly] is [true]
	long long min = 0,
			  max = 1000;
		
	///Minimum characters for the input, can be zero
	uint minCharacters= 1;

	///Limits input that can be entered into a QPlainTextEdit
	QString regex;

	///[optional] Enable logical expressions instead of a write to a Stat and perform an ActionJump on success or failure
	bool bStatRelated = true;

	///[optional] The expresion to be evaluated after the Player entered the text (and pressed the Enter)
	QString logicalExpression;

	///[optional] -1 is unlimited tries to enter the text, so basically until [logicExpression] evaluates to [true]
	int	tries = -1;

	///[optional] Perform jump depending on [logicExpression] evaluation
	EventJump successJump,
			  failureJump;

	///Pointer to a QPlainTextEdit from which the text will be copied 
	QPlainTextEdit *textEdit;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};
