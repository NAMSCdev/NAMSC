#pragma once
#include "Global.h"

#include "Story/Action/Visual/Filter/ActionFilter.h"

//[optional] Creates a Hue Filter at a SceneryObject or the viewport
class ActionFilterHue final : public ActionFilter
{
public:
	ActionFilterHue() = default;
	ActionFilterHue(unsigned sceneID, unsigned eventExecutionOrder, int hueShift = 0, double intensivness = 100.0, int objectID = -1,
		QString &&label = "") :
			ActionFilter(sceneID, eventExecutionOrder, intensivness, objectID, move(label)), hueShift(hueShift) {}

	//Executes Action's logic
	void			run		() override;

	//Accepts ActionVisitor
	void			accept	(ActionVisitor* visitor) override	{ visitor->visitActionFilterHue(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType	() const override					{ return SerializationID::ActionFilterHue; }

	//Adds Hue to every pixel of the affected object/vieport
	//Accepted values: -360 - 360
	int				hueShift									= 0;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		ActionFilter::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> hueShift;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		ActionFilter::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << hueShift;
	}
};