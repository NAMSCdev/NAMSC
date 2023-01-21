#pragma once
#include "Novel/Event/Event.h"

#include "Novel/Data/Text/Choice.h"

class Scene;

/// Creates a Choice selection window
class EventChoice final : public Event
{
	/// Swap trick
	friend void swap(EventChoice& first, EventChoice& second) noexcept;
public:
	explicit EventChoice(Scene* const parentScene) noexcept;
	/// \param label Displayed in the Editor to distinquish important Events
	/// \param A text to be displayed during Choice selection screen
	/// \exception One of the Actions or the Choices or the `text` contains an Error 
	EventChoice(Scene* const parentScene, const QString& label, const Translation& menuText = Translation());
	EventChoice(const EventChoice& obj)            noexcept;
	EventChoice(EventChoice&& obj)                 noexcept;
	///This one needs to be optimized at the cost of strong exception safety, as it is frequently assigned during gameplay (so the performance is a priority here)
	///No swap trick to avoid containers reallocation
	EventChoice& operator=(const EventChoice& obj) noexcept;
	bool operator==(const EventChoice& obj) const  noexcept;
	bool operator!=(const EventChoice& obj) const  noexcept = default;

	/// \exception Error Invalid Action in `actions_` / invalid Choice in `choices` / invalid `text`
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the EventChoice's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Scene* const parentScene, const QString& label, const Translation* const text, const std::vector<Choice>* const choices)> onRun) noexcept;

	const Translation* getMenuText() const        noexcept;
	Translation*       getMenuText()              noexcept;
	void setMenuText(const Translation& menuText) noexcept;

	const std::vector<Choice>* getChoices() const noexcept;
	/// \exception Error Tried to get a Choice past the `choices_` container's size
	const Choice* getChoice(uint index)     const;
	/// \exception Error Tried to get a Choice past the `choices_` container's size
	Choice* getChoice(uint index);
	const std::vector<Choice>* setChoices(const std::vector<Choice>& choices) noexcept;
	const std::vector<Choice>* setChoices(std::vector<Choice>&& choices)      noexcept;
	/// \exception Error Tried to insert a Choice past the `choices_` container's size
	Choice* insertChoice(uint index, const Choice& choice);
	/// \exception Error Tried to insert a Choice past the `choices_` container's size
	Choice* insertChoice(uint index, Choice&& choice);
	/// \exception Error Tried to reinsert a Choice past the `choices_` container's size
	Choice* reinsertChoice(uint index, uint newIndex);
	Choice* addChoice(const Choice& choice);
	Choice* addChoice(Choice&& choice);
	/// \exception Error Tried to remove a Choice past the `choices_` container's size
	bool removeChoice(uint index);
	void clearChoices() noexcept;

	void acceptVisitor(EventVisitor* visitor) override;

	/// \todo make it private and create getters/setters
	std::vector<Choice> choices_;

	//todo: do not botch
	QString getComponentSubTypeName()    const noexcept override { return "Choice"; }
    EventSubType getComponentEventType() const noexcept override { return EventSubType::EVENT_CHOICE; }

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventChoice's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Scene* const parentScene, const QString& label, const Translation* const text, const std::vector<Choice>* const choices)> onRun_ = nullptr;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// A text to be displayed during Choice selection screen
	Translation menuText_;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};