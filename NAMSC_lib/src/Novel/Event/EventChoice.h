#pragma once
#include "Novel/Event/Event.h"

#include "Novel/Data/Text/Choice.h"

class Scene;

/// Creates a Choice selection window
class EventChoice final : public Event
{
public:
	EventChoice(Scene* const parentScene) noexcept;
	/// \exception One of the Actions or the Choices or the `text` contains an Error 
	EventChoice(Scene* const parentScene, const QString label, const Translation& menuText, const std::vector<Choice>& choices, std::vector<std::unique_ptr<Action>>&& actions = std::vector<std::unique_ptr<Action>>());
	EventChoice(const EventChoice& obj) noexcept;
	EventChoice& operator=(const EventChoice& obj) noexcept;
	bool operator==(const EventChoice& obj) const noexcept;
	bool operator!=(const EventChoice& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error Invalid Action in `actions_` / invalid Choice in `choices` / invalid `text`
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const override;

	virtual Event* clone() const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the EventChoice's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, Translation* text, std::vector<Choice>* choices)> onRun) noexcept;

	const Translation* getMenuText() const noexcept;
	Translation* getMenuText() noexcept;
	void setMenuText(const Translation& menuText) noexcept;

	void acceptVisitor(EventVisitor* visitor) override;

	std::vector<Choice> choices;

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventChoice's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, Translation* text, std::vector<Choice>* choices)> onRun_ = nullptr;

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