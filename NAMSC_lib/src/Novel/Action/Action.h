#pragma once
#include "Novel/Data/NovelFlowInterface.h"

#include "Novel/Action/Visitor/ActionVisitor.h"
#include "Serialization.h"

class Event;
class Scene;

/// Action is an additional work added to an Event
class Action : public NovelFlowInterface
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream& dataStream, Action&);
	friend QDataStream& operator<<(QDataStream& dataStream, const Action&);
	//Other friends
	friend class Event;
	friend class Scene;
public:
	Action(Event* const parentEvent, Scene* const parentScene) noexcept;
	Action(const Action& obj)                = delete;
	Action& operator=(const Action& obj) noexcept;
	bool operator==(const Action& obj) const noexcept;
	bool operator!=(const Action& obj) const = default; //{ return !(*this == obj); }
	// The destructor needs to be virtual, so the proper destructor will always be called when destroying an Action pointer
	virtual ~Action() = 0;

	/// \return Whether an Error has occurred
	virtual bool checkForErrors(bool bComprehensive = false) const override;

	virtual void run() override;
	/// Some Actions are designed to update things and should be called frequently until the end of the Event
	virtual void update() override;
	virtual void end() override;

	/// Some Actions need to access the data, that is a part of the Save
	/// Must be called after the Save is loaded
	virtual void syncWithSave() noexcept override {}

	virtual void acceptVisitor(ActionVisitor* visitor) = 0;

protected:
	/// Needed for Serialization, to know the class of an object before the loading performed
	virtual NovelLib::SerializationID getType() const  = 0;

	virtual void ensureResourcesAreLoaded() override {}

	Event* const parentEvent_;
	Scene* const parentScene_;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const;
};