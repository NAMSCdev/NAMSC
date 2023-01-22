#pragma once
#include "Novel/Event/Event.h"

#include <QElapsedTimer>

#include "Novel/Data/Text/Sentence.h"

/// Displays text said by one of the Characters or the Narrator
class EventDialogue final : public Event
{
	friend class NovelSettings;
	/// Swap trick
	friend void swap(EventDialogue& first, EventDialogue& second) noexcept;
public:
	explicit EventDialogue(Scene* const parentScene)   noexcept;
	/// \param label Displayed in the Editor to distinquish important Event
	/// \exception One of the Actions or Sentences contains an Error
	EventDialogue(Scene* const parentScene, const QString& label, const std::vector<Sentence>& sentences = std::vector<Sentence>());
	EventDialogue(const EventDialogue& obj)            noexcept;
	EventDialogue(EventDialogue&& obj)                 noexcept;
	///This one needs to be optimized at the cost of strong exception safety, as it is frequently assigned during gameplay (so the performance is a priority here)
	///No swap trick to avoid containers reallocation
	EventDialogue& operator=(const EventDialogue& obj) noexcept;
	bool operator==(const EventDialogue& obj) const    noexcept;
	bool operator!=(const EventDialogue& obj) const    noexcept = default;

	/// \exception Error invalid Action in `actions_` / invalid Sentence in `sentences`
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the EventDialogue's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const std::vector<Sentence>* const sentences)> onRun) noexcept;

	const std::vector<Sentence>* getSentences() const noexcept;
	/// \exception Error Tried to get a Sentence past the `sentences_` container's size
	const Sentence* getSentence(uint index)     const;
	/// \exception Error Tried to get a Sentence past the `sentences_` container's size
	Sentence* getSentence(uint index);
	const std::vector<Sentence>* setSentences(const std::vector<Sentence>& sentences) noexcept;
	const std::vector<Sentence>* setSentences(std::vector<Sentence>&& sentences)      noexcept;
	/// \exception Error Tried to insert a Sentence past the `sentences_` container's size
	Sentence* insertSentence(uint index, const Sentence& sentence);
	/// \exception Error Tried to insert a Sentence past the `sentences_` container's size
	Sentence* insertSentence(uint index, Sentence&& sentence);
	/// \exception Error Tried to reinsert a Sentence past the `sentences_` container's size
	Sentence* reinsertSentence(uint index, uint newIndex);
	Sentence* addSentence(const Sentence& sentence);
	Sentence* addSentence(Sentence&& sentence);
	/// \exception Error Tried to remove a Sentence past the `sentences_` container's size
	bool removeSentence(uint index);
	void clearSentences() noexcept;
	
	void acceptVisitor(EventVisitor* visitor) override;

	//todo: do not botch
	QString getComponentSubTypeName()    const noexcept override { return "Dialogue"; }
    EventSubType getComponentEventType() const noexcept override { return EventSubType::EVENT_DIALOG; }
private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventDialogue's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Scene* const parentScene, const QString& label, const std::vector<Sentence>* const sentences)> onRun_ = nullptr;

	std::vector<Sentence> sentences_;
public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};