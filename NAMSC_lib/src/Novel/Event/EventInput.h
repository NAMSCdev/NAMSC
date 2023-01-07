#pragma once
#include "Novel/Event/Event.h"

#include <QPlainTextEdit>

#include "Novel/Data/Stat/Stat.h"

/// Waits for a text/numeric input from the Player
class EventInput final : public Event
{
public:
	EventInput(Scene* const parentScene) noexcept;
	/// \exception One of the Actions contains an Error or the regex is not properly formatted or the Stat couldn't be found or logicalExpression is not properly formatted
	EventInput(Scene* const parentScene, const QString& label, uint minCharacters, const QString& regex, const QString& inputStatName, bool bDigitsOnly, const long long digitsOnly_min, const long long digitsOnly_max, bool bLogicalExpression, const QString& logicalExpression, int logicalExpression_tries, const QString& logicalExpression_failureJumpToSceneName, std::vector<std::unique_ptr<Action>>&& actions = std::vector<std::unique_ptr<Action>>());
	EventInput(const EventInput& obj) noexcept;
	EventInput& operator=(const EventInput& obj) noexcept;
	bool operator==(const EventInput& obj) const noexcept;
	bool operator!=(const EventInput& obj) const = default; //{ return !(*this == obj); }
	
	/// \exception Error invalid Action in `actions_` / invalid `regex` / invalid `Stat` / invalid `logicalExpression`
	/// \return Whether an Error has occurred
	/// \todo implement this
	bool checkForErrors(bool bComprehensive = false) const override;

	virtual Event* clone() const override;

	void run() override;

	void syncWithSave() noexcept override;

	/// Sets a function pointer that is called (if not nullptr) after the EventInput's `void run()` when the input was accepted, allowing for data read
	void setOnSuccessListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QPlainTextEdit* textEdit, Stat* inputStat, uint minCharacters, QString regex, QString inputStatName, bool bDigitsOnly, long long digitsOnly_min, long long digitsOnly_max, bool bLogicalExpression, QString logicalExpression, int logicalExpression_tries, QString logicalExpression_failureJumpToSceneName)> onSuccess) noexcept;

	/// Sets a function pointer that is called (if not nullptr) after the EventInput's `void run()` when the input was rejected too many times, allowing for data read
	void setOnFailureListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QPlainTextEdit* textEdit, Stat* inputStat, uint minCharacters, QString regex, QString inputStatName, bool bDigitsOnly, long long digitsOnly_min, long long digitsOnly_max, bool bLogicalExpression, QString logicalExpression, int logicalExpression_tries, QString logicalExpression_failureJumpToSceneName)> onFailure) noexcept;

	/// Sets a function pointer that is called (if not nullptr) after the EventInput's `void run()` every time the input was rejected (less than `tries` times), allowing for data read
	void setOnRejectListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QPlainTextEdit* textEdit, Stat* inputStat, uint minCharacters, QString regex, QString inputStatName, bool bDigitsOnly, long long digitsOnly_min, long long digitsOnly_max, bool bLogicalExpression, QString logicalExpression, int logicalExpression_tries, QString logicalExpression_failureJumpToSceneName)> onReject) noexcept;
													    
	void setInputStat(const QString& inputStatName) noexcept;
	Stat* getInputStat() noexcept;
	const Stat* getInputStat() const noexcept;
	QString getInputStatName() const noexcept;
													    
	void acceptVisitor(EventVisitor* visitor) override;

	/// Can be zero
	uint minCharacters = 1;

	/// Limits input that can be entered into a QPlainTextEdit using a Regular Expression
	QString regex      = "";

	/// The only way to insert a value into an IntStat is to set this to [true]. You can still insert a digitsOnly text into a StringStat
	bool bDigitsOnly   = false;

	/// Min and max are available only when [bDigitsOnly] is [true]
	long long digitsOnly_min    = 0,
			  digitsOnly_max    = 1000;

	/// [optional] Enable logical expressions instead of a write to a Stat and perform an ActionJump on success or failure
	bool bLogicalExpression     = false;

	/// [optional] The expresion to be evaluated after the Player entered the text (and pressed the Enter, no multiline allowed)
	QString logicalExpression   = "";

	/// [optional] -1 is unlimited tries to enter the text, so basically until `logicalExpression` evaluates to `true`
	int	logicalExpression_tries = -1;

	/// [optional] Perform jump if `logicalExpression` failed
	QString logicalExpression_failureJumpToSceneName = "";

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override { return NovelLib::SerializationID::EventInput; }

	/// A function pointer that is called (if not nullptr) after the EventInput's `void run()` when the input was accepted, allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, QPlainTextEdit* textEdit, Stat* inputStat, uint minCharacters, QString regex, QString inputStatName, bool bDigitsOnly, long long digitsOnly_min, long long digitsOnly_max, bool bLogicalExpression, QString logicalExpression, int logicalExpression_tries, QString logicalExpression_failureJumpToSceneName)> onSuccess_ = nullptr;

	/// A function pointer that is called (if not nullptr) after the EventInput's `void run()` when the input was rejected too many times, allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, QPlainTextEdit* textEdit, Stat* inputStat, uint minCharacters, QString regex, QString inputStatName, bool bDigitsOnly, long long digitsOnly_min, long long digitsOnly_max, bool bLogicalExpression, QString logicalExpression, int logicalExpression_tries, QString logicalExpression_failureJumpToSceneName)> onFailure_ = nullptr;

	/// A function pointer that is called (if not nullptr) after the EventInput's `void run()` every time the input was rejected (less than `tries` times), allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, QPlainTextEdit* textEdit, Stat* inputStat, uint minCharacters, QString regex, QString inputStatName, bool bDigitsOnly, long long digitsOnly_min, long long digitsOnly_max, bool bLogicalExpression, QString logicalExpression, int logicalExpression_tries, QString logicalExpression_failureJumpToSceneName)> onReject_ = nullptr;

	/// The ActionInput will store the entered text (or number if it is set to be digitsOnly) inside this Stat if it is set
	QString	inputStatName_ = "";
	Stat*   inputStat_     = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};