#pragma once
#include "Global.h"

#include "Novel/Event/Event.h"
#include "Novel/Data/Visual/Scenery/Scenery.h"

///A catalogue of Scenes for better navigation
///[optional] Allows more intelligent Asset loading 
class Chapter
{
	//Our overlord
	friend class Novel;
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, SceneryObject&);
	friend QDataStream& operator<<(QDataStream&, const SceneryObject&);
public:
	Chapter() { assignLabel(); };
	Chapter(QString &&label, QVector<uPtr<Event>> &&events, Scenery &&scenery) : 
		label(move(label)), events(move(events)), scenery(move(scenery)) { if (label.isEmpty()) assignLabel(); };

private:
	///Executes [Events](#Event) that are stored in the [`events` container](#events)
	///@param offset The first [Event](#Event) to be executed from the container
	void run(uint offset);

	///Removes an [Events](#Event) from the [`events` container](#events)
	///Fixes all the others [Events's executionOrders](#Event#executionOrder) and corrects [Jumps](#Jump) or marks them as invalid
	///@param executionOrder ID of an Event is equivalent with its order in execution. This  one will be deleted
	///@todo: add Visitors to fix Events and Jumps
	void removeEvent(uint executionOrder);

	///Inserts an [Events](#Event) into [`events` container](#events) at certain point
	///Fixes all the others [Events's executionOrders](#Event#executionOrder) and corrects [Jumps](#Jump)
	///@param executionOrder ID of an Event is equivalent with its order in execution. The even will be inserted past this `executionOrder`
	///@todo: add Visitors to fix Events and Jumps
	void insertEvent(uint executionOrder, Event &&ev);

	///An optional name for a Scene, commonly used by the Editor User to quickly distinguish amongst other Scenes
	///Automatically asigned upon creation
	QString		label;

private:
	///All the Events to be executed in the Scene
	QVector<uPtr<Event>>	events;

	//TODO: serialization
	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream)
	{
		dataStream;
	}
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const
	{
		dataStream << SerializationID::Scene;
	}
};