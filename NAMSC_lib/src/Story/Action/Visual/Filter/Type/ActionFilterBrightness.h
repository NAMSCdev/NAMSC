#pragma once
#include "Global.h"

#include "Story/Action/Visual/Filter/ActionFilter.h"

//[optional] Creates a Brightnss Filter at a SceneryObject or the viewport
class ActionFilterBrightness final : public ActionFilter
{
public:
	ActionFilterBrightness() = default;
	ActionFilterBrightness(unsigned sceneID, unsigned eventExecutionOrder, double addedBrightness = 0.0, double percentBrightness = 100.0,
		double intensivness = 100.0, int objectID = -1, QString &&label = "") :
			ActionFilter(sceneID, eventExecutionOrder, intensivness, objectID, move(label)), addedBrightness(addedBrightness), 
				percentBrightness(percentBrightness) {}

	//Executes Action's logic
	void			run		() override;

	//Accepts ActionVisitor
	void			accept	(ActionVisitor* visitor) override	{ visitor->visitActionFilterBrightness(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType	() const override					{ return SerializationID::ActionFilterBrightness; }

	//Adds Brightness to every pixel of the affected object/vieport
	//Accepted values: 0.0 - 1.0
	double			addedBrightness								= 0.0;

	//Modifies percent value of Brightness in every pixel of the affected object/vieport
	double			percentBrightness							= 100.0;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		ActionFilter::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> addedBrightness >> percentBrightness;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		ActionFilter::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << addedBrightness << percentBrightness;
	}
};