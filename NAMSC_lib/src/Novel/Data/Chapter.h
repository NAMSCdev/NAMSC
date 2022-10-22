#pragma once
#include "Global.h"
#include "Novel/Data/Scene.h"

#include "Novel/Data/Visual/Scenery/Scenery.h"

/// A catalogue of Scenes for better navigation
/// [optional] Allows more intelligent Asset loading 
class Chapter
{
	//Our overlord
	friend class Novel;
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Chapter&);
	friend QDataStream& operator<<(QDataStream&, const Chapter&);
public:
	Chapter() = default;
	Chapter(QString&& label, QVector<uPtr<Event>>&& events);

private:
	/// Executes [Events](#Event) that are stored in the [`events` container](#events)
	/// @param offset The first [Event](#Event) to be executed from the container
	void run(uint offset);

	/// Removes an [Events](#Event) from the [`events` container](#events)
	/// Fixes all the others [Events's executionOrders](#Event#executionOrder) and corrects [Jumps](#Jump) or marks them as invalid
	/// @param executionOrder ID of an Event is equivalent with its order in execution. This  one will be deleted
	/// @todo add Visitors to fix Events and Jumps
	void removeScene(uint sceneID);

	/// Inserts an [Events](#Event) into [`events` container](#events) at certain point
	/// Fixes all the others [Events's executionOrders](#Event#executionOrder) and corrects [Jumps](#Jump)
	/// @param executionOrder ID of an Event is equivalent with its order in execution. The even will be inserted past this `executionOrder`
	/// @todo add Visitors to fix Events and Jumps
	void appendScene(Scene&& scene);

	/// A name for a Chapter, commonly used by the Editor User to quickly distinguish amongst other Chapters
	QString label;

private:
	/// All the Scenes in the Chapter
	QVector<uPtr<Scene>> events;

	//---SERIALIZATION---
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream &dataStream)
	{
		dataStream;
	}
	/// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const
	{
		dataStream << SerializationID::Scene;
	}
};




inline Chapter::Chapter(QString&& label, QVector<uPtr<Event>>&& events) :
	label(move(label)), events(move(events))
{
}