#pragma once
#include "Novel/Event/Event.h"

class Scene;

/// Redirects the flow to an another Scene
class EventJump final : public Event
{
public:
	EventJump(Scene* const parentScene) noexcept;
	/// \exception One of the Actions contains an Error or the `jumpToSceneName` points to a deleted Scene or the `condition` is not structured properly
	EventJump(Scene* const parentScene, const QString& label, const QString& jumpToSceneName, const QString& condition, std::vector<std::unique_ptr<Action>>&& actions = std::vector<std::unique_ptr<Action>>());
	EventJump(const EventJump& obj) noexcept;
	EventJump& operator=(const EventJump& obj) noexcept;
	bool operator==(const EventJump& obj) const noexcept;
	bool operator!=(const EventJump& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error invalid Action in `actions_` / invalid `regex` / invalid `Stat` / invalid `logicalExpression`
	/// \return Whether an Error has occurred
	/// \todo implement this
	bool checkForErrors(bool bComprehensive = false) const override;

	virtual Event* clone() const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the EventJump's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QString jumpToSceneName, QString condition)> onRun) noexcept;

	void acceptVisitor(EventVisitor* visitor) override;

	QString jumpToSceneName = "";

	/// A jump might contain a logical expression, so the jump happens only if the `condition` is met
	QString condition       = "";

private:
	/// Needed for Serialization, to know the class of an object before the loading performed
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the EventJump's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, QString jumpToSceneName, QString condition)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};