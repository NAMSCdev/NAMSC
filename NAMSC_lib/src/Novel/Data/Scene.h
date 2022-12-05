#pragma once

#include "Novel/Data/Chapter.h"
#include "Novel/Data/Visual/Scenery/Scenery.h"
#include "Novel/Event/Event.h"

/// The logical unit of the Novel's flow in the [Novel](#Novel]
/// The Editor user should be able to create one whenever
class Scene final : public NovelFlowInterface
{
	//Our overlord
	friend class Novel;
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, SceneryObject&);
	friend QDataStream& operator<<(QDataStream&, const SceneryObject&);
	//Other Friends
	friend class Event;
	friend class NovelSettings;
public:
	Scene() = default;
	/// \exception Error A detailed Exception is thrown, if the proper QtMessageHandler is installed. Error might occur in any of the contained data as it is called top-down, so it's too long to list it here, instead check other data structures if interested
	Scene(const QString& name, const QString& chapterName, const std::vector<std::unique_ptr<Event>>& events, const Scenery& scenery);
	Scene(const Scene& obj) noexcept;
	Scene& operator=(Scene obj) noexcept;
	//todo: define
	//bool operator==(const Scene& obj) const;
	bool operator!=(const Scene& obj) const = default;

	/// Checks if the Scene's Events can load Definitions and Resources associated with them and don't have any other Errors, which would halt the Novel execution
	/// \exception Error A detailed Exception is thrown, if the proper QtMessageHandler is installed. Error might occur in any of the contained data as it is called top-down, so it's too long to list it here, instead check other data structures if interested
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const override;
	void ensureResourcesAreLoaded() override;

	QString nextFreeEventName();

	/// \exception Crititcal Tried to run an Event past the `events_` container's size
	void run() override;
	/// \exception Crititcal Tried to update an Event past the `events_` container's size
	void update() override;
	/// \exception Crititcal Tried to end an Event past the `events_` container's size
	void end() override;

	void syncWithSave() noexcept override;

	const std::vector<std::unique_ptr<Event>>* getEvents() const noexcept;
	/// \exception Error Tried to get an Event past the `events` container's size
	const Event* getEvent(uint eventIndex) const;
	/// \exception Error Tried to get an Event past the `events` container's size
	Event* getEvent(uint eventIndex);
	/// \exception Error Tried to insert a new Event past the `events` container's size
	bool insertEvent(uint eventIndex, std::unique_ptr<Event>&& event);
	/// \exception Error Tried to remove an Event past the `events` container's size
	bool removeEvent(uint eventIndex);

	/// Automatically assigned upon creation or changed by the Editor User
	QString	name                = "";

	/// Currently displayed media of the Scene
	Scenery	scenery;

private:
	QString        chapterName_ = "";
	const Chapter* chapter_     = nullptr;

	std::vector<std::unique_ptr<Event>> events_;

	//---SERIALIZATION---
	/// \exception Critical Could not find a Stat's type, so the whole becomes unreadable
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);

	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};