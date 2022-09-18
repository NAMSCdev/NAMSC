#pragma once
#include "Global.h"

#include "Story/Action/Visual/Filter/ActionFilter.h"

//[optional] Creates a Blur Filter at a SceneryObject or the viewport
class ActionFilterBlur final : public ActionFilter
{
public:
	//Algorithm used for blurring
	enum class BlurType
	{
		Gaussian
	};

	ActionFilterBlur() = default;
	ActionFilterBlur(unsigned sceneID, unsigned eventExecutionOrder, BlurType blurType = BlurType::Gaussian, double radius = 1.0,
		double intensivness = 100.0, int objectID = -1, QString &&label = "") :
			ActionFilter(sceneID, eventExecutionOrder, intensivness, objectID, move(label)), blurType(blurType), radius(radius) {}

	//Executes Action's logic
	void					run		() override;

	//Accepts ActionVisitor
	void					accept	(ActionVisitor* visitor) override	{ visitor->visitActionFilterBlur(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID			getType	() const override					{ return SerializationID::ActionFilterBlur; }

	//Algorithm used for blurring
	BlurType				blurType									= BlurType::Gaussian;

	//Radius of radius based blurs
	double					radius										= 1.0;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		ActionFilter::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> blurType >> radius;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		ActionFilter::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << blurType << radius;
	}
};