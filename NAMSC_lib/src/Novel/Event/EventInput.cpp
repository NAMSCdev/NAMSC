#include "Novel/Event/EventInput.h"

#include "Novel/Data/Scene.h"

EventInput::EventInput(Scene* const parentScene) noexcept
	: Event(parentScene)
{
	checkForErrors(true);
}

EventInput::EventInput(Scene* const parentScene, const QString& label, uint minCharacters, const QString& regex, const QString& inputStatName, bool bDigitsOnly, const long long digitsOnly_min, const long long digitsOnly_max, bool bLogicalExpression, const QString& logicalExpression, int logicalExpression_tries, const QString& logicalExpression_failureJumpToSceneName, std::vector<std::unique_ptr<Action>>&& actions)
	: Event(parentScene, label, std::move(actions)), minCharacters(minCharacters), regex(regex), inputStatName_(inputStatName), bDigitsOnly(bDigitsOnly), digitsOnly_min(digitsOnly_min), digitsOnly_max(digitsOnly_max), bLogicalExpression(bLogicalExpression), logicalExpression(logicalExpression), logicalExpression_tries(logicalExpression_tries), logicalExpression_failureJumpToSceneName(logicalExpression_failureJumpToSceneName)
{
}

EventInput::EventInput(const EventInput& obj) noexcept
	: Event(parentScene)
{
	//TODO: change to swap trick for more efficency
	*this = obj;
}

EventInput& EventInput::operator=(const EventInput& obj) noexcept
{
	if (this == &obj) return *this;

	Event::operator=(obj);
	//onSuccess_              = obj.onSuccess_;
	//onFailure_              = obj.onFailure_;
	//onReject_               = obj.onReject_;
	minCharacters           = obj.minCharacters;
	regex                   = obj.regex;
	inputStatName_          = obj.inputStatName_;
	bDigitsOnly             = obj.bDigitsOnly;
	digitsOnly_min          = obj.digitsOnly_min;
	digitsOnly_max          = obj.digitsOnly_max;
	bLogicalExpression      = obj.bLogicalExpression;
	logicalExpression       = obj.logicalExpression;
	logicalExpression_tries = obj.logicalExpression_tries;
	logicalExpression_failureJumpToSceneName = obj.logicalExpression_failureJumpToSceneName;

	return *this;
}

bool EventInput::operator==(const EventInput& obj) const noexcept
{
	if (this == &obj) return true;

	return 	Event::operator==(obj)                                                          &&
			minCharacters           == obj.minCharacters                                    &&
			regex                   == obj.regex                                            &&
			inputStatName_          == obj.inputStatName_                                   &&
			bDigitsOnly             == obj.bDigitsOnly                                      &&
			digitsOnly_min          == obj.digitsOnly_min                                   &&
			digitsOnly_max          == obj.digitsOnly_max                                   &&
			bLogicalExpression      == obj.bLogicalExpression                               &&
			logicalExpression       == obj.logicalExpression                                &&
			logicalExpression_tries == obj.logicalExpression_tries                          &&
			logicalExpression_failureJumpToSceneName == obj.logicalExpression_failureJumpToSceneName;
}

bool EventInput::checkForErrors(bool bComprehensive) const
{
	bool bError = Event::checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		//todo check if `regex` is valid
		//todo check if `logicalExpression` is valid
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "An Error occurred in EventInput::checkForErrors of Scene \"" + parentScene->name + "\" Event" << getIndex();

	return bError;
}

Event* EventInput::clone() const
{
	EventInput* clone = new EventInput(*this);
	return clone;
}

void EventInput::run()
{
}

void EventInput::syncWithSave() noexcept
{
}

/// Sets a function pointer that is called (if not nullptr) after the EventInput's `void run()` when the input was accepted, allowing for data read

void EventInput::setOnSuccessListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QPlainTextEdit* textEdit, Stat* inputStat, uint minCharacters, QString regex, QString inputStatName, bool bDigitsOnly, long long digitsOnly_min, long long digitsOnly_max, bool bLogicalExpression, QString logicalExpression, int logicalExpression_tries, QString logicalExpression_failureJumpToSceneName)> onSuccess) noexcept 
{ 
	onSuccess_ = onSuccess; 
}

/// Sets a function pointer that is called (if not nullptr) after the EventInput's `void run()` when the input was rejected too many times, allowing for data read

void EventInput::setOnFailureListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QPlainTextEdit* textEdit, Stat* inputStat, uint minCharacters, QString regex, QString inputStatName, bool bDigitsOnly, long long digitsOnly_min, long long digitsOnly_max, bool bLogicalExpression, QString logicalExpression, int logicalExpression_tries, QString logicalExpression_failureJumpToSceneName)> onFailure) noexcept
{ 
	onFailure_ = onFailure;
}

/// Sets a function pointer that is called (if not nullptr) after the EventInput's `void run()` every time the input was rejected (less than `tries` times), allowing for data read

void EventInput::setOnRejectListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QPlainTextEdit* textEdit, Stat* inputStat, uint minCharacters, QString regex, QString inputStatName, bool bDigitsOnly, long long digitsOnly_min, long long digitsOnly_max, bool bLogicalExpression, QString logicalExpression, int logicalExpression_tries, QString logicalExpression_failureJumpToSceneName)> onReject) noexcept
{ 
	onReject_ = onReject; 
}

void EventInput::setInputStat(const QString& inputStatName) noexcept
{ 
	inputStatName_ = inputStatName; 
	syncWithSave();
}

Stat* EventInput::getInputStat() noexcept
{
	return inputStat_; 
}

const Stat* EventInput::getInputStat() const noexcept
{ 
	return inputStat_; 
}

QString EventInput::getInputStatName() const noexcept
{ 
	return inputStatName_; 
}

void EventInput::acceptVisitor(EventVisitor* visitor) { visitor->visitEventInput(this); }

void EventInput::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	dataStream >> minCharacters >> regex >> bDigitsOnly >> digitsOnly_min >> digitsOnly_max >> bLogicalExpression >> logicalExpression >> logicalExpression_tries >> logicalExpression_failureJumpToSceneName >> inputStatName_;
	checkForErrors();
}

void EventInput::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << minCharacters << regex << bDigitsOnly << digitsOnly_min << digitsOnly_max << bLogicalExpression << logicalExpression << logicalExpression_tries << logicalExpression_failureJumpToSceneName << inputStatName_;
}