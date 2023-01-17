#include "Novel/Event/EventInput.h"

#include "Novel/Data/Scene.h"

EventInput::EventInput(Scene* const parentScene) noexcept
	: Event(parentScene)
{
	errorCheck(true);
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(EventInput& first, EventInput& second) noexcept
{
	using std::swap;
	swap(static_cast<Event&>(first), static_cast<Event&>(second));
	swap(first.minCharacters,                            second.minCharacters);
	swap(first.regex,                                    second.regex);
	swap(first.inputStatName_,                           second.inputStatName_);
	swap(first.bDigitsOnly,                              second.bDigitsOnly);
	swap(first.digitsOnly_min,                           second.digitsOnly_min);
	swap(first.digitsOnly_max,                           second.digitsOnly_max);
	swap(first.bLogicalExpression,                       second.bLogicalExpression);
	swap(first.logicalExpression,                        second.logicalExpression);
	swap(first.logicalExpression_tries,                  second.logicalExpression_tries);
	swap(first.logicalExpression_failureJumpToSceneName, second.logicalExpression_failureJumpToSceneName);
	swap(first.onSuccess_,                               second.onSuccess_);
	swap(first.onFailure_,                               second.onFailure_);
	swap(first.onReject_,                                second.onReject_);
}

EventInput::EventInput(Scene* const parentScene, const QString& label, const QString& inputStatName, bool bDigitsOnly, const long long digitsOnly_min, const long long digitsOnly_max, uint minCharacters, const QString& regex, bool bLogicalExpression, const QString& logicalExpression, int logicalExpression_tries, const QString& logicalExpression_failureJumpToSceneName)
	: Event(parentScene, label), 
	minCharacters(minCharacters), 
	regex(regex), 
	inputStatName_(inputStatName),
	bDigitsOnly(bDigitsOnly),
	digitsOnly_min(digitsOnly_min), 
	digitsOnly_max(digitsOnly_max),
	bLogicalExpression(bLogicalExpression),
	logicalExpression(logicalExpression),
	logicalExpression_tries(logicalExpression_tries), 
	logicalExpression_failureJumpToSceneName(logicalExpression_failureJumpToSceneName)
{
}

void EventInput::setOnSuccessListener(std::function<void(const Scene* const parentScene, const QString& label, const Stat* const inputStat, const uint& minCharacters, const QString& regex, const QString& inputStatName, const bool& bDigitsOnly, const long long& digitsOnly_min, const long long& digitsOnly_max, const bool& bLogicalExpression, const QString& logicalExpression, const int& logicalExpression_tries, const QString& logicalExpression_failureJumpToSceneName)> onSuccess) noexcept
{ 
	onSuccess_ = onSuccess; 
}

void EventInput::setOnFailureListener(std::function<void(const Scene* const parentScene, const QString& label, const Stat* const inputStat, const uint& minCharacters, const QString& regex, const QString& inputStatName, const bool& bDigitsOnly, const long long& digitsOnly_min, const long long& digitsOnly_max, const bool& bLogicalExpression, const QString& logicalExpression, const int& logicalExpression_tries, const QString& logicalExpression_failureJumpToSceneName)> onFailure) noexcept
{ 
	onFailure_ = onFailure;
}

void EventInput::setOnRejectListener(std::function<void(const Scene* const parentScene, const QString& label, const Stat* const inputStat, const uint& minCharacters, const QString& regex, const QString& inputStatName, const bool& bDigitsOnly, const long long& digitsOnly_min, const long long& digitsOnly_max, const bool& bLogicalExpression, const QString& logicalExpression, const int& logicalExpression_tries, const QString& logicalExpression_failureJumpToSceneName)> onReject) noexcept
{ 
	onReject_ = onReject; 
}

void EventInput::serializableLoad(QDataStream& dataStream)
{
	Event::serializableLoad(dataStream);
	dataStream >> bDigitsOnly >> digitsOnly_min >> digitsOnly_max >> minCharacters >> regex >>  bLogicalExpression >> logicalExpression >> logicalExpression_tries >> logicalExpression_failureJumpToSceneName >> inputStatName_;

	errorCheck();
}

void EventInput::serializableSave(QDataStream& dataStream) const
{
	Event::serializableSave(dataStream);
	dataStream << bDigitsOnly << digitsOnly_min << digitsOnly_max << minCharacters << regex << bLogicalExpression << logicalExpression << logicalExpression_tries << logicalExpression_failureJumpToSceneName << inputStatName_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

EventInput::EventInput(EventInput&& obj) noexcept
	: Event(obj.parentScene)
{
	swap(*this, obj);
}

QString EventInput::getInputStatName() const noexcept
{
	return inputStatName_;
}

const Stat* EventInput::getInputStat() const noexcept
{
	return inputStat_;
}

Stat* EventInput::getInputStat() noexcept
{
	return inputStat_; 
}

void EventInput::setInputStat(const QString& inputStatName) noexcept
{
	inputStatName_ = inputStatName;
	syncWithSave();
}

void EventInput::acceptVisitor(EventVisitor* visitor) 
{
	visitor->visitEventInput(this); 
}

NovelLib::SerializationID EventInput::getType() const noexcept 
{ 
	return NovelLib::SerializationID::EventInput;
}