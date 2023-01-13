#pragma once
#include "Novel/Event/Event.h"

#include <QPlainTextEdit>

#include "Novel/Data/Stat/Stat.h"

/// \todo Add StatDouble insert methods
/// \todo Add QSlider/QSpinBox insert methods
/// Waits for a text/numeric input from the Player
class EventInput final : public Event
{
	/// Swap trick
	friend void swap(EventInput& first, EventInput& second) noexcept;
public:
	explicit EventInput(Scene* const parentScene) noexcept;
	/// \param label Displayed in the Editor to distinquish important Events
	/// \param inputStatName The ActionInput will store the entered text (or number if it is set to be digitsOnly) inside this Stat if it is set
	/// \param minCharacters Can be zero
	/// \param regex Limits input that can be entered into a QPlainTextEdit using a Regular Expression
	/// \param bDigitsOnly The only way to insert a value into a StatLongLong is to set this to `true`. You can still insert a digitsOnly text into a StringStat
	/// \param digitsOnly_min Min and max are available only when `bDigitsOnly` is `true`
	/// \param digitsOnly_max Min and max are available only when `bDigitsOnly` is `true`
	/// \param bLogicalExpression Enable logical expressions instead of a write to a Stat and perform an ActionJump on success or failure
	/// \param The expresion to be evaluated after the Player entered the text (and pressed the Enter, no multiline allowed)
	/// \param -1 is unlimited tries to enter the text, so basically until `logicalExpression` evaluates to `true`
	/// \param Perform jump if `logicalExpression` failed
	/// \exception One of the Actions contains an Error or the regex is not properly formatted or the Stat couldn't be found or logicalExpression is not properly formatted
	EventInput(Scene* const parentScene, const QString& label, const QString& inputStatName = "", bool bDigitsOnly = false, const long long digitsOnly_min = 0, const long long digitsOnly_max = 1000, uint minCharacters = 0, const QString& regex = "", bool bLogicalExpression = false, const QString& logicalExpression = "", int logicalExpression_tries = 0, const QString& logicalExpression_failureJumpToSceneName = "", std::vector<std::unique_ptr<Action>>&& actions = std::move(std::vector<std::unique_ptr<Action>>()));
	EventInput(const EventInput& obj)            noexcept = delete;
	EventInput(EventInput&& obj)                 noexcept;
	EventInput& operator=(const EventInput& obj) noexcept = delete;
	bool operator==(const EventInput& obj) const noexcept = delete;
	bool operator!=(const EventInput& obj) const noexcept = delete;
	
	/// \exception Error invalid Action in `actions_` / invalid `regex` / invalid `Stat` / invalid `logicalExpression`
	/// \return Whether an Error has occurred
	/// \todo implement this
	bool errorCheck(bool bComprehensive = false) const override;

	void run() override;

	void syncWithSave() noexcept override;

	/// Sets a function pointer that is called (if not nullptr) after the EventInput's `void run()` when the input was accepted, allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnSuccessListener(std::function<void(const Scene* const parentScene, const QString& label, const Stat* const inputStat, const uint& minCharacters, const QString& regex, const QString& inputStatName, const bool& bDigitsOnly, const long long& digitsOnly_min, const long long& digitsOnly_max, const bool& bLogicalExpression, const QString& logicalExpression, const int& logicalExpression_tries, const QString& logicalExpression_failureJumpToSceneName)> onSuccess) noexcept;

	/// Sets a function pointer that is called (if not nullptr) after the EventInput's `void run()` when the input was rejected too many times, allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnFailureListener(std::function<void(const Scene* const parentScene, const QString& label, const Stat* const inputStat, const uint& minCharacters, const QString& regex, const QString& inputStatName, const bool& bDigitsOnly, const long long& digitsOnly_min, const long long& digitsOnly_max, const bool& bLogicalExpression, const QString& logicalExpression, const int& logicalExpression_tries, const QString& logicalExpression_failureJumpToSceneName)> onFailure) noexcept;

	/// Sets a function pointer that is called (if not nullptr) after the EventInput's `void run()` every time the input was rejected (less than `tries` times), allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRejectListener(std::function<void(const Scene* parentScene, const QString& label, const Stat* const inputStat, const uint& minCharacters, const QString& regex, const QString& inputStatName, const bool& bDigitsOnly, const long long& digitsOnly_min, const long long& digitsOnly_max, const bool& bLogicalExpression, const QString& logicalExpression, const int& logicalExpression_tries, const QString& logicalExpression_failureJumpToSceneName)> onReject) noexcept;
									
	QString getInputStatName() const noexcept;
	const Stat* getInputStat() const noexcept;
	Stat*       getInputStat()       noexcept;
	void setInputStat(const QString& inputStatName) noexcept;

	void acceptVisitor(EventVisitor* visitor) override;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// The only way to insert a value into an IntStat is to set this to `true`. You can still insert a digitsOnly text into a StringStat
	bool bDigitsOnly            = false;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Min and max are available only when `bDigitsOnly` is `true`
	long long digitsOnly_min    = 0,
			  digitsOnly_max    = 1000;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Can be zero
	uint minCharacters          = 1;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Limits input that can be entered into a QPlainTextEdit using a Regular Expression
	QString regex               = "";

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Enable logical expressions instead of a write to a Stat and perform an ActionJump on success or failure
	bool bLogicalExpression     = false;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// The expresion to be evaluated after the Player entered the text (and pressed the Enter, no multiline allowed)
	QString logicalExpression   = "";

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// -1 is unlimited tries to enter the text, so basically until `logicalExpression` evaluates to `true`
	int	logicalExpression_tries = -1;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Perform jump if `logicalExpression` failed
	QString logicalExpression_failureJumpToSceneName = "";

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventInput's `void run()` when the input was accepted, allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Scene* const parentScene, const QString& label, const Stat* const inputStat, const uint& minCharacters, const QString& regex, const QString& inputStatName, const bool& bDigitsOnly, const long long& digitsOnly_min, const long long& digitsOnly_max, const bool& bLogicalExpression, const QString& logicalExpression, const int& logicalExpression_tries, const QString& logicalExpression_failureJumpToSceneName)> onSuccess_ = nullptr;

	/// A function pointer that is called (if not nullptr) after the EventInput's `void run()` when the input was rejected too many times, allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Scene* const parentScene, const QString& label, const Stat* const inputStat, const uint& minCharacters, const QString& regex, const QString& inputStatName, const bool& bDigitsOnly, const long long& digitsOnly_min, const long long& digitsOnly_max, const bool& bLogicalExpression, const QString& logicalExpression, const int& logicalExpression_tries, const QString& logicalExpression_failureJumpToSceneName)> onFailure_ = nullptr;

	/// A function pointer that is called (if not nullptr) after the EventInput's `void run()` every time the input was rejected (less than `tries` times), allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Scene* const parentScene, const QString& label, const Stat* const inputStat, const uint& minCharacters, const QString& regex, const QString& inputStatName, const bool& bDigitsOnly, const long long& digitsOnly_min, const long long& digitsOnly_max, const bool& bLogicalExpression, const QString& logicalExpression, const int& logicalExpression_tries, const QString& logicalExpression_failureJumpToSceneName)> onReject_ = nullptr;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
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