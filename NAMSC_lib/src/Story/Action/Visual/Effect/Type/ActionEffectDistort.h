#pragma once
#include "Global.h"

#include "Story/Action/Visual/Effect/ActionEffect.h"

//[optional] Creates a Distort Effect at some point in a SceneryObject or the viewport
class ActionEffectDistort final : public ActionEffect
{
public:
	ActionEffectDistort() = default;
	ActionEffectDistort(unsigned sceneID, unsigned eventExecutionOrder, double x, double y, int objectID = -1, QString &&label = "") :
		ActionEffect(sceneID, eventExecutionOrder, x, y, objectID, move(label)) {}

	//Executes Action's logic
	void			run		() override;

	//Accepts ActionVisitor
	void			accept	(ActionVisitor* visitor) override	{ visitor->visitActionEffectDistort(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType	() const override					{ return SerializationID::ActionEffectDistort; }

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		ActionEffect::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		ActionEffect::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream;
	}
};