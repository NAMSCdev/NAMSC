#pragma once

#include <functional>
#include <QString>
#include <vector>

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
	/// \param label Displayed in the Editor to distinquish between important Events
	explicit Event(Scene* const parentScene, const QString& label = "", const std::vector<std::shared_ptr<Action>>& actions = std::vector<std::shared_ptr<Action>>());
	Event(Event&& obj)                      noexcept;
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
	virtual void syncWithSave() override;

	const std::vector<std::shared_ptr<Action>>* getActions() const noexcept;
	/// \exception Error Tried to get an Action past the `actions_` container's size
	const std::shared_ptr<Action> getAction(uint index)      const;
	/// \exception Error Tried to get an Action past the `actions_` container's size
	std::shared_ptr<Action>       getAction(uint index);
	const std::vector<std::shared_ptr<Action>>* setActions(const std::vector<std::shared_ptr<Action>>& actions) noexcept;
	const std::vector<std::shared_ptr<Action>>* setActions(std::vector<std::shared_ptr<Action>>&& actions) noexcept;
	std::shared_ptr<Action> addAction(Action* action);
	std::shared_ptr<Action> addAction(std::shared_ptr<Action>&& action);
	/// \exception Error Tried to insert a new Action past the `actions_` container's size
	std::shared_ptr<Action> insertAction(uint index, Action* action);
	/// \exception Error Tried to insert a new Action past the `actions_` container's size
	std::shared_ptr<Action> insertAction(uint index, std::shared_ptr<Action>&& action);
	/// \exception Error Tried to reinsert a new Action past the `actions_` container's size
	std::shared_ptr<Action> reinsertAction(uint index, uint newIndex);
	/// \exception Error Tried to remove an Action past the `actions_` container's size
	bool removeAction(uint index);
	void clearActions() noexcept;

	virtual void acceptVisitor(EventVisitor* visitor) = 0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Displayed in the Editor to distinquish important Events
	QString label = "";

	Scenery scenery;

	Scene* const parentScene;

    //todo: do not botch
    virtual QString getComponentTypeName()        const noexcept { return "Event"; }
    virtual SceneComponentType getComponentType() const noexcept { return EVENT; }
    virtual EventSubType getComponentEventType()  const noexcept override = 0;
    virtual QString getComponentName()            const noexcept{ return label; }
protected:
	std::vector<std::shared_ptr<Action>> actions_;

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