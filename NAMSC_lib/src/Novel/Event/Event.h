#pragma once

#include <functional>
#include <QString>
#include <vector>

#include "Novel/SceneComponent.h"
#include "Novel/Action/Action.h"
#include "Novel/Event/Visitor/EventVisitor.h"
#include "Novel/Data/Visual/Scenery/Scenery.h"

/// Represents a state change in the Scene
class Event : public NovelFlowInterface, public SceneComponent
{
	/// Our overlord
	friend Scene;
	/// Swap trick
	friend void swap(Event& first, Event& second) noexcept;
public:
	/// \param label Displayed in the Editor to distinquish important Events
	explicit Event(Scene* const parentScene, const QString& label = "", std::vector<std::unique_ptr<Action>>&& actions = std::move(std::vector<std::unique_ptr<Action>>()));
	Event(const Event& obj)                 noexcept = delete;
	Event(Event&& obj)                      noexcept;
	Event& operator=(const Event& obj)      noexcept = delete;
	bool operator==(const Event& obj) const noexcept = delete;
	bool operator!=(const Event& obj) const noexcept = delete;
	//The destructor needs to be virtual, so the proper destructor will always be called when destroying an Action pointer
	virtual ~Event() = 0;

	/// Checks if the Event's Actions don't have any Errors, which would halt the Novel execution
	/// \return Whether an Error has occurred
	virtual bool errorCheck(bool bComprehensive = false) const;

	uint getIndex() const;

	virtual void run()    override;
	/// Some of the Event's Actions might be designed to update things and should be called frequently until the end of the Event
	virtual void update() override;
	virtual void end()    override;

	/// Some of the Event's Actions might need to access the data, that is a part of the Save
	/// Must be called after the Save is loaded
	virtual void syncWithSave() noexcept override;

	const std::vector<std::unique_ptr<Action>>* getActions() const noexcept;
	/// \exception Error Tried to get an Action past the `actions` container's size
	const Action* getAction(uint actionIndex) const;
	/// \exception Error Tried to get an Action past the `actions` container's size
	Action*       getAction(uint actionIndex);
	/// Takes ownership of the Action and manages its destruction
	void addAction(Action* action);
	/// Takes ownership of the Action and manages its destruction
	/// \exception Error Tried to insert a new Action past the `actions` container's size
	bool insertAction(uint actionIndex, Action* action);
	/// \exception Error Tried to remove an Action past the `actions` container's size
	bool removeAction(uint actionIndex);
	void clearActions() noexcept;

	virtual void acceptVisitor(EventVisitor* visitor) = 0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Displayed in the Editor to distinquish important Events
	QString label = "";

	Scenery scenery;

	Scene* const parentScene;

    // SceneComponent for EventsTree
    virtual QString getTypeName() { return "Event"; }
    virtual QString getSubTypeName() = 0;
    virtual SceneComponentType getType() { return EVENT; }
    virtual EventSubType getEventType() = 0;
    virtual QString getName() { return label; }
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