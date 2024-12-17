#pragma once

#include "pvnLib/Novel/Data/Chapter.h"
#include "pvnLib/Novel/Data/Visual/Scenery/Scenery.h"
#include "pvnLib/Novel/Event/Event.h"

/// The logical unit of the Novel's flow in the [Novel](#Novel)
/// The Editor user should be able to create one whenever
class Scene final : public SceneComponent, public NovelFlowInterface
{
	/// Our overlord
	friend class Novel;
	//Other Friends
	friend Event;
	friend struct NovelSettings;
	/// Swap trick
	friend void swap(Scene& first, Scene& second) noexcept;
public:
	Scene()                                 noexcept = default;
	/// \exception Error A detailed Exception is thrown, if the proper QtMessageHandler is installed. Error might occur in any of the contained data as it is called top-down, so it's too long to list it here, instead check other data structures if interested
	explicit Scene(const QString& name, const QString& chapterName = ""/*, const Scenery& scenery = Scenery(),*/);
	Scene(const Scene& obj)                 noexcept;
	Scene(Scene&& obj)                      noexcept;
	Scene& operator=(const Scene& obj)      noexcept;
	bool operator==(const Scene& obj) const noexcept;
	bool operator!=(const Scene& obj) const noexcept = default;
	/// Checks if the Scene's Events can load Definitions and Resources associated with them and don't have any other Errors, which would halt the Novel execution
	/// \exception Error A detailed Exception is thrown, if the proper QtMessageHandler is installed. Error might occur in any of the contained data as it is called top-down, so it's too long to list it here, instead check other data structures if interested
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const override;
	void ensureResourcesAreLoaded() override;

	QString nextFreeEventName();

	/// \exception Crititcal Tried to run an Event past the `events_` container's size
	void run() override;
	/// \exception Crititcal Tried to update an Event past the `events_` container's size
	void update() override;
	/// \exception Crititcal Tried to end an Event past the `events_` container's size
	void end() override;

	void syncWithSave() override;

	const std::vector<std::shared_ptr<Event>>* getEvents() const noexcept;
	/// \exception Error Tried to get an Event past the `events_` container's size
	const std::shared_ptr<Event> getEvent(uint index) const;
	/// \exception Error Tried to get an Event past the `events_` container's size
	std::shared_ptr<Event>       getEvent(uint index);
	/// \exception Error Could not find an Event with this name
	const std::shared_ptr<Event> getEvent(const QString& name) const;
	/// \exception Error Could not find an Event with this name
	std::shared_ptr<Event>       getEvent(const QString& name);
	/// \exception Error Could not find an Event with this name
	const std::vector<std::shared_ptr<Event>>* setEvents(std::vector<std::shared_ptr<Event>>&& events) noexcept;
	std::shared_ptr<Event> addEvent(Event* event) noexcept;
	std::shared_ptr<Event> addEvent(std::shared_ptr<Event>&& event) noexcept;
	/// \exception Error Tried to insert a new Event past the `events_` container's size
	std::shared_ptr<Event> insertEvent(uint index, Event* event);
	/// \exception Error Tried to insert a new Event past the `events_` container's size
	std::shared_ptr<Event> insertEvent(uint index, std::shared_ptr<Event>&& event);
	/// \exception Error Tried to reinsert a new Event past the `events_` container's size
	std::shared_ptr<Event> reinsertEvent(uint index, uint newIndex);
	/// \exception Error Tried to remove an Event past the `events_` container's size
	bool removeEvent(uint index);
	/// \exception Error Could not find an Event with this name
	bool removeEvent(const QString& name);
	void clearEvents() noexcept;

	/// Automatically assigned upon creation or changed by the Editor User
	QString	name                = "";

	/// Currently displayed media of the Scene
	Scenery	scenery             = Scenery(this);

	//todo: do not botch
    QString getComponentTypeName()        const noexcept override { return "Scene"; }
    QString getComponentSubTypeName()     const noexcept override { return "Scene"; }
    SceneComponentType getComponentType() const noexcept override { return SCENE; }
    EventSubType getComponentEventType()  const noexcept override { return EventSubType::NOT_EVENT; }
    QString getComponentName()            const noexcept override { return name; }
	
private:
	QString        chapterName_ = "";
	const Chapter* chapter_     = nullptr;

	std::vector<std::shared_ptr<Event>> events_;

public:
	//---SERIALIZATION---
	/// \exception Critical Could not find a Stat's type, so the whole becomes unreadable
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);

	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};