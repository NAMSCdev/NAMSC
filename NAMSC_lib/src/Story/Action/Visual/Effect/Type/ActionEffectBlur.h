#pragma once
#include "Global.h"

#include "Story/Action/Visual/Effect/ActionEffect.h"

//[optional] Creates a Blur Effect at some point in a SceneryObject or the viewport
class ActionEffectBlur final : public ActionEffect
{
public:
	//Algorithm used for blurring
	enum class BlurType
	{
		Gaussian
	};

	ActionEffectBlur() = default;
	ActionEffectBlur(unsigned sceneID, unsigned eventExecutionOrder, BlurType blurType = BlurType::Gaussian, 
		double radius = 1.0, double x = 0.0, double y = 0.0, int objectID = -1, QString &&label = "") :
			ActionEffect(sceneID, eventExecutionOrder, x, y, objectID, move(label)), blurType(blurType)  {}

	//Executes Action's logic
	void			run		() override;

	//Accepts ActionVisitor
	void			accept	(ActionVisitor* visitor) override	{ visitor->visitActionEffectBlur(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType	() const override					{ return SerializationID::ActionEffectBlur; }

	//Algorithm used for blurring
	BlurType		blurType									= BlurType::Gaussian;

	//Radius of radius based blurs
	double			radius										= 1.0;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		ActionEffect::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> blurType >> radius;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		ActionEffect::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << blurType << radius;
	}
};