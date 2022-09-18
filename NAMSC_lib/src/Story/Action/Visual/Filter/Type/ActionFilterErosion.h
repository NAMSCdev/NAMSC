#pragma once
#include "Global.h"

#include "Story/Action/Visual/Filter/ActionFilter.h"

//[optional] Creates a Erosion Filter at a SceneryObject or the viewport
class ActionFilterErosion final : public ActionFilter
{
public:
	ActionFilterErosion() = default;
	ActionFilterErosion(unsigned sceneID, unsigned eventExecutionOrder, unsigned pixels = 1, double intensivness = 100.0, 
		int objectID = -1, QString &&label = "") :
			ActionFilter(sceneID, eventExecutionOrder, intensivness, objectID, move(label)), pixels(pixels) {}
	
	//Executes Action's logic
	void			run		() override;

	//Accepts ActionVisitor
	void			accept	(ActionVisitor* visitor) override	{ visitor->visitActionFilterErosion(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType	() const override					{ return SerializationID::ActionFilterErosion; }

	//Strength of Erosion
	unsigned		pixels										= 1;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		ActionFilter::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> pixels;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		ActionFilter::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << pixels;
	}
};