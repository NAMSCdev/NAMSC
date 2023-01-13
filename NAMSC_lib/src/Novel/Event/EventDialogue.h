#pragma once
#include "Novel/Event/Event.h"

#include <QElapsedTimer>

#include "Novel/Data/Text/Sentence.h"

/// Displays text said by one of the Characters or the Narrator
class EventDialogue final : public Event
{
	/// Swap trick
	friend void swap(EventDialogue& first, EventDialogue& second) noexcept;
public:
	explicit EventDialogue(Scene* const parentScene)   noexcept;
	/// \param label Displayed in the Editor to distinquish important Event
	/// \exception One of the Actions or Sentences contains an Error
	EventDialogue(Scene* const parentScene, const QString& label, const std::vector<Sentence>& sentences = std::vector<Sentence>(), std::vector<std::unique_ptr<Action>>&& actions = std::move(std::vector<std::unique_ptr<Action>>()));
	EventDialogue(const EventDialogue& obj)            noexcept = delete;
	EventDialogue(EventDialogue&& obj)                 noexcept;
	EventDialogue& operator=(const EventDialogue& obj) noexcept = delete;
	bool operator==(const EventDialogue& obj) const    noexcept = delete;
	bool operator!=(const EventDialogue& obj) const    noexcept = delete;

	/// \exception Error invalid Action in `actions_` / invalid Sentence in `sentences`
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the EventDialogue's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const std::vector<Sentence>* const sentences)> onRun) noexcept;

	void acceptVisitor(EventVisitor* visitor) override;

	/// \todo make it private and create getters/setters
	std::vector<Sentence> sentences;

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventDialogue's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Scene* const parentScene, const QString& label, const std::vector<Sentence>* const sentences)> onRun_ = nullptr;

	QElapsedTimer cpsTimer;

	/// Whether the user provided input to skip the text appearing
	bool bCickSkip = false;

	/// Prevents accidential Scene skip due to a double click when one was intended (just to skip the text appearing)
	QElapsedTimer antiDoubleClickTimer;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};