#pragma once
#include "Global.h"

#include "Story/Action/Visual/Filter/ActionFilter.h"

//[optional] Creates a Saturation Filter at a SceneryObject or the viewport
class ActionFilterSaturation final: public ActionFilter
{
public:
	ActionFilterSaturation() = default;
	ActionFilterSaturation(unsigned sceneID, unsigned eventExecutionOrder, double addedSaturation = 0, double percentSaturation = 100.0,
		double intensivness = 100.0, int objectID = -1, QString &&label = "") :
			ActionFilter(sceneID, eventExecutionOrder, intensivness, objectID, move(label)), addedSaturation(addedSaturation), percentSaturation(percentSaturation) {}
	
	//Executes Action's logic
	void			run		() override;

	//Accepts ActionVisitor
	void			accept	(ActionVisitor* visitor) override	{ visitor->visitActionFilterSaturation(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType	() const override					{ return SerializationID::ActionFilterSaturation; }

	//Adds Saturation to every pixel of the affected object/vieport
	//Accepted values: 0.0 - 1.0
	double			addedSaturation								= 0;

	//Modifies percent value of Saturation in every pixel of the affected object/vieport
	double			percentSaturation							= 100.0;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		ActionFilter::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> addedSaturation >> percentSaturation;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		ActionFilter::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << addedSaturation << percentSaturation;
	}
};