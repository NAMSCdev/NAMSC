#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

//[optional] Base class for the rest of the ActionEffects
class ActionEffect : public Action
{
public:
	ActionEffect() = default;
	ActionEffect(unsigned sceneID, unsigned eventExecutionOrder, double x, double y, int objectID = -1, QString &&label = "") :
		Action(sceneID, eventExecutionOrder, move(label)), pos(x, y), objectID(objectID) {}

	//The destructor needs to be virtual, so the proper destructor will always be called when destroying an Action pointer
	virtual ~ActionEffect() override = 0;

	//Executes Action's logic
	void					run() override								= 0;

	//Accepts ActionVisitor
	void					accept(ActionVisitor* visitor) override		= 0;

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID			getType() const override					= 0;

	//Specifies where the effect is placed in local position (in relation to the object's origin, not the vieport's, unless the affected object is the viewport itself)
	struct EffectPos
	{
		EffectPos(double x, double y) :
			x(x), y(y) {};
		double	x = 0,
				y = 0;
	}						pos;

	//If objectID is set to -1, it will affect the viewPort, otherwise some object in the Scenery
	int						objectID									= -1;

	//---SERIALIZATION---
	//Loading an object from a binary file
	virtual void serializableLoad(QIODevice &ar) override
	{
		Action::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> pos.x >> pos.y >> objectID;
	}
	//Saving an object to a binary file
	virtual void serializableSave(QIODevice &ar) const override
	{
		Action::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << pos.x << pos.y << objectID;
	}
};