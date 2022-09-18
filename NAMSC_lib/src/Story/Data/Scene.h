#pragma once
#include "Global.h"

#include "Story/Event/Event.h"
#include "Story/Data/Visual/Scenery/Scenery.h"

//This hasn't been fully thought through yet. It is WIP
//Logical unit of the novel's flow in the Story
//The Editor user should be able to create one whenever
class Scene
{
	//Our overlord
	friend class Story;
	//Friends for serialization
	friend QIODevice &operator>>(QIODevice &device, SceneryObject &t);
	friend QIODevice &operator<<(QIODevice &device, const SceneryObject &t);
public:
	Scene() = default;
	//TODO: add a special constructor, once fields are set in stone
	//Scene(

protected:
	//Running a Scene means executing Events that are stored in the [events] container. 
	void						run		(unsigned offset);

	//An optional name for a Scene, commonly used by the Editor User to quickly distinguish amongst other Scenes
	QString						label;

private:
	//All the Events to be executed in the Scene
	std::vector<uPtr<Event>>	events;
	
	//Media of the Scene
	Scenery						scenery;

	//TODO: serialization
	//---SERIALIZATION---
	//Loading an object from a binary file
	virtual void serializableLoad(QIODevice &ar)
	{
		QDataStream dataStream(&ar);
		dataStream;
	}
	//Saving an object to a binary file
	virtual void serializableSave(QIODevice &ar) const
	{
		QDataStream dataStream(&ar);
		dataStream << SerializationID::Scene;
	}
};