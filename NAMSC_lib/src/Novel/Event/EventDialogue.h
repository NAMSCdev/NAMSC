#pragma once
#include "Novel/Event/Event.h"

#include "Novel/Data/Text/Sentence.h"

/// Displays text said by one of the Characters or the Narrator
class EventDialogue final : public Event
{
public:
	EventDialogue(Scene* const parentScene) noexcept;
	/// \exception One of the Actions or Sentences contains an Error
	EventDialogue(Scene* const parentScene, const QString& label, const std::vector<Sentence>& sentence);
	/// \exception One of the Actions or Sentences contains an Error
	EventDialogue(Scene* const parentScene, const QString& label, const std::vector<Sentence>& sentences, std::vector<std::unique_ptr<Action>>&& actions);
	EventDialogue(const EventDialogue& obj)         = delete;
	EventDialogue& operator=(const EventDialogue& obj) noexcept;
	bool operator==(const EventDialogue& obj) const noexcept;
	bool operator!=(const EventDialogue& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error invalid Action in `actions_` / invalid Sentence in `sentences`
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the EventDialogue's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, std::vector<Sentence>* sentences)> onRun) noexcept;

	void acceptVisitor(EventVisitor* visitor) override;

	std::vector<Sentence> sentences;

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventDialogue's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, std::vector<Sentence>* sentences)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};