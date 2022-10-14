#pragma once
#include "Global.h"

#include "Story/Action/Visual/ActionSceneryObject.h"

///[optional] Base class for the rest of the ActionEffects
class ActionEffect : public ActionSceneryObject
{
public:
	enum class EffectShape
	{
		Ellipse,
		Rectangle
	};

	ActionEffect() = default;
	ActionEffect(Event *parent, unsigned actionID, QString &&label, QString &&sceneryObjectName, EffectShape effectShape, QPoint pos,
				 QSize size, unsigned strength) :
		ActionSceneryObject(parent, actionID, move(label), move(sceneryObjectName)), effectShape(effectShape), pos(pos), 
		size(size), strength(strength) {}
	ActionEffect(const ActionEffect& asset)				= default;
	ActionEffect& operator=(const ActionEffect& asset)	= default;

protected:
	///Determines the shape of the effect: area that will affect an Image
	EffectShape effectShape;

	///Specifies where the effect is placed in local position (in relation to the object's origin, not the vieport's, unless the affected object is the viewport itself)
	QPoint		pos;

	///Semi-major and semi-minor axes of an Ellipse or size of a Rectangle
	QSize		size;	

	///Strength of the Effect
	double		strength	= 1.0;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const override;
};