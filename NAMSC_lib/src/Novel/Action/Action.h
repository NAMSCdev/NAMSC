#pragma once
#include "Novel/Data/NovelFlowInterface.h"

#include <memory>

#include "Novel/Action/Visitor/ActionVisitor.h"
#include "Serialization.h"

class Event;
class Scene;

/// Action is an additional work added to an Event
class Action : public NovelFlowInterface
{
	friend Event;
	friend Scene;
	/// Swap trick
	friend void swap(Action& first, Action& second) noexcept;
public:
	explicit Action(Event* const parentEvent) noexcept;
	Action(Action&& action)                   noexcept;
	// The destructor needs to be virtual, so the proper destructor will always be called when destroying an Action pointer
	virtual ~Action() = 0;

	/// \return Whether an Error has occurred
	virtual bool errorCheck(bool bComprehensive = false) const override;

	virtual void run()    override;
	/// Some Actions are designed to update things and should be called frequently until the end of the Event
	virtual void update() override;
	virtual void end()    override;

	/// Some Actions need to access the data, that is a part of the Save
	/// Must be called after the Save is loaded
	virtual void syncWithSave() override;

	virtual void acceptVisitor(ActionVisitor* visitor) = 0;

	Event* const parentEvent;

protected:
	/// Needed for Serialization, to know the class of an object before the loading performed
	virtual NovelLib::SerializationID getType() const  = 0;

	virtual void ensureResourcesAreLoaded() override;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const;
};