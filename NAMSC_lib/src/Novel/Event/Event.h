#pragma once

#include <functional>
#include <QString>
#include <vector>

#include "Novel/Action/Action.h"
#include "Novel/Event/Visitor/EventVisitor.h"
#include "Novel/Data/Visual/Scenery/Scenery.h"

/// Represents a state change in the Scene
class Event : public NovelFlowInterface
{
	//Our overlord
	friend class Scene;
	//Good Friends who Visit us (Events) often :>
	friend class EventVisitorChangeID;
public:
	Event(Scene* const parentScene) noexcept;
	Event(Scene* const parentScene, const QString label, std::vector<std::unique_ptr<Action>>&& actions = std::vector<std::unique_ptr<Action>>());
	Event(const Event& obj) = delete;
	Event& operator=(const Event& obj) noexcept;
	bool operator==(const Event& obj) const noexcept;
	bool operator!=(const Event& obj) const = default; //{ return !(*this == obj); }
	//The de	structor needs to be virtual, so the proper destructor will always be called when destroying an Action pointer
	virtual ~Event() = default;

	/// Checks if the Event's Actions don't have any Errors, which would halt the Novel execution
	/// \return Whether an Error has occurred
	virtual bool checkForErrors(bool bComprehensive = false) const;

	virtual Event* clone() const = 0;

	uint getIndex() const;

	virtual void run() override;
	/// Some of the Event's Actions might be designed to update things and should be called frequently until the end of the Event
	virtual void update() override;
	virtual void end() override;

	/// Some of the Event's Actions might need to access the data, that is a part of the Save
	/// Must be called after the Save is loaded
	virtual void syncWithSave() noexcept override;

	virtual void acceptVisitor(EventVisitor* visitor) = 0;

	/// Displayed in the Editor to distinquish important Events
	QString label = "";

	Scenery scenery;

	Scene* const parentScene;
protected:
	std::vector<std::unique_ptr<Action>> actions_;

	/// Needed for Serialization, to know the class of an object before the loading performed
	virtual NovelLib::SerializationID getType() const = 0;

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