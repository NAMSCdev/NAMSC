#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

//Base class for the rest of the ActionFilters
class ActionFilter : public Action
{
public:
	ActionFilter() = default;
	ActionFilter(unsigned sceneID, unsigned eventExecutionOrder, int objectID = -1, double intensivness = 100.0, QString &&label = "") :
		Action(sceneID, eventExecutionOrder, move(label)), intensivness(intensivness), objectID(objectID) {}
	//The destructor needs to be virtual, so the proper destructor will always be called when destroying an ActionFilter pointer
	virtual ~ActionFilter()	= 0;

protected:
	//If objectID is set to -1, it will affect the viewPort, otherwise some object in the Scenery
	int				objectID										= -1;

	//If objectID is set to -1, it will affect the viewPort, otherwise some object in the Scenery
	//empty list means all the parts
	std::vector<unsigned> objectPartsAffected;

	//Sets the intesivity of the filter in percent
	//Accepted values: 0.0-100.0
	double			intensivness									= 100.0;

	//---SERIALIZATION---
	//Loading an object from a binary file
	virtual void serializableLoad(QIODevice &ar) override
	{
		Action::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> objectID >> intensivness;
	}
	//Saving an object to a binary file
	virtual void serializableSave(QIODevice &ar) const override
	{
		Action::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << objectID << intensivness;
	}
};